#include <stdio.h>
#include <stdlib.h>
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Faturacao.h"
#include "API-Filiais.h"

#define nfiliais 3

int main(){
  FILE *fichClientes;
  FILE *fichProdutos;
  FILE *fichVendas;
  
  CatalogoClientes teste;
  CatalogoProdutos teste2;
  CatalogoFaturacao teste3;
  CatalogoFilial teste4;
  char buffer[41];

  teste = iniciaCatClientes();
  teste2 = iniciaCatProdutos();
  teste3 = iniciaCatFaturacao(nfiliais);
  teste4 = iniciaCatFilial(nfiliais); 
  
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
      teste4 = insereCompra(teste4, teste, teste2, strtok(buffer, "\r\n"));
    }
  }
  
  fclose(fichClientes);
  fclose(fichProdutos);
  fclose(fichVendas); 

  printf("Total de Clientes: %d.\n", totalClientes(teste));
  printf("Total de Produtos: %d.\n", totalProdutos(teste2));
  removeCatClientes(teste);
  removeCatProdutos(teste2);
  removeCatFaturacao(teste3, nfiliais);
  removeCatFilial(teste4, nfiliais);

  return 0;
}
