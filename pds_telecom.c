#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <gsl/gsl_linalg.h>

typedef struct {
    double real;
    double imag;
} Complexo;

typedef struct {
    int linhas;
    int colunas;
    Complexo **dados;
} Matriz;

Matriz* criar_matriz(int n, int m) {
    Matriz* matriz = (Matriz*) malloc(sizeof(Matriz));
    matriz->linhas = n;
    matriz->colunas = m;
    matriz->dados = (Complexo**) malloc(n * sizeof(Complexo*));
    for (int i = 0; i < n; i++) {
        matriz->dados[i] = (Complexo*) malloc(m * sizeof(Complexo));
    }
    return matriz;
}


/// Função para liberar memoria
void free_matrix(Matriz mat) {
    for (int i = 0; i < mat.linhas; i++) {
        free(mat.dados[i]);
    }
    free(mat.dados);
}

/**
* Função que leia um arquivo txt ascii e separa cada byte do arquivo em 4 números inteiros de 0 a 3, de acordo com os valores dos bits.
* @param[in] filename
* @param[in] numElements
* @param[out] elements
*/
int* tx_data_read(const char* filename, int* numElements) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    /// Determinar o tamanho do arquivo
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    /// Alocar memória para armazenar os valores separados
    int* elements = (int*)malloc(fileSize * 4 * sizeof(int));
    if (elements == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(file);
        return NULL;
    }

    int byte;
    int count = 0;

    /// Ler cada byte do arquivo e separar em 4 números inteiros
    while ((byte = fgetc(file)) != EOF) {
        elements[count++] = (byte >> 6) & 3;
        elements[count++] = (byte >> 4) & 3;
        elements[count++] = (byte >> 2) & 3;
        elements[count++] = byte & 3;
    }

    fclose(file);

    /// Definir o número de elementos
    *numElements = count;

    return elements;
}


void rx_data_write(const char* filename, const int* elements, int numElements) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    for (int i = 0; i < numElements; i++) {
        unsigned char realByte = (unsigned char)elements[i];


        fwrite(&realByte, sizeof(unsigned char), 1, file);

    }

    fclose(file);
}


Complexo *tx_qam_mapper(int *indices, int size) {
    Complexo *symbols = (Complexo *)malloc(size * sizeof(Complexo));

    for (int i = 0; i < size; i++) {
        int index = indices[i];
        Complexo symbol;
        switch (index) {
            case 0:
                symbol.real = -1.0;
                symbol.imag = 1.0;
                break;
            case 1:
                symbol.real = -1.0;
                symbol.imag = -1.0;
                break;
            case 2:
                symbol.real = 1.0;
                symbol.imag = 1.0;
                break;
            case 3:
                symbol.real = 1.0;
                symbol.imag = -1.0;
                break;
            default:
                printf("Índice inválido.\n");
                break;
        }
        symbols[i] = symbol;
    }

    return symbols;
}

Complexo *tx_layer_mapper(Complexo *symbols, int size, int num_streams) {
    Complexo *mapped_symbols = (Complexo *)malloc(size * num_streams * sizeof(Complexo));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < num_streams; j++) {
            int index = i * num_streams + j;
            mapped_symbols[index] = symbols[i];
        }
    }

    return mapped_symbols;
}

Matriz* channel_gen(int Nr, int Nt) {
    Matriz* channel = criar_matriz(Nr, Nt);

    for (int i = 0; i < channel->linhas; i++) {
        for (int j = 0; j < channel->colunas; j++) {
            channel->dados[i][j].real = -1.0 + 2.0 * rand() / (RAND_MAX + 1.0);
            channel->dados[i][j].imag = -1.0 + 2.0 * rand() / (RAND_MAX + 1.0);
        }
    }

    return channel;
}

Complexo* channel_transmission(Complexo* symbols, int size, Matriz* channel, double noise_min, double noise_max) {
    Complexo* received_symbols = (Complexo*)malloc(size * sizeof(Complexo));

    for (int i = 0; i < size; i++) {
        Complexo symbol = symbols[i];
        Complexo sum = {0.0, 0.0};

        for (int j = 0; j < channel->colunas; j++) {
            Complexo channel_entry = channel->dados[i % channel->linhas][j];
            Complexo noise = {0.0, 0.0};
            noise.real = noise_min + (noise_max - noise_min) * rand() / (RAND_MAX + 1.0);
            noise.imag = noise_min + (noise_max - noise_min) * rand() / (RAND_MAX + 1.0);

            Complexo product = {
                channel_entry.real * symbol.real - channel_entry.imag * symbol.imag,
                channel_entry.real * symbol.imag + channel_entry.imag * symbol.real
            };
            sum.real += product.real + noise.real;
            sum.imag += product.imag + noise.imag;
        }

        received_symbols[i]= sum;
    }

    return received_symbols;
}

