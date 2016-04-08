#include <stdio.h>
#include <stdlib.h>
#include "API-Clientes.h"
#include "API-Produtos.h"

int main(){
  FILE *fichClientes;
  FILE *fichProdutos;
  int i;
  catClientes teste;
  catProdutos teste2;
  char buffer[21];

  teste = iniciaCatClientes();
  teste2 = iniciaCatProdutos();

  fichClientes = fopen("fichTeste/Clientes.txt", "r");
  if (fichClientes != NULL){
    while (fgets(buffer, 6, fichClientes)!=NULL){
      teste = insereCliente(teste, buffer);
    }
  }

  fichProdutos = fopen("fichTeste/Produtos.txt", "r");
  if (fichProdutos != NULL){
    while (fgets(buffer, 7, fichProdutos)!=NULL){
      teste2 = insereProduto(teste2, buffer);
    }
  }

/*
  for (i=0; i<26; i++){
    printf("Total de Clientes letra %c: %d.\n", (char)('A'+i), totalClientesLetra(teste, (char)('A'+i)));
  }
  for (i=0; i<26; i++){
    printf("Total de Produtos letra %c: %d.\n", (char)('A'+i), totalProdutosLetra(teste2, (char)('A'+i)));
  }
*/
  printf("Total de Clientes: %d.\n", totalClientes(teste));
  printf("Total de Produtos: %d.\n", totalProdutos(teste2));
  
  char c1[] = "A2129";
  char c2[] = "A4310"; /* not */
  char p1[] = "AF1198";
  char p2[] = "GG1046"; /* not */
  
  if (existeCliente(teste, c1))
    printf("Cliente %s existe.\n", c1);
  else
    printf("Cliente %s não existe.\n", c1);
  
  
  if (existeProduto(teste2, p1)==TRUE)
    printf("Produto %s existe.\n", p1);
  else
    printf("Produto %s não existe.\n", p1);
  
  return 0;
}
