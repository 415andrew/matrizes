///@file matrizes.h

#ifndef MATRIZES_H_INCLUDED
#define MATRIZES_H_INCLUDED

/** 
 * Estrutura de dados que armazena números complexos, que tem parte real e imaginaria.
*/
 
typedef struct complexo {
   double real;  ///< Parte real do número complexo.
   double imag;  ///< Parte imaginaria do número complexo.
} Complexo;

/// Estrutura de dados que armazena uma Matriz, as variáveis linhas​​ e colunas armazenam o número de linhas e colunas da matriz, respectivamente, e dados é um ponteiro para um ponteiro de complexo.
typedef struct matriz {
   int linhas;   ///< Número de linhas da Matriz.
   int colunas;  ///< Número de colunas da Matriz.
   Complexo **dados; 
   double **dados1;
} Matriz;




Matriz* transpos_matriz(Matriz* matriz);

Matriz* multiplicar_matrizes(Matriz* matriz1, Matriz* matriz2);

Matriz* conjugada_matriz(Matriz* matriz);

Matriz* hermitiana_matriz(Matriz* matriz);

Complexo produto_escalar(Complexo* v1, Complexo* v2, int n);

Matriz *soma_matrizes(Matriz *matriz11, Matriz *matriz22);

Matriz *subtracao_matrizes(Matriz *matriz33, Matriz *matriz44);

Matriz* criar_matriz(int n, int m);

void teste_todos();

#endif // MATRIZES_H_INCLUDED
