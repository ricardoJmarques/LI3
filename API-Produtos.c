#include <stdlib.h>
#include "avl-strings.h"

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
  if (verificaAlpha(produto[0]) && verificaAlpha(produto[1]) && verificaNumero(&produto[2], MINPRODUTO, MAXPRODUTO)){
    prod[produto[0]-'A'].lista = insertAVL(prod[produto[0]-'A'].lista, produto, &prod[produto[0]-'A'].crescimento);
    prod[produto[0]-'A'].tamanho++;
  }
  return prod;
}

/*Boolean existeProduto(catClientes ccs, Cliente c){
  return true;
}*/

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

}

