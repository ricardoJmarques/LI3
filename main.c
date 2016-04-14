#include <stdio.h>
#include <stdlib.h>
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Facturacao.h"

#define nfiliais 3

int main(){
  FILE *fichClientes;
  FILE *fichProdutos;
  FILE *fichVendas;
  
  /*int i;*/
  
  catClientes teste;
  catProdutos teste2;
  catFacturacao teste3;
  char buffer[41];

  teste = iniciaCatClientes();
  teste2 = iniciaCatProdutos();
  teste3 = iniciaCatFacturacao(nfiliais);
  
  fichClientes = fopen("fichTeste/Clientes.txt", "r");
  if (fichClientes != NULL){
    while (fgets(buffer, 40, fichClientes)!=NULL){
      teste = insereCliente(teste, strtok(buffer, "\r\n"));
    }
  }

  fichProdutos = fopen("fichTeste/Produtos.txt", "r");
  if (fichProdutos != NULL){
    while (fgets(buffer, 40, fichProdutos)!=NULL){
      teste2 = insereProduto(teste2, strtok(buffer, "\r\n"));
    }
  }

  fichVendas = fopen("fichTeste/Vendas_1M.txt", "r");
  if (fichVendas != NULL){
    while (fgets(buffer, 40, fichVendas)!=NULL){
      teste3 = insereVenda(teste3, teste, teste2, strtok(buffer, "\r\n"));
    }
  }
  
  fclose(fichClientes);
  fclose(fichProdutos);
  fclose(fichVendas);

  printf("Total de Clientes: %d.\n", totalClientes(teste));
  printf("Total de Produtos: %d.\n", totalProdutos(teste2));
  printf("Total de Vendas: %d.\n", totalVendas(teste3));

/* DB1519 953.23 98 N U3353 5 2 */
  char *ale = "DB1519"; /* 13 */
  
  retornaCoisas(teste3, ale, 5, 2);
  
  if (existeVenda(teste3, ale, 2, 5) == TRUE)
    retornaCoisas(teste3, ale, 5, 2);
  else
    printf("tou fodido pah!\n");
  

 
  removeCatClientes(teste);
  removeCatProdutos(teste2);
  removeCatFacturacao(teste3, 3);
 
  return 0;
}
