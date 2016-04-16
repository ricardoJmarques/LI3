#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Clientes.h"

#define TAMCAT 26 /* numero de arvores do catalogo */
#define MINCLIENTE 1000
#define MAXCLIENTE 5000

/* listaLetra é uma AVL onde constam os   */
/* clientes iniciados por determinada letra */
typedef struct ListaClientes{
  BTree lista;
  int tamanho;
  int crescimento;
} listac;

/* catalogo de clientes */
/*typedef struct ListaClientes *CatalogoClientes;*/

CatalogoClientes iniciaCatClientes(){
  int i;
  CatalogoClientes catCli = (CatalogoClientes)malloc(sizeof(struct ListaClientes) * TAMCAT);
  for (i=0; i<TAMCAT; i++){
    catCli[i].lista = NULL;
    catCli[i].tamanho = 0;
    catCli[i].crescimento = 0;
  }
  return catCli;
}

CatalogoClientes copiaCatClientes(CatalogoClientes catCli){
  int i;
  CatalogoClientes cp = (CatalogoClientes)malloc(sizeof(struct ListaClientes) * TAMCAT);
  for (i=0; i<TAMCAT; i++){
    cp[i].lista = avlCopy(catCli[i].lista);
    cp[i].tamanho = catCli[i].tamanho;
    cp[i].crescimento = catCli[i].crescimento;
  }
  return cp;
}

CatalogoClientes insereCliente(CatalogoClientes catCli, Cliente c){
  char *ch;
  int i;
  if (verificaAlpha(c[0]) && verificaNumero(&c[1], MINCLIENTE, MAXCLIENTE)){
    i = c[0]-'A';
    ch = (char*)malloc(sizeof(char)*(strlen(c)+1));
    strcpy(ch , c);
    catCli[i].lista = insertAVL(catCli[i].lista, ch, &catCli[i].crescimento,NULL);
    catCli[i].tamanho++;
  }
  return catCli;
}

Boolean existeCliente(CatalogoClientes catCli, Cliente c){
  Boolean b = FALSE;
  if (verificaAlpha(c[0]))
    b= exists(catCli[c[0]-'A'].lista, c);
  return b;
}

int totalClientes(CatalogoClientes catCli){
  int total = 0;
  int i;
  for (i=0; i<TAMCAT; i++){
    total += catCli[i].tamanho;
  }
  return total;
}

int totalClientesLetra(CatalogoClientes catCli, char letra){
  return catCli[letra-'A'].tamanho;
}

void removeCatClientes(CatalogoClientes catCli){
  int i;
  for (i=0; i<TAMCAT; i++){
    deleteAvl(catCli[i].lista);
  }
  free(catCli);
}

