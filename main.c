#include <stdio.h>
#include <stdlib.h>
#include "avl-strings.h"
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
    while (fgets(buffer, 20, fichClientes)!=NULL){
      teste = insereCliente(teste, buffer);
    }
  }

  fichProdutos = fopen("fichTeste/Produtos.txt", "r");
  if (fichProdutos != NULL){
    while (fgets(buffer, 20, fichProdutos)!=NULL){
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
  
  return 0;
}
