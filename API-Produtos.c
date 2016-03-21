#include <string.h>

#define TAMPL 200000/*tamanho das linhas produto*/
#define TAMPC 10 /*tamanho das colunas produto*/

typedef struct {
   char  letra1; /* AA1234 - [A-Z][A-Z][1000-1999] */
   char letra2;
   int numero;
} Produto;

int retornaCodProduto(char *codigo){
  int i;
  int fst = 0;
  int snd = 0;
  int trd = 0;

  fst = codigo[0] - 'A';
  snd = codigo[1] - 'A';
  for (i=2; i<6; i++){
    trd = ((trd * 10) + (codigo[i]-'0'));
  }
  return (fst*26*1000)+(snd*1000)+(trd%1000);
}

void criaMapaProduto(char *mapa, char *listaProduto, int tam){
  int i = 0;
  char codigo[TAMPC];
 
  for (i=0; i<tam; i++){
    strcpy(codigo, &listaProduto[i * TAMPC]);
    mapa[retornaCodProduto(codigo)] = 0x01;
  }
}


