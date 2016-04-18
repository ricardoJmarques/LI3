#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Filiais.h"

#define FMTAM 12
#define FCTAM 26
#define MINCLIENTE 1000
#define MAXCLIENTE 5000
#define MINPRODUTO 1000
#define MAXPRODUTO 1999

typedef struct ListaFilial{/*lista de clientes*/
  CatalogoClientes catMes[FMTAM];
  int comprasvalidas[FMTAM];
} lf1;
	
typedef struct Compra{
  int qtdN;
  float precoN;
  int qtdP;
  float precoP;
  } *compra;

compra insereCompra(compra c, int qtd, float preco, char tipo){
  if (c!=NULL){
    if (tipo == 'N'){
      c->qtdN += qtd;
      c->precoN += preco;
    }
    else{
      c->qtdP += qtd;
      c->precoP += preco;
    }
    return c;
  }
  else {
    compra aux;
    aux = (compra)malloc(sizeof(struct Compra));
    if (tipo == 'N'){
      aux->qtdN = qtd;
      aux->precoN = preco;
      aux->qtdP = 0;
      aux->precoP = 0;
    }
    else{
      aux->qtdP = qtd;
      aux->precoP = preco;
      aux->qtdN = 0;
      aux->precoN = 0;
    }
    return aux;
  }
}

CatalogoFilial iniciaCatFilial(CatalogoClientes catCli, int nfiliais){
  int i, j;
  CatalogoFilial catFil = malloc(sizeof(struct ListaFilial)*nfiliais);
  for (i=0;i<nfiliais;i++){
    for (j = 0; j<FMTAM; j++){
      catFil[i].catMes[j] = copiaCatClientes(catCli);
    }
  }
  return catFil;
}

CatalogoFilial insereVendaFilial(CatalogoFilial catFil, Cliente c, Produto p, int qtd, float preco, int mes, char tipo, int filial){
  int i, j;
  CatalogoProdutos catProd;
  compra cp;
  i = filial-1;
  j = mes - 1;
    
  if ((catProd=(CatalogoProdutos)retornaDadosCliente(catFil[i].catMes[j], c)) == NULL){
    catProd = iniciaCatProdutos();
    insereDadosCliente(catFil[i].catMes[j], c, catProd);
    insereProduto(catProd, p);
  }

  if ((cp=(compra)retornaDadosProduto(catProd, p)) == NULL){
    cp = insereCompra(cp, qtd, preco, tipo);
    insereDadosProduto(catProd, p, cp);
  }
  else
    cp = insereCompra(cp, qtd, preco, tipo);

  catFil[i].comprasvalidas[j]++;
  return catFil;
}

void removeCatFilial(CatalogoFilial catFil, int nfiliais){
  int i,j,k,l;
  char c;
  char ch[10];
  CatalogoProdutos catProd;
  CatalogoClientes catCli;
  for (i=0; i<nfiliais; i++){
    for (j=0; j<FMTAM; j++){
      c = 'A';
      for (k=0; k<FCTAM; k++){
        for (l=MINCLIENTE; l<=MAXCLIENTE; l++){
          sprintf(ch,"%c%d",c , l);
          if ((catProd = (CatalogoProdutos)retornaDadosCliente(catFil[i].catMes[j], ch)) != NULL){
          removeCatProdutos(catProd);
          }
        }
      c++;
      }
    removeCatClientes(catFil[i].catMes[j]);
    }
  }
  free(catFil);
}

