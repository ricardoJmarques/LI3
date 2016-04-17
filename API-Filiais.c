#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Filiais.h"

#define TAMCAT 12 /* numero de arvores do catalogo; 12 meses por Filial */
#define TAMCLI 26
typedef struct Compra{
  int qtdN;
  int qtdP;
  float precoN;
  float precoP;
/*  int filial;*/
} *compra;

typedef struct ListaCompra{
  BTree lista;
  int tamanho;
  int crescimento;
} *listacompra;

typedef struct ListaFilial{
    listacompra catalogo;
    int erroClientes;
    int erroProdutos;
    int linhasLidas;
} *listafilial;

/*typedef struct ListaFilial *CatalogoFilial;*/

CatalogoFilial iniciaCatFilial(int nfiliais){
  int i, j, k;
  CatalogoFilial catFil;
  catFil = (CatalogoFilial)malloc(sizeof(struct ListaFilial));
  catFil->catalogo = (listacompra)malloc(sizeof(struct ListaCompra) * (TAMCAT*nfiliais));
  catFil->erroClientes = 0;
  catFil->erroProdutos = 0;
  catFil->linhasLidas = 0;
  for (j=0; j<nfiliais; j++){
    for (i=0; i<TAMCAT; i++){
      k = (j * TAMCAT) + i;
      catFil->catalogo[k].lista = NULL;
      catFil->catalogo[k].tamanho = 0;
      catFil->catalogo[k].crescimento = 0;
    }
  }
  return catFil;
}

CatalogoFilial insereCompra(CatalogoFilial catFil, CatalogoClientes catCli, CatalogoProdutos catProd, char *venda){
  int i;
  char v[7][7]; /*char produtoID[7];char preço[7];char qtd[4];char PN[2];char cliente[6];char MES[3];char Filial[2];*/
  char *var;
  compra cp;
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
  a = existeProduto(catProd, v[0]);
  b = existeCliente(catCli, v[4]);
  if (!a || !b){
    if (!a) catFil->erroProdutos++;
    else catFil->erroClientes++;
  }
  else {
    if ((cp=(compra)retornaDados(catFil->catalogo[i].lista, v[0]))!=NULL){
      if (v[3][0] == 'N'){
        cp->qtdN += atoi(v[2]);
      }
      else{
        cp->qtdP += atoi(v[2]);
      }
    }
    else {
      cp = (compra)malloc(sizeof(struct Compra));
      var = (char*)malloc(sizeof(char) * (strlen(v[0]) +1));
      strcpy(var, v[0]);
      if (v[3][0] == 'N'){
        cp->qtdN = atoi(v[2]);
        cp->precoN = atof(v[1]);
        cp->qtdP = 0;
        cp->precoP = 0;
      }
      else{
        cp->qtdP = atoi(v[2]);
        cp->precoP = atof(v[1]);
        cp->qtdN = 0;
        cp->precoN = 0;
      }
      catFil->catalogo[i].lista = insertAVL(catFil->catalogo[i].lista, var, &catFil->catalogo[i].crescimento, cp);
      catFil->catalogo[i].tamanho++;
    }
    catFil->linhasLidas++;
  }
  return catFil;
}

int totalProdutosCompra(CatalogoFilial catFil, int mes, int filial){
  int i;
  i = ((filial-1)*TAMCAT)+(mes-1);
  return catFil->catalogo[i].tamanho;
}
/*
void retornaCoisas(CatalogoFilial cat, char *produto, int mes, int filial){
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
Boolean existeCompra(CatalogoFilial catFil, Produto p, int filial, int mes){
  Boolean b = FALSE;
  int i;
  if (verificaAlpha(p[0]))
    i = ((filial-1)*TAMCAT)+(mes-1);
    if (exists(catFil->catalogo[i].lista, p))
      b = TRUE;
  return b;
}

void removeCatFilial(CatalogoFilial catFil, int nfiliais){
  int i, j;
  j = TAMCAT * nfiliais;
  for (i=0; i<j; i++){
    deleteAvl(catFil->catalogo[i].lista);
  }
  free(catFil->catalogo);
  free(catFil);
}

int totalCompras(CatalogoFilial catFil){
  return catFil->linhasLidas;
}

