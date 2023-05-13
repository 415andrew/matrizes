#ifndef MATRIZES_H_INCLUDED
#define MATRIZES_H_INCLUDED

typedef struct complexo {
   double real;
   double imag;
} Complexo;

typedef struct matriz {
   int linhas;
   int colunas;
   Complexo **dados;
} Matriz;

Matriz* criar_matriz(int n, int m);

 void teste_todos();

//ASSINATURA DAS FUN��ES

Matriz* transpos_matriz(Matriz* matriz);

Matriz* multiplicar_matrizes(Matriz* matriz1, Matriz* matriz2);

Matriz* conjugada_matriz(Matriz* matriz);

Matriz* hermitiana_matriz(Matriz* matriz);

Complexo produto_escalar(Complexo* v1, Complexo* v2, int n);

Matriz *soma_matrizes(Matriz *matriz11, Matriz *matriz22);

Matriz *subtracao_matrizes(Matriz *matriz33, Matriz *matriz44);


#endif // MATRIZES_H_INCLUDED
