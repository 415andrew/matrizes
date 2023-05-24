///@file matrizes.c
#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

/**
* Cria uma matriz.
* Esse codigo aloca memória para uma matriz n x m e retorna um ponteiro para essa matriz.
* @param[in] n ///< Números de linhas 
* @param[in] m ///< Números de colunas
* @param[out] matriz 
*/
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

/**
* Imprime uma matriz de numeros complexos.
*/
void imprimir_matriz(Matriz* matriz) {
   for (int i = 0; i < matriz->linhas; i++) {
      for (int j = 0; j < matriz->colunas; j++) {
         printf("(%.1f + %.1fi)\t", matriz->dados[i][j].real, matriz->dados[i][j].imag);

      }
      printf("\n");
   }
}

/**
* Imprime um número complexo.
*/
void print_complexo(Complexo z) {
    printf("%.1f + %.1fi", z.real, z.imag);
}

/**
* Imprime um vetor de números complexos.
*/
void print_vetor(Complexo* v, int n) {
  printf("[");
  for (int i = 0; i < n; i++) {
    print_complexo(v[i]);
    if (i < n - 1) {
      printf(" , ");
    }
  }
  printf("]\n");
}



//IMPLEMENTA��O DAS FUN��ES

/**
 * Calcula a transposta de uma Matriz de números complexos.
 * @param[in] matriz
 * @param[out] transposta
 */

Matriz* transpos_matriz(Matriz* matriz) {
   Matriz* transposta = criar_matriz(matriz->colunas, matriz->linhas);
   for (int i = 0; i < matriz->linhas; i++) {
      for (int j = 0; j < matriz->colunas; j++) {
         transposta->dados[j][i] = matriz->dados[i][j];
      }
   }
   return transposta;
}


/**
 * Calcula o produto matricial entre duas Matrizes de números complexos.
 * @param[in] matriz1
 * @param[in] matriz2
 * @param[out] resultado
 */

Matriz* multiplicar_matrizes(Matriz* matriz1, Matriz* matriz2) {

   if (matriz1->colunas != matriz2->linhas) {
      printf("As matrizes nao podem ser multiplicadas.\n");
      return NULL;
   }

   Matriz* resultado = criar_matriz(matriz1->linhas, matriz2->colunas);

   for (int i = 0; i < matriz1->linhas; i++) {
      for (int j = 0; j < matriz2->colunas; j++) {
         Complexo soma = {0, 0};
         for (int k = 0; k < matriz1->colunas; k++) {
            Complexo produto = {matriz1->dados[i][k].real * matriz2->dados[k][j].real-
                                matriz1->dados[i][k].imag * matriz2->dados[k][j].imag,
                                matriz1->dados[i][k].real * matriz2->dados[k][j].imag+
                                matriz1->dados[i][k].imag * matriz2->dados[k][j].real};
            soma.real += produto.real;
            soma.imag += produto.imag;
         }
         resultado->dados[i][j] = soma;
      }
   }

   return resultado;
}

/**
* Calcula a conjugada de uma Matriz de números complexos.
* @param[in] matriz
* @param[out] conjugada
*/
 Matriz* conjugada_matriz(Matriz* matriz){
    Matriz* conjugada = criar_matriz(matriz->colunas, matriz->linhas);
       for (int i = 0; i < matriz->linhas; i++) {
       for (int j = 0; j < matriz->colunas; j++) {
        conjugada->dados[i][j].real = matriz->dados[i][j].real;
        conjugada->dados[i][j].imag = -matriz->dados[i][j].imag;
      }
   }
   return conjugada;
}

/**
 * Calcula a hermitiana de uma Matriz de números complexos.
 * @param[in] matriz
 * @param[out] hermitiana
 */

 Matriz* hermitiana(Matriz* matriz){
   Matriz* hermi = transpos_matriz(matriz); 
   hermi = conjugada_matriz(hermi);
   return hermi;

}

/**
 * Calcula o produto escalar entre dois vetores de números complexos.
 * @param[in] v1 ///< Vetor 1.
 * @param[in] v2 ///< Vetor 2.
 * @param[in] n  ///< Tamanho do vetor.
 * @param[out] escalar 
 */

Complexo produto_escalar(Complexo* v1, Complexo* v2, int n) {
  Complexo escalar = {0.0, 0.0};
  for (int i = 0; i < n; i++) {
    Complexo term = {v1[i].real * v2[i].real - v1[i].imag * v2[i].imag,
                   v1[i].real * v2[i].imag + v1[i].imag * v2[i].real};
    escalar.real += term.real;
    escalar.imag += term.imag;
  }
  return escalar;
}

/**
 * Soma duas Matrizes de números complexos.
 * @param[in] matriz11
 * @param[in] matriz22
 * @param[out] soma
 */

