#include <stdlib.h>
#include "API-Produtos.h"
#include "API-Faturacao.h"

#define FMTAM 12
#define FCTAM 26
#define MINCLIENTE 1000
#define MAXCLIENTE 5000
#define MINPRODUTO 1000
#define MAXPRODUTO 1999

typedef struct ListaFaturacao{/*lista de clientes*/
  CatalogoProdutos catMes[FMTAM];
  int vendasValidas[FMTAM];
} lf1;
	
typedef struct Venda{
  int qtdN;
  float precoN;
  int qtdP;
  float precoP;
  } *venda;

venda insereVenda(venda v, int qtd, float preco, char tipo){
  if (v!=NULL){
    if (tipo == 'N')
      v->qtdN += qtd;
    else
      v->qtdP += qtd;
    return v;
  }
  else {
    venda aux;
    aux = (venda)malloc(sizeof(struct Venda));
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

CatalogoFaturacao iniciaCatFaturacao(CatalogoProdutos catProd, int nfiliais){
  int i, j;
  CatalogoFaturacao catFact = malloc(sizeof(struct ListaFaturacao)*nfiliais);
  for (i=0;i<nfiliais;i++){
    for (j = 0; j<FMTAM; j++){
      catFact[i].catMes[j] = copiaCatProdutos(catProd);
      catFact[i].vendasValidas[j] = 0;
    }
  }
  return catFact;
}

CatalogoFaturacao insereCompraFaturacao(CatalogoFaturacao catFact, Produto p, int qtd, float preco, int mes, char tipo, int filial){
  int i, j;
  venda vd;
  i = filial-1;
  j = mes - 1;
    
  if ((vd=(venda)retornaDadosProduto(catFact[i].catMes[j], p)) == NULL){
    vd = insereVenda(vd, qtd, preco, tipo);
    insereDadosProduto(catFact[i].catMes[j], p, vd);
  }
  else{
    vd = insereVenda(vd, qtd, preco, tipo);
  }

  catFact[i].vendasValidas[j]++;
  return catFact;
}

void removeCatFaturacao(CatalogoFaturacao catFact, int nfiliais){
  int i,j;
  for (i=0; i<nfiliais; i++){
    for (j=0; j<FMTAM; j++){
          removeCatProdutos(catFact[i].catMes[j]);
    }
  }
  free(catFact);
}

int totalVendas(CatalogoFaturacao catFact, int nfiliais){
  int i,j,total;
  total=0;
  for (i=0; i<nfiliais; i++){
    for (j=0; j<FMTAM; j++){
      total += catFact[i].vendasValidas[j];
    }
  }
  return total;
}

