#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Faturacao.h"

#define TAMCAT 12 /* numero de arvores do catalogo; 12 meses por Filial */
#define TAMMES 12
#define TAMPROD 26
typedef struct Venda{
  int qtdN;
  int qtdP;
  float precoN;
  float precoP;
/*  int filial;*/
} *venda;

typedef struct ListaVenda{
  BTree lista;
  int tamanho;
  int crescimento;
} *listavenda;

typedef struct ListaFaturacao{
    listavenda catalogo;
    int linhasLidas;
} *listafaturacao;

/*typedef struct facturacao *CatalogoFaturacao;*/

CatalogoFaturacao iniciaCatFaturacao(int nfiliais){
  int i, j, k;
  CatalogoFaturacao cat;
  cat = (CatalogoFaturacao)malloc(sizeof(struct ListaFaturacao));
  cat->catalogo = (listavenda)malloc(sizeof(struct ListaVenda) * (TAMCAT*nfiliais));
  cat->linhasLidas = 0;
  for (j=0; j<nfiliais; j++){
    for (i=0; i<TAMCAT; i++){
      k = (j * TAMCAT) + i;
      cat->catalogo[k].lista = NULL;
      cat->catalogo[k].tamanho = 0;
      cat->catalogo[k].crescimento = 0;
    }
  }
  return cat;
}

CatalogoFaturacao insereVenda(CatalogoFaturacao catFact, Produto p, int qtd, float preco, int mes, char tipo, int filial){
  int i;
  venda vd;
  char* var;
  i=((filial-1)*TAMCAT)+(mes-1);
  if ((vd=(venda)retornaDados(catFact->catalogo[i].lista, p))!=NULL){
    if (tipo == 'N'){
      vd->qtdN += qtd;
    }
    else{
      vd->qtdP += qtd;
    }
  }
  else {
    vd = (venda)malloc(sizeof(struct Venda));
    var = (char*)malloc(sizeof(char) * (strlen(p)+1));
    strcpy(var, p);
    if (tipo == 'N'){
      vd->qtdN = qtd;
      vd->precoN = preco;
      vd->qtdP = 0;
      vd->precoP = 0;
    }
    else{
      vd->qtdP = qtd;
      vd->precoP = preco;
      vd->qtdN = 0;
      vd->precoN = 0;
    }
    catFact->catalogo[i].lista = insertAVL(catFact->catalogo[i].lista, var, &catFact->catalogo[i].crescimento, vd);
    catFact->catalogo[i].tamanho++;
  }
  catFact->linhasLidas++;
  return catFact;
}

int totalProdutosVenda(CatalogoFaturacao catFact, int mes, int filial){
  int i;
  i = ((filial-1)*TAMCAT)+(mes-1);
  return catFact->catalogo[i].tamanho;
}
/*
void retornaCoisas(CatalogoFaturacao cat, char *produto, int mes, int filial){
    ppVenda pp;
    int i;
    i= ((filial-1)*TAMCAT) + mes - 1;
    pp = (ppVenda) retornaDados (cat->catalogo[i].lista, produto);
    if (pp)
      printf("QuantidadeN: %d. PreçoN: %0.2f.\nQuantidadeP: %d. PreçoP: %0.2f.\n", pp->qtdN, pp->precoN, pp->qtdP, pp->precoP);
    else
      printf("Não existem dados.\n"); 
}
*/
Boolean existeVenda(CatalogoFaturacao catFact, Produto p, int filial, int mes){
  Boolean b = FALSE;
  int i;
  if (verificaAlpha(p[0]))
    i = ((filial-1)*TAMCAT)+(mes-1);
    if (exists(catFact->catalogo[i].lista, p))
      b = TRUE;
  return b;
}

void removeCatFaturacao(CatalogoFaturacao catFact, int filiais){
  int i, j;
  j = TAMCAT * filiais;
  for (i=0; i<j; i++){
    deleteAvl(catFact->catalogo[i].lista);
  }
  free(catFact->catalogo);
  free(catFact);
}

int totalVendas(CatalogoFaturacao catFact){
  return catFact->linhasLidas;
}

