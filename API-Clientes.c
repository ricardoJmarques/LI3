#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Clientes.h"

#define TAMCAT 26 /* numero de arvores do catalogo */
#define MINCLIENTE 1000
#define MAXCLIENTE 5000
/* listaLetra é uma AVL onde constam os   */
/* clientes iniciados por determinada letra */
typedef struct StructClientes{
  BTree lista[TAMCAT];
  int tamanho[TAMCAT];
  int crescimento[TAMCAT];
} *structclientes;

/* catalogo de clientes */
/*typedef struct ListaClientes *CatalogoClientes;*/

CatalogoClientes iniciaCatClientes(){
  int i;
  CatalogoClientes catCli = (CatalogoClientes)malloc(sizeof(struct StructClientes));
  for (i=0; i<TAMCAT; i++){
    catCli->lista[i] = NULL;
    catCli->tamanho[i] = 0;
    catCli->crescimento[i] = 0;
  }
  return catCli;
}

CatalogoClientes copiaCatClientes(CatalogoClientes catCli){
  int i;
  CatalogoClientes cp = (CatalogoClientes)malloc(sizeof(struct StructClientes));
  for (i=0; i<TAMCAT; i++){
    cp->lista[i] = avlCopy(catCli->lista[i]);
    cp->tamanho[i] = catCli->tamanho[i];
    cp->crescimento[i] = catCli->crescimento[i];
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
    catCli->lista[i] = insertAVL(catCli->lista[i], ch, &catCli->crescimento[i],NULL);
    catCli->tamanho[i]++;
  }
  return catCli;
}

Boolean existeCliente(CatalogoClientes catCli, Cliente c){
  Boolean b = FALSE;
  if (verificaAlpha(c[0]))
    b= exists(catCli->lista[c[0]-'A'], c);
  return b;
}

int totalClientes(CatalogoClientes catCli){
  int total = 0;
  int i;
  for (i=0; i<TAMCAT; i++){
    total += catCli->tamanho[i];
  }
  return total;
}

int totalClientesLetra(CatalogoClientes catCli, char letra){
  return catCli->tamanho[letra-'A'];
}

void removeCatClientes(CatalogoClientes catCli){
  int i;
  for (i=0; i<TAMCAT; i++){
    deleteAvl(catCli->lista[i]);
  }
  free(catCli);
}

void removeCatClientes2(CatalogoClientes catCli){
  int i;
  for (i=0; i<TAMCAT; i++){
    deleteAvl(catCli->lista[i]);
  }
}

void* retornaDadosCliente(CatalogoClientes catCli, Cliente c){
  return retornaDados(catCli->lista[c[0]-'A'], c);
}

void insereDadosCliente(CatalogoClientes catCli, Cliente c, void* dados){
    insereDados(catCli->lista[c[0]-'A'], c, dados);
}

ListaClientes retornaListaClientes (CatalogoClientes catCli){
  ListaClientes ListaC;
  int i,j,t;
  t = totalClientes(catCli);
  ListaC= calloc(t, sizeof(char*));
  j=0;
  for(i=0;i<TAMCAT;i++){
    avlInorder(catCli->lista[i] , ListaC , &j);
  }
  return ListaC;
}

void removeListaClientes(ListaClientes ListC, int tamanho){
  int i;
  for (i=0; i<tamanho; i++)
    free(ListC[i]);
  free(ListC);
}