Matriz *soma_matrizes(Matriz *matriz11, Matriz *matriz22) {
    if (matriz11->linhas != matriz22->linhas || matriz11->colunas != matriz22->colunas) {
        printf("Erro: as matrizes devem ter o mesmo n�mero de linhas e colunas.\n");
        return NULL;
    }

    Matriz *soma = criar_matriz(matriz11->colunas, matriz11->linhas);

    for (int i = 0; i < matriz11->linhas; i++) {
        for (int j = 0; j < matriz11->colunas; j++) {
            soma->dados[i][j].real = matriz11->dados[i][j].real + matriz22->dados[i][j].real;
            soma->dados[i][j].imag = matriz11->dados[i][j].imag + matriz22->dados[i][j].imag;
        }
    }

    return soma;
}

/**
 * Calcula a subtração de duas matrizes de números complexos.
 * @param[in] matriz33
 * @param[in] matriz44
 * @param[out] subtração
 */

Matriz *subtracao_matrizes(Matriz *matriz33, Matriz *matriz44) {
    if (matriz33->linhas != matriz44->linhas || matriz33->colunas != matriz44->colunas) {
        printf("Erro: as matrizes devem ter o mesmo n�mero de linhas e colunas.\n");
        return NULL;
    }

    Matriz *subtracao = criar_matriz(matriz33->colunas, matriz33->linhas);

    for (int i = 0; i < matriz33->linhas; i++) {
        for (int j = 0; j < matriz33->colunas; j++) {
            subtracao->dados[i][j].real = matriz33->dados[i][j].real - matriz44->dados[i][j].real;
            subtracao->dados[i][j].imag = matriz33->dados[i][j].imag - matriz44->dados[i][j].imag;
        }
    }

    return subtracao;
}


    //FUN��ES_TESTE



void teste_hermitiana(){
   Matriz* matriz = criar_matriz(3, 3);
  matriz->dados[0][0] = (Complexo){-2,9};
  matriz->dados[0][1] = (Complexo){8,2};
  matriz->dados[0][2] = (Complexo){1,7};
  matriz->dados[1][0] = (Complexo){7,-9};
  matriz->dados[1][1] = (Complexo){5,2};
  matriz->dados[1][2] = (Complexo){8,3};
  matriz->dados[2][0] = (Complexo){9,7};
  matriz->dados[2][1] = (Complexo){5,6};
  matriz->dados[2][2] = (Complexo){6,2};

  printf("Operando: A =\n");
   imprimir_matriz(matriz);


   Matriz* h = hermitiana(matriz);

   printf("\nResposta: R =\n");
   imprimir_matriz(h);




}


 void teste_transposta(){

 Matriz* matriz = criar_matriz(3, 3);
  matriz->dados[0][0] = (Complexo){-2,9};
  matriz->dados[0][1] = (Complexo){8,2};
  matriz->dados[0][2] = (Complexo){1,7};
  matriz->dados[1][0] = (Complexo){7,-9};
  matriz->dados[1][1] = (Complexo){5,2};
  matriz->dados[1][2] = (Complexo){8,3};
  matriz->dados[2][0] = (Complexo){9,7};
  matriz->dados[2][1] = (Complexo){5,6};
  matriz->dados[2][2] = (Complexo){6,2};



   printf("Operando: A =\n");
   imprimir_matriz(matriz);


   Matriz* transposta = transpos_matriz(matriz);

   printf("\nResposta: R =\n");
   imprimir_matriz(transposta);

 }



   void teste_produto_matricial(){

   Matriz* matriz1 = criar_matriz(3, 3);
     matriz1->dados[0][0] = (Complexo){1, 2};
     matriz1->dados[0][1] = (Complexo){3, 4};
     matriz1->dados[0][2] = (Complexo){1, 5};
     matriz1->dados[1][0] = (Complexo){5, 6};
     matriz1->dados[1][1] = (Complexo){7, 8};
     matriz1->dados[1][2] = (Complexo){9, 3};
     matriz1->dados[2][0] = (Complexo){8, 2};
     matriz1->dados[2][1] = (Complexo){7, 7};
     matriz1->dados[2][2] = (Complexo){3, 5};

   Matriz* matriz2 = criar_matriz(3, 3);
     matriz2->dados[0][0] = (Complexo){1, 2};
     matriz2->dados[0][1] = (Complexo){3, 4};
     matriz2->dados[0][2] = (Complexo){5, 6};
     matriz2->dados[1][0] = (Complexo){7, 8};
     matriz2->dados[1][1] = (Complexo){9, 10};
     matriz2->dados[1][2] = (Complexo){11, 12};
     matriz2->dados[2][0] = (Complexo){29, 2};
     matriz2->dados[2][1] = (Complexo){1, 1};
     matriz2->dados[2][2] = (Complexo){11, 89};

    printf("Operando: A =\n");
     imprimir_matriz(matriz1);

    printf("\nOperando: B =\n");
     imprimir_matriz(matriz2);


   Matriz* resultado = multiplicar_matrizes(matriz1, matriz2);

    printf("\nProduto Matricial AxB:\n");
   imprimir_matriz(resultado);
   }

