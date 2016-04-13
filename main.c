#include <stdio.h>
#include <stdlib.h>
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Facturacao.h"

int main(){
  FILE *fichClientes;
  FILE *fichProdutos;
  int i;
  catClientes teste;
  catProdutos teste2;
  catFacturacao teste3;
  char buffer[21];

  teste = iniciaCatClientes();
  teste2 = iniciaCatProdutos();
  teste3 = iniciaCatFacturacao();
  
  fichClientes = fopen("fichTeste/Clientes.txt", "r");
  if (fichClientes != NULL){
    while (fgets(buffer, 20, fichClientes)!=NULL){
      teste = insereCliente(teste, strtok(buffer, "\r\n"));
    }
  }

  fichProdutos = fopen("fichTeste/Produtos.txt", "r");
  if (fichProdutos != NULL){
    while (fgets(buffer, 20, fichProdutos)!=NULL){
      teste2 = insereProduto(teste2, strtok(buffer, "\r\n"));
    }
  }
  
  char v1[] = "OP1244 481.43 67 P Q3869 9 1";
  char v2[] = "GK1523 344.51 146 N U3261 11 2";
  char v3[] = "XU1314 332.11 160 P Y1793 7 2";
  
  teste3 = insereVenda(teste3, v1);
  teste3 = insereVenda(teste3, v2);
  teste3 = insereVenda(teste3, v3);
  
  fclose(fichClientes);
  fclose(fichProdutos);

  printf("Total de Clientes: %d.\n", totalClientes(teste));
  printf("Total de Produtos: %d.\n", totalProdutos(teste2));
  int abc;
  char cvb;
  cvb = 'N';
  for (i=0; i<2; i++){
    for (abc=0; abc<12; abc++)
      printf("Total de produtos %c venda mes %d: %d.\n", cvb, (abc+1), totalProdutosVenda(teste3, abc+1,cvb));
    cvb = 'P';
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
