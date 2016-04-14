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
      teste3 = insereVenda(teste3, teste, teste2, strtok(buffer, "\r\n"));
    }
  }
  
  fclose(fichClientes);
  fclose(fichProdutos);
  fclose(fichVendas	);

  printf("Total de Clientes: %d.\n", totalClientes(teste));
  printf("Total de Produtos: %d.\n", totalProdutos(teste2));
  int abc;
  
  for (i=0; i<3; i++){
    for (abc=0; abc<12; abc++)
      printf("Total de produtos %d venda mes %d: %d.\n", i+1, abc+1, totalProdutosVenda(teste3, abc+1,i+1));
  }



/*
  for (i=0; i<26; i++){
    printf("Total de Clientes letra %c: %d.\n", (char)('A'+i), totalClientesLetra(teste, (char)('A'+i)));
  }
  for (i=0; i<26; i++){
    printf("Total de Produtos letra %c: %d.\n", (char)('A'+i), totalProdutosLetra(teste2, (char)('A'+i)));
  }
*/
  char c1[] = "A2129";
  char c2[] = "A4310"; /* not */
  char p1[] = "AF1198";
  char p2[] = "GG1046"; /* not */
  char p3[] = "OP1244";
  
  printf("Existe %s.\n", existeProduto2(teste2, p1));
  
  retornaCoisas(teste3, p3, 9, 'P');
  
  if (existeCliente(teste, c1))
    printf("Cliente %s existe.\n", c1);
  else
    printf("Cliente %s não existe.\n", c1);
  
  
  if (existeProduto(teste2, p1)==TRUE)
    printf("Produto %s existe.\n", p1);
  else
    printf("Produto %s não existe.\n", p1);
 
  removeCatClientes(teste);
  removeCatProdutos(teste2);
 
  return 0;
}