void teste_conjugada(){

   Matriz* matriz = criar_matriz(3, 3);
  matriz->dados[0][0] = (Complexo){-2,9};
  matriz->dados[0][1] = (Complexo){8,2};
  matriz->dados[0][2] = (Complexo){1,7};
  matriz->dados[1][0] = (Complexo){7,-9};
  matriz->dados[1][1] = (Complexo){5,2};
  matriz->dados[1][2] = (Complexo){8,3};
  matriz->dados[2][0] = (Complexo){9,7};
  matriz->dados[2][1] = (Complexo){5,6};
  matriz->dados[2][2] = (Complexo){6,2};

    printf("Operando: A =\n");
   imprimir_matriz(matriz);


   Matriz* conjugada = conjugada_matriz(matriz);

   printf("\nResposta: R =\n");
    imprimir_matriz(conjugada);

}

void teste_produto_escalar(){
  Complexo v1[3] = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
  Complexo v2[3] = {{-1.0, 1.0}, {3.0, -2.0}, {2.0, -3.0}};
  int n = 3;

    printf("Operando: A = \n");
    print_vetor(v1, 3);
    printf("\nOperando: B = \n");
    print_vetor(v2, 3);

   Complexo escalar = produto_escalar(v1, v2, n);

    printf("\nResposta: R =\n");
    print_complexo(escalar);

}

void teste_soma(){
    Matriz* matriz11 = criar_matriz(3, 3);
     matriz11->dados[0][0] = (Complexo){1, 2};
     matriz11->dados[0][1] = (Complexo){3, 4};
     matriz11->dados[0][2] = (Complexo){1, 5};
     matriz11->dados[1][0] = (Complexo){5, 6};
     matriz11->dados[1][1] = (Complexo){7, 8};
     matriz11->dados[1][2] = (Complexo){9, 3};
     matriz11->dados[2][0] = (Complexo){8, 2};
     matriz11->dados[2][1] = (Complexo){7, 7};
     matriz11->dados[2][2] = (Complexo){3, 5};

   Matriz* matriz22 = criar_matriz(3, 3);
     matriz22->dados[0][0] = (Complexo){1, 2};
     matriz22->dados[0][1] = (Complexo){3, 4};
     matriz22->dados[0][2] = (Complexo){5, 6};
     matriz22->dados[1][0] = (Complexo){7, 8};
     matriz22->dados[1][1] = (Complexo){9, 10};
     matriz22->dados[1][2] = (Complexo){11, 12};
     matriz22->dados[2][0] = (Complexo){29, 2};
     matriz22->dados[2][1] = (Complexo){1, 1};
     matriz22->dados[2][2] = (Complexo){11, 89};

       printf("Operando: A =\n");
     imprimir_matriz(matriz11);

    printf("\nOperando: B =\n");
     imprimir_matriz(matriz22);

     Matriz *soma = soma_matrizes(matriz11, matriz22);

   printf("\nResposta: R =\n");
    imprimir_matriz(soma);

}

void teste_subtracao(){
    Matriz* matriz33 = criar_matriz(3, 3);
     matriz33->dados[0][0] = (Complexo){1, 2};
     matriz33->dados[0][1] = (Complexo){3, 4};
     matriz33->dados[0][2] = (Complexo){1, 5};
     matriz33->dados[1][0] = (Complexo){5, 6};
     matriz33->dados[1][1] = (Complexo){7, 8};
     matriz33->dados[1][2] = (Complexo){9, 3};
     matriz33->dados[2][0] = (Complexo){8, 2};
     matriz33->dados[2][1] = (Complexo){7, 7};
     matriz33->dados[2][2] = (Complexo){3, 5};

   Matriz* matriz44 = criar_matriz(3, 3);
     matriz44->dados[0][0] = (Complexo){1, 2};
     matriz44->dados[0][1] = (Complexo){3, 4};
     matriz44->dados[0][2] = (Complexo){5, 6};
     matriz44->dados[1][0] = (Complexo){7, 8};
     matriz44->dados[1][1] = (Complexo){9, 10};
     matriz44->dados[1][2] = (Complexo){11, 12};
     matriz44->dados[2][0] = (Complexo){29, 2};
     matriz44->dados[2][1] = (Complexo){1, 1};
     matriz44->dados[2][2] = (Complexo){11, 89};

       printf("Operando: A =\n");
     imprimir_matriz(matriz33);

    printf("\nOperando: B =\n");
     imprimir_matriz(matriz44);

     Matriz *subtracao = subtracao_matrizes(matriz33, matriz44);

   printf("\nResposta: R =\n");
    imprimir_matriz(subtracao);

}

/// Função que testa todas as funções implementadas.

void teste_todos(){

   printf("\n====Teste da opera��o Transposta====\n");
  teste_transposta();
    printf("\n====Teste da opra��o Conjugada====\n");
  teste_conjugada();
    printf("\n====Teste da opra��o Hermitiana====\n");
  teste_hermitiana();
    printf("\n====Teste da opera��o Produto Escalar====\n");
  teste_produto_escalar();
    printf("\n====Teste da opera��o Produto Matricial====\n");
  teste_produto_matricial();
    printf("\n====Teste da opera��o Soma====\n");
  teste_soma();
    printf("\n====Teste da opera��o Subtra��o====\n");
  teste_subtracao();

}
