#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"

#define TAMCAT 26 /* numero de arvores do catalogo */
#define MINPRODUTO 1000
#define MAXPRODUTO 1999

/* listaLetra é uma AVL onde constam os   */
/* clientes iniciados por determinada letra */
typedef struct listaProdutos{
  BTree lista;
  int tamanho;
  int crescimento;
} listaLetraProdutos;

/* catalogo de clientes */
typedef listaLetraProdutos *catProdutos;

catProdutos iniciaCatProdutos(){
  int i;
  catProdutos prod = (catProdutos) malloc(sizeof(struct listaProdutos) * TAMCAT);
  for (i=0; i<TAMCAT; i++){
    prod[i].lista = NULL;
    prod[i].tamanho = 0;
    prod[i].crescimento = 0;
  }
  return prod;
}

catProdutos insereProduto(catProdutos prod, char *produto){
  char *p;
  if (verificaAlpha(produto[0]) && verificaAlpha(produto[1]) && verificaNumero(&produto[2], MINPRODUTO, MAXPRODUTO)){
    p = (char*)malloc(sizeof(char)*(strlen(produto)+1));
    strcpy(p , produto);
    prod[produto[0]-'A'].lista = insertAVL(prod[produto[0]-'A'].lista, p, &prod[produto[0]-'A'].crescimento,NULL);
    prod[produto[0]-'A'].tamanho++;
  }
  return prod;
}

Boolean existeProduto(catProdutos prod, char *produto){
  Boolean b = FALSE;
  if (verificaAlpha(produto[0])){
    if (exists(prod[produto[0]-'A'].lista, produto)){
      b = TRUE;
    }
  }
  return b;
}

char* existeProduto2(catProdutos prod, char *produto){
    char *c;
    c = (char*)exists2(prod[produto[0]-'A'].lista, produto);
    return c;
}

int totalProdutos(catProdutos prod){
  int total = 0;
  int i;
  for (i=0; i<TAMCAT; i++){
    total += prod[i].tamanho;
  }
  return total;
}

int totalProdutosLetra(catProdutos prod, char letra){
  return prod[letra - 'A'].tamanho;
}

void removeCatProdutos(catProdutos prod){
  int i;
  for (i=0; i<TAMCAT; i++){
    deleteAvl(prod[i].lista);
/*    prod[i].lista = NULL;
    prod[i].tamanho = 0;
    prod[i].crescimento = 0;*/
  }
  free(prod);
}

