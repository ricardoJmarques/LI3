#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Produtos.h"

#define TAMCAT 26 /* numero de arvores do catalogo */
#define MINP 1000
#define MAXP 1999

/* listaLetra é uma AVL onde constam os   */
/* clientes iniciados por determinada letra */
typedef struct ListaProdutos{
  BTree lista;
  int tamanho;
  int crescimento;
} listap;

/* tipo Produto */
/*typedef char* Produto;*/

/* catalogo de Produtos */
/*typedef struct ListaProdutos *CatalogoProdutos;*/

CatalogoProdutos iniciaCatProdutos(){
  int i;
  /* criar array de 26 listaProdutos */
  CatalogoProdutos catProd = (CatalogoProdutos)malloc(sizeof(struct ListaProdutos) * TAMCAT);
  for (i=0; i<TAMCAT; i++){
    catProd[i].lista = NULL;
    catProd[i].tamanho = 0;
    catProd[i].crescimento = 0;
  }
  return catProd;
}

CatalogoProdutos copiaCatProdutos(CatalogoProdutos catProd){
  int i;
  CatalogoProdutos cp = (CatalogoProdutos)malloc(sizeof(struct ListaProdutos) * TAMCAT);
  for (i=0; i<TAMCAT; i++){
    cp[i].lista = avlCopy(catProd[i].lista);
    cp[i].tamanho = catProd[i].tamanho;
    cp[i].crescimento = catProd[i].crescimento;
  }
  return cp;
}

CatalogoProdutos insereProduto(CatalogoProdutos catProd, Produto p){
  char *ch;
  int i;
  if (verificaAlpha(p[0]) && verificaAlpha(p[1]) && verificaNumero(&p[2], MINP, MAXP)){
    i = p[0]-'A';
    ch = (char*)malloc(sizeof(char)*(strlen(p)+1));
    strcpy(ch , p);
    catProd[i].lista = insertAVL(catProd[i].lista, ch, &catProd[i].crescimento,NULL);
    catProd[i].tamanho++;
  }
  return catProd;
}

Boolean existeProduto(CatalogoProdutos catProd, Produto p){
  Boolean b = FALSE;
  if (verificaAlpha(p[0])){
    b=exists(catProd[p[0]-'A'].lista, p);
  }
  return b;
}

int totalProdutos(CatalogoProdutos catProd){
  int total = 0;
  int i;
  for (i=0; i<TAMCAT; i++){
    total += catProd[i].tamanho;
  }
  return total;
}

int totalProdutosLetra(CatalogoProdutos catProd, char letra){
  return catProd[letra - 'A'].tamanho;
}

void removeCatProdutos(CatalogoProdutos catProd){
  int i;
  for (i=0; i<TAMCAT; i++){
    deleteAvl(catProd[i].lista);
  }
  free(catProd);
}


