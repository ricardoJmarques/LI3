#include <stdio.h>
#include <stdlib.h>
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Filiais.h"

/*#include "API-Facturacao.h"*/

#define nfiliais 3

int main(){
  FILE *fichClientes;
  FILE *fichProdutos;
/*  FILE *fichVendas; */
  
  CatalogoClientes teste;
  CatalogoProdutos teste2;
/*  catFacturacao teste3; */
  CatalogoFilial teste4;
  char buffer[41];

  teste = iniciaCatClientes();
  teste2 = iniciaCatProdutos();
/*  teste3 = iniciaCatFacturacao(nfiliais);*/
  
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
/*
  fichVendas = fopen("fichTeste/Vendas_1M.txt", "r");
  if (fichVendas != NULL){
    while (fgets(buffer, 40, fichVendas)!=NULL){
      teste3 = insereVenda(teste3, teste, teste2, strtok(buffer, "\r\n"));
    }
  }
*/
  teste4 = iniciaCatFilial(teste);


  /* KR1583 77.72 128 P L4891 2 1 */
  char *c = "L4891";
  char *p = "KR1583";

  teste4 = insereVendaFilial(teste4, c, p, 128, 77.72, 2, 'P');
  teste4 = insereVendaFilial(teste4, c, p, 64, 75.72, 2, 'N');
  
  fclose(fichClientes);
  fclose(fichProdutos);
/*  fclose(fichVendas); */

  printf("Total de Clientes: %d.\n", totalClientes(teste));
  printf("Total de Produtos: %d.\n", totalProdutos(teste2));
/*  printf("Total de Vendas: %d.\n", totalVendas(teste3)); */

  removeCatClientes(teste); 
  removeCatProdutos(teste2);
/*  removeCatFacturacao(teste3, 3); */
  removeCatFilial(teste4);
  
  return 0;
}
