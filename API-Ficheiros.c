#include <stdio.h>
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Faturacao.h"
#include "API-Filiais.h"

CatalogoClientes abreFicheiroClientes(CatalogoClientes catCli){/*int argc, char *argv[]){*/
  FILE *fichClientes;
  char buffer[41];
  fichClientes = fopen("fichTeste/Clientes.txt", "r");
  if (fichClientes != NULL){
    while (fgets(buffer, 40, fichClientes)!=NULL){
      catCli = insereCliente(catCli, strtok(buffer, "\r\n"));
    }
  }
  fclose(fichClientes);
  return catCli;
}


CatalogoProdutos abreFicheiroProdutos(CatalogoProdutos catProd){/*int argc, char *argv[]){*/
  FILE *fichProdutos;
  char buffer[41];
  fichProdutos = fopen("fichTeste/Produtos.txt", "r");
  if (fichProdutos != NULL){
    while (fgets(buffer, 40, fichProdutos)!=NULL){
      catProd = insereProduto(catProd, strtok(buffer, "\r\n"));
    }
  }
  fclose(fichProdutos);
  return catProd;
}

/*char v[7][7];
  char produtoID[7];
  char preço[7];
  char qtd[4];
  char PN[2];
  char cliente[6];
  char MES[3];
  char Filial[2];*/
void abreFicheiroVendas(CatalogoFaturacao catFact, CatalogoFilial catFil, CatalogoClientes catCli, CatalogoProdutos catProd){
  FILE *fichVendas;
  char buffer[41];
  int i;
  char *var;
  char v[7][7];
  float preco;
  int qtd;
  char tipo;
  int mes;
  int filial;

  fichVendas = fopen("fichTeste/Vendas_20E.txt", "r");
  if (fichVendas != NULL){
    while (fgets(buffer, 40, fichVendas)!=NULL){
      i=0;
      var = strtok(buffer, " ");
      strcpy(v[i] , var);
      while ((var = strtok(NULL, " ")) != NULL){ 
        i++;
        strcpy(v[i] , var);
      }
      preco = atof(v[1]);
      qtd = atoi(v[2]);
      tipo = v[3][0];
      mes = atoi(v[5]);
      filial = atoi(v[6]);
      if (existeProduto(catProd, v[0]) && existeCliente(catCli, v[4]) &&
          (preco >= 0.0 && preco <= 999.99) && (qtd >=1 && qtd <= 200) &&
          (tipo == 'N' || tipo == 'P') && (mes >=1 && mes <=12) &&
          (filial >= 1 && filial <=3)){
        
        catFact = insereVenda(catFact, v[0], qtd, preco, mes, tipo, filial);
        catFil = insereVendaFilial(catFil, v[4], v[0], qtd, preco, mes, tipo, filial);
      }
    }
  }
  fclose(fichVendas);
}
