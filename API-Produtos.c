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
  BTree lista[TAMCAT];
  int tamanho[TAMCAT];
  int crescimento[TAMCAT];
} listap;

/* tipo Produto */
/*typedef char* Produto;*/

/* catalogo de Produtos */
/*typedef struct ListaProdutos *CatalogoProdutos;*/

CatalogoProdutos iniciaCatProdutos(){
  int i;
  /* criar array de 26 listaProdutos */
  CatalogoProdutos catProd = malloc(sizeof(struct ListaProdutos));
  for (i=0; i<TAMCAT; i++){
    catProd->lista[i] = NULL;
    catProd->tamanho[i] = 0;
    catProd->crescimento[i] = 0;
  }
  return catProd;
}

CatalogoProdutos copiaCatProdutos(CatalogoProdutos catProd){
  int i;
  CatalogoProdutos cp = (CatalogoProdutos)malloc(sizeof(struct ListaProdutos));
  for (i=0; i<TAMCAT; i++){
    cp->lista[i] = avlCopy(catProd->lista[i]);
    cp->tamanho[i] = catProd->tamanho[i];
    cp->crescimento[i] = catProd->crescimento[i];
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
    catProd->lista[i] = insertAVL(catProd->lista[i], ch, &catProd->crescimento[i],NULL);
    catProd->tamanho[i]++;
  }
  return catProd;
}

Boolean existeProduto(CatalogoProdutos catProd, Produto p){
  Boolean b = FALSE;
  if (verificaAlpha(p[0])){
    b=exists(catProd->lista[p[0]-'A'], p);
  }
  return b;
}

int totalProdutos(CatalogoProdutos catProd){
  int total = 0;
  int i;
  for (i=0; i<TAMCAT; i++){
    total += catProd->tamanho[i];
  }
  return total;
}

int totalProdutosLetra(CatalogoProdutos catProd, char letra){
  return catProd->tamanho[letra - 'A'];
}

void removeCatProdutos(CatalogoProdutos catProd){
  int i;
  for (i=0; i<TAMCAT; i++){
    deleteAvl(catProd->lista[i]);
  }
  free(catProd);
}

void* retornaDadosProduto(CatalogoProdutos catProd, Produto p){
  return retornaDados (catProd->lista[p[0]-'A'], p);
}