Complexo int_to_complex(int index) {
    Complexo symbol;
    switch (index) {
        case 0:
            symbol.real = -1.0;
            symbol.imag = 1.0;
            break;
        case 1:
            symbol.real = -1.0;
            symbol.imag = -1.0;
            break;
        case 2:
            symbol.real = 1.0;
            symbol.imag = 1.0;
            break;
        case 3:
            symbol.real = 1.0;
            symbol.imag = -1.0;
            break;
        default:
            printf("Índice inválido.\n");
            symbol.real = 0.0;
            symbol.imag = 0.0;
            break;
    }
    return symbol;
}

int* rx_qam_demapper(Complexo* symbols, int size){
    int* demapped_symbols = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        Complexo symbol = symbols[i];
        int index = 0;  // Add the declaration of 'index' variable here

        if (symbol.real < 0.0) {
            if (symbol.imag > 0.0) {
                index = 0;
            } else {
                index = 1;
            }
        } else {
            if (symbol.imag > 0.0) {
                index = 2;
            } else {
                index = 3;
            }
        }

        demapped_symbols[i] = index;
    }

    return demapped_symbols;
}


Complexo* rx_layer_demapper(Complexo* received_symbols, int size, int num_streams) {
    Complexo* demapped_symbols = (Complexo*)malloc(size / num_streams * sizeof(Complexo));

    for (int i = 0; i < size / num_streams; i++) {
        Complexo sum = {0.0, 0.0};

        for (int j = 0; j < num_streams; j++) {
            int index = i * num_streams + j;
            sum.real += received_symbols[index].real;
            sum.imag += received_symbols[index].imag;
        }

        demapped_symbols[i] = sum;
    }

    return demapped_symbols;
}

Matriz* svd_decomposition(Matriz* matriz, Matriz** U, gsl_vector** S, Matriz** V) {
    // Criar uma cópia da matriz do canal H
    Matriz* H_copy = criar_matriz(matriz->linhas, matriz->colunas);
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            H_copy->dados[i][j] = matriz->dados[i][j];
        }
    }

    // Converter a matriz H para uma matriz gsl
    gsl_matrix* H_gsl = gsl_matrix_alloc(matriz->linhas, matriz->colunas);
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            gsl_matrix_set(H_gsl, i, j, matriz->dados[i][j].real);
        }
    }

    // Realizar a decomposição SVD usando a GSL
    gsl_matrix* U_gsl = gsl_matrix_alloc(matriz->linhas, matriz->linhas);
    gsl_vector* S_gsl = gsl_vector_alloc(matriz->colunas);
    gsl_matrix* V_gsl = gsl_matrix_alloc(matriz->colunas, matriz->colunas);
    gsl_vector* work = gsl_vector_alloc(matriz->colunas);

    gsl_linalg_SV_decomp(H_gsl, V_gsl, S_gsl, work);
    gsl_linalg_SV_decomp(H_gsl, U_gsl, S_gsl, work);

    // Converter a matriz U, matriz S e matriz V de volta para as estruturas de dados personalizadas
    *U = criar_matriz(matriz->linhas, matriz->linhas);
    *S = gsl_vector_alloc(matriz->colunas);
    *V = criar_matriz(matriz->colunas, matriz->colunas);

    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->linhas; j++) {
            (*U)->dados[i][j].real = gsl_matrix_get(U_gsl, i, j);
        }
    }

    for (int i = 0; i < matriz->colunas; i++) {
        gsl_vector_set(*S, i, gsl_vector_get(S_gsl, i));
    }

    for (int i = 0; i < matriz->colunas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            (*V)->dados[i][j].real = gsl_matrix_get(V_gsl, i, j);
        }
    }

    // Liberar memória alocada
    gsl_matrix_free(H_gsl);
    gsl_matrix_free(U_gsl);
    gsl_vector_free(S_gsl);
    gsl_matrix_free(V_gsl);
    gsl_vector_free(work);

    return H_copy;
}

Complexo* tx_precoder_svd(Complexo* symbols, int size, Matriz* V) {
    Complexo* precoded_symbols = (Complexo*)malloc(size * sizeof(Complexo));

    for (int i = 0; i < size; i++) {
        Complexo symbol = symbols[i];
        Complexo precoded_symbol = {0.0, 0.0};

        for (int j = 0; j < V->colunas; j++) {
            Complexo V_entry = V->dados[i % V->linhas][j];
            Complexo product = {
                symbol.real * V_entry.real - symbol.imag * V_entry.imag,
                symbol.real * V_entry.imag + symbol.imag * V_entry.real
            };
            precoded_symbol.real += product.real;
            precoded_symbol.imag += product.imag;
        }

        precoded_symbols[i] = precoded_symbol;
    }

    return precoded_symbols;
}


