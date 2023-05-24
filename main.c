///@file main.c
#include <stdio.h> ///informa ao main as variáveis pertencentes ao head do stdio
#include <stdlib.h> ///informa ao main as variáveis pertencentes ao head do stdlib
#include "matrizes.h" ///informa ao main as variáveis pertencentes ao head do matrizes
#include <locale.h> ///informa ao main as variáveis pertencentes ao head do locale

/// Função Principal do Projeto.
int main(){

    setlocale(LC_ALL,"Portuguese"); ///configura a lingua para português

   printf("====EQUIPE====\n"); ///mostra nome de equipe
   printf("Luis Carlos de Souza Pereira\n"); ///mostra primeiro componente da equipe
   printf("Andrew Borges Pinheiro\n"); ///mostra segundo componente da equipe
   printf("Luan Matheus Silva dos Anjos\n"); ///mostra o terceiro componente da equipe
   printf("Thiago Ferreira da Silva\n"); ///mostra o quarto integrante da equipe
    /// Função teste_todos.
    /// Essa função mostra todos os testes feitos na matrizes.c .
   teste_todos(); 
   
  return 0;

}
