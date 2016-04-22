#include <stdlib.h>
#include <string.h>
#include "API-Utils.h"

/*typedef enum {FALSE,TRUE} Boolean;*/

typedef struct ListaGen{
  char** lista;
  int tamanho;
  int tamMax;
} *listaGen;

Boolean verificaAlpha(char caracter){
    return ( caracter >= 'A' && caracter <= 'Z' ) ? TRUE : FALSE;
}

Boolean verificaNumero(char *num, int min, int max){
    int n;
    n=atoi(num);
    return ( n >=min && n <=max ) ? TRUE : FALSE;  
}

ListaGenerica initListaGen(int n){
  listaGen lg;
  lg = malloc(sizeof(struct ListaGen));
  lg->lista= calloc(n, sizeof(char*));
  lg->tamanho = 0;
  lg->tamMax = n;
}

ListaGenerica insereListaGen(ListaGenerica lg, char* string){
  int i, j;
  i = retornaPosListaGen(lg);
  j = retornaTamMaxListaGen(lg);
  if (i<j){
    lg->lista[i]=malloc(sizeof(char) * (strlen(string)+1));
    strcpy(lg->lista[i],string);
    lg->tamanho++;
  }
  return lg;
}
  
int retornaPosListaGen(ListaGenerica lg){
  return lg->tamanho;
}

int retornaTamMaxListaGen(ListaGenerica lg){
  return lg->tamMax;
}

char** retornaListaGen(ListaGenerica lg){
  return lg->lista;
}

void removeListaGen(ListaGenerica lg){
  int i, tamanho;
  char **lista;
  tamanho = retornaPosListaGen(lg);
  lista = retornaListaGen(lg);
  for (i=0; i<tamanho; i++)
    free(lista[i]);
  free(lista);
  free(lg);
}
