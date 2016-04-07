#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"

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
typedef listaLetraClientes *catClientes;

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

catClientes insereCliente(catClientes ccs, char *cliente){
  if (verificaAlpha(cliente[0]) && verificaNumero(&cliente[1], MINCLIENTE, MAXCLIENTE)){
    ccs[cliente[0]-'A'].lista = insertAVL(ccs[cliente[0]-'A'].lista, cliente, &ccs[cliente[0]-'A'].crescimento);
    ccs[cliente[0]-'A'].tamanho++;
  }
  return ccs;
}

Boolean existeCliente(catClientes ccs, char *cliente){
  Boolean b = FALSE;
  if (verificaAlpha(cliente[0]))
    if (exists(ccs[cliente[0]-'A'].lista, cliente))
      b = TRUE;
  return b;
}

int totalClientes(catClientes ccs){
  int total = 0;
  int i;
  for (i=0; i<TAMCAT; i++){
    total += ccs[i].tamanho;
  }
  return total;
}

int totalClientesLetra(catClientes ccs, char letra){
  return ccs[letra - 'A'].tamanho;
}

void removeCatClientes(catClientes ccs){

}

