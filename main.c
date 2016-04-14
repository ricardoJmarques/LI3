#include <stdio.h>
#include <stdlib.h>
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Facturacao.h"

int main(){
  FILE *fichClientes;
  FILE *fichProdutos;
  FILE *fichVendas;
  int i;
  catClientes teste;
  catProdutos teste2;
  catFacturacao teste3;
  char buffer[41];

  int errosproduto = 0;
  int erroscliente = 0;
  int vendasValidas = 0;

  teste = iniciaCatClientes();
  teste2 = iniciaCatProdutos();
  teste3 = iniciaCatFacturacao();
  
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
      teste3 = insereVenda(teste3, teste, teste2, strtok(buffer, "\r\n"), &erroscliente, &errosproduto, &vendasValidas);
    }
  }
  
  fclose(fichClientes);
  fclose(fichProdutos);
  fclose(fichVendas);

  printf("Total de Clientes: %d.\n", totalClientes(teste));
  printf("Total de Produtos: %d.\n", totalProdutos(teste2));
  printf("Erros de cliente: %d\n", erroscliente);
  printf("Erros de produto: %d\n", errosproduto);
  printf("Vendas Validas: %d\n", vendasValidas);
 
  removeCatClientes(teste);
  removeCatProdutos(teste2);
  removeCatFacturacao(teste3, 3);
 
  return 0;
}
