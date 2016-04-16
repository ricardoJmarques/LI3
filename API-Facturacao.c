#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Facturacao.h"
#include "API-Clientes.h"
#include "API-Produtos.h"

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
    catVenda catalogo;
    int erroClientes;
    int erroProdutos;
    int linhasLidas;
} *listafaturacao;

/*typedef struct facturacao *catFacturacao;*/

catFacturacao iniciaCatFacturacao(int nfiliais){
  int i, j, k;
  catFacturacao cat;
  cat = (catFacturacao)malloc(sizeof(struct facturacao));
  cat->catalogo = (catVenda)malloc(sizeof(struct venda) * (TAMCAT*nfiliais));
  cat->erroClientes = 0;
  cat->erroProdutos = 0;
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

catFacturacao insereVenda(catFacturacao cat, catClientes cli, catProdutos pro, char *venda){
  int i;
  char v[7][7]; /*char produtoID[7];char preço[7];char qtd[4];char PN[2];char cliente[6];char MES[3];char Filial[2];*/
  char *var;
  ppVenda pp;
  Boolean a;
  Boolean b;
  i=0;
  var = strtok(venda, " ");
  strcpy(v[i] , var);
  while ((var = strtok(NULL, " ")) != NULL){ 
    i++;
    strcpy(v[i] , var);
  }
  i = ((atoi(v[6])-1) * TAMCAT) + (atoi(v[5]) - 1 );
  /* teste variaveis */
  a = existeProduto(pro, v[0]);
  b = existeCliente(cli, v[4]);
  if (!a || !b){
    if (!a) cat->erroProdutos++;
    else cat->erroClientes++;
  }
  else {
    if ((pp=(ppVenda)retornaDados(cat->catalogo[i].lista, v[0]))!=NULL){
      if (v[3][0] == 'N'){
        pp->qtdN += atoi(v[2]);
      }
      else{
        pp->qtdP += atoi(v[2]);
      }
    }
    else {
      pp = (ppVenda)malloc(sizeof(struct prodVenda));
      var = (char*)malloc(sizeof(char) * (strlen(v[0]) +1));
      strcpy(var, v[0]);
      if (v[3][0] == 'N'){
        pp->qtdN = atoi(v[2]);
        pp->precoN = atof(v[1]);
        pp->qtdP = 0;
        pp->precoP = 0;
      }
      else{
        pp->qtdP = atoi(v[2]);
        pp->precoP = atof(v[1]);
        pp->qtdN = 0;
        pp->precoN = 0;
      }
      cat->catalogo[i].lista = insertAVL(cat->catalogo[i].lista, var, &cat->catalogo[i].crescimento, pp);
      cat->catalogo[i].tamanho++;
    }
    cat->linhasLidas++;
  }
  return cat;
}

int totalProdutosVenda(catFacturacao cat, int mes, int filial){
  int i;
  i = ((filial-1)*TAMCAT)+(mes-1);
  return cat->catalogo[i].tamanho;
}
/*
void retornaCoisas(catFacturacao cat, char *produto, int mes, int filial){
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
Boolean existeVenda(catFacturacao cat, char *produto, int filial, int mes){
  Boolean b = FALSE;
  int i;
  if (verificaAlpha(produto[0]))
    i = ((filial-1)*TAMCAT)+(mes-1);
    if (exists(cat->catalogo[i].lista, produto))
      b = TRUE;
  return b;
}

void removeCatFacturacao(catFacturacao fact, int filiais){
  int i, j;
  j = TAMCAT * filiais;
  for (i=0; i<j; i++){
    deleteAvl(fact->catalogo[i].lista);
  }
  free(fact->catalogo);
  free(fact);
}

int totalVendas(catFacturacao cat){
  return cat->linhasLidas;
}

