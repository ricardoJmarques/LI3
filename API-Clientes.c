#include <string.h>

#define TAMCL 20000 /*tamanho das linhas cliente*/
#define TAMCC 10 /*tamanho das colunas cliente*/

typedef enum{FALSE,TRUE}boolean;


typedef struct Cliente {
   char  letra; /* A1234 - [A-Z][1000-5000] */
   int numero;
} Cliente;

boolean verificaAlpha(char caracter){
    return ( caracter >= 'A' && caracter <= 'Z' ) ? TRUE : FALSE;
}

boolean verificaNumero(char *num){
    int n;
    n=atoi(num);
    return ( n >=1000 && n <=5000 ) ? TRUE : FALSE;  
}

int criaListaClientes(){
  char *CodAlfa[26];
}

int retornaCodCliente(char *codigo){
  int i;
  int fst = 0;
  int snd = 0;

  fst = codigo[0] - 'A';
  for (i=1; i<5; i++){
     snd = ((snd * 10) + (codigo[i]-'0'));
  }
  return ((fst*10000)+(snd%10000));
}

void criaMapaCliente(char *mapa, char *listaCliente, int tam){
  int i = 0;
  char codigo[TAMCC];

  for (i=0; i<tam; i++){
    strcpy(codigo, &listaCliente[i * TAMCC]);
    mapa[retornaCodCliente(codigo)] = 0x01;
  }
}

