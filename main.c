///@file main.c
#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"
#include <locale.h>

/// Função Principal do Projeto.
int main(){

    setlocale(LC_ALL,"Portuguese");

   printf("====EQUIPE====\n");
   printf("Luis Carlos de Souza Pereira\n");
   printf("Andrew Borges Pinheiro\n");
   printf("Luan Matheus Silva dos Anjos\n");
   printf("Thiago Ferreira da Silva\n");

    /// Função teste_todos.
    /// Essa função mostra todos os testes feitos na matrizes.c .
   teste_todos(); 

  return 0;
  
}
