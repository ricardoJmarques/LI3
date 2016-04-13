#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Clientes.h"

#define TAMCAT 26 /* numero de arvores do catalogo */
#define MINCLIENTE 1000
#define MAXCLIENTE 5000

/* listaLetra é uma AVL onde constam os   */
/* clientes iniciados por determinada letra */
typedef struct listaClientes{
  BTree lista;
  int tamanho;
  int crescimento;
} listaLetraClientes;

/* catalogo de clientes */
/*typedef struct listaClientes *catClientes;*/

catClientes iniciaCatClientes(){
  int i;
  catClientes cat = (catClientes) malloc(sizeof(struct listaClientes) * TAMCAT);
  for (i=0; i<TAMCAT; i++){
    cat[i].lista = NULL;
    cat[i].tamanho = 0;
    cat[i].crescimento = 0;
  }
  return cat;
}

catClientes insereCliente(catClientes cat, char *cliente){
  char *c;
  if (verificaAlpha(cliente[0]) && verificaNumero(&cliente[1], MINCLIENTE, MAXCLIENTE)){
    c = (char*)malloc(sizeof(char)*(strlen(cliente)+1));
    strcpy(c , cliente);
    cat[cliente[0]-'A'].lista = insertAVL(cat[cliente[0]-'A'].lista, c, &cat[cliente[0]-'A'].crescimento,NULL);
    cat[cliente[0]-'A'].tamanho++;
  }
  return cat;
}

Boolean existeCliente(catClientes cat, char *cliente){
  Boolean b = FALSE;
  if (verificaAlpha(cliente[0]))
    if (exists(cat[cliente[0]-'A'].lista, cliente))
      b = TRUE;
  return b;
}

int totalClientes(catClientes cat){
  int total = 0;
  int i;
  for (i=0; i<TAMCAT; i++){
    total += cat[i].tamanho;
  }
  return total;
}

int totalClientesLetra(catClientes cat, char letra){
  return cat[letra - 'A'].tamanho;
}

void removeCatClientes(catClientes cat){
  int i;
  for (i=0; i<TAMCAT; i++){
    deleteAvl(cat[i].lista);
/*    cat[i].lista = NULL;
    cat[i].tamanho = 0;
    cat[i].crescimento = 0; */
  }
  free(cat);
}