Complexo* rx_combiner(Complexo* received_symbols, int size, Matriz* U, int Nr) {
    Complexo* combined_symbols = (Complexo*)malloc(size / Nr * sizeof(Complexo));

    for (int i = 0; i < size / Nr; i++) {
        Complexo sum = {0.0, 0.0};

        for (int j = 0; j < Nr; j++) {
            int index = i * Nr + j;

            for (int k = 0; k < U->linhas; k++) {
                Complexo U_entry = U->dados[k][j];
                Complexo product = {
                    received_symbols[index].real * U_entry.real - received_symbols[index].imag * U_entry.imag,
                    received_symbols[index].real * U_entry.imag + received_symbols[index].imag * U_entry.real
                };
                sum.real += product.real;
                sum.imag += product.imag;
            }
        }

        combined_symbols[i] = sum;
    }

    return combined_symbols;
}



Complexo* rx_feq(Complexo* received_symbols, int size, gsl_vector* S) {
    Complexo* equalized_symbols = (Complexo*)malloc(size * sizeof(Complexo));

    for (int i = 0; i < size; i++) {
        Complexo symbol = received_symbols[i];
        Complexo equalized_symbol = {0.0, 0.0};

       for (int j = 0; j < S->size; j++) {
            double S_entry = gsl_vector_get(S, j);

            Complexo product = {
                symbol.real * S_entry,
                symbol.imag * S_entry
            };

            equalized_symbol.real += product.real;
            equalized_symbol.imag += product.imag;
        }

        equalized_symbols[i] = equalized_symbol;
    }

    return equalized_symbols;
}

void gera_estatisticas(Complexo* transmitted_symbols, int* received_symbols, int size) {
    int num_errors = 0;

    for (int i = 0; i < size; i++) {
        if (transmitted_symbols[i].real != received_symbols[i] ||
            transmitted_symbols[i].imag != received_symbols[i]) {
            num_errors++;
        }
    }

    double error_percentage = (double)num_errors / size * 100;

    printf("Numero de simbolos transmitidos: %d\n", size);
    printf("Numero de simbolos recebidos com erro: %d\n", num_errors);
    printf("Porcentagem de simbolos recebidos com erro: %.2lf%%\n", error_percentage);
}


int main(){


    int num_streams = 3;
    int numElements;

  int* tx_data = tx_data_read("arquivo1.txt", &numElements);
   int size = numElements / 4;
    Complexo* tx_symbols = tx_qam_mapper(tx_data, size);
    Complexo* tx_mapped_symbols = tx_layer_mapper(tx_symbols, size, num_streams);


    /// Geração do canal aleatório H
    int Nr = 4;
    int Nt = 4;
    Matriz* channel = channel_gen(Nr, Nt);

    /// Decomposição SVD da matriz do canal H
    Matriz* U;
    gsl_vector* S;
    Matriz* V;
    Matriz* H = svd_decomposition(channel, &U, &S, &V);

    /// Precodificação dos símbolos transmitidos usando a matriz V
    Complexo* tx_precoded_symbols = tx_precoder_svd(tx_mapped_symbols, size * num_streams, V);

    /// Transmissão pelo canal com ruído
   double noise_min = -0.5;
    double noise_max = 0.5;
    Complexo* rx_received_symbols = channel_transmission(tx_mapped_symbols, size * num_streams, channel, noise_min, noise_max);

     Complexo* rx_combined_symbols = rx_combiner(rx_received_symbols, size * num_streams, U, Nr);

    /// Equalização dos símbolos recebidos usando a matriz U e vetor S da decomposição SVD
    Complexo* rx_equalized_symbols = rx_feq(rx_combined_symbols, size * num_streams, S);
    int* rx_recovered_integers = rx_qam_demapper(rx_equalized_symbols, size * num_streams);

    /// Demapeamento em camadas
     Complexo* rx_demapped_symbols = rx_layer_demapper(rx_received_symbols, size * num_streams, num_streams);
    int* rx_indices = rx_qam_demapper(rx_demapped_symbols, size);

    /// Demapeamento QAM
    int* rx_symbols = rx_qam_demapper(rx_demapped_symbols, size);


    /// Estatísticas de transmissão
    gera_estatisticas(tx_symbols, rx_symbols, size);


    rx_data_write("informacao_recebida.bin", rx_indices, size);



    /// Liberação de memória
    free(tx_data);
    free(tx_symbols);
    free(tx_mapped_symbols);
    free(tx_precoded_symbols);
    free(rx_received_symbols);
    free(rx_combined_symbols);
    free(rx_equalized_symbols);
    free(rx_demapped_symbols);
    free(rx_symbols);
    free_matrix(*channel);
    free(channel);
    free_matrix(*H);
    free(H);
    free_matrix(*U);
    free(U);
    gsl_vector_free(S);
    free_matrix(*V);
    free(V);

    return 0;
}





