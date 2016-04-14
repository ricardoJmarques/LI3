#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TAMVL 1000000 /*tamanho das linhas vendas*/
#define TAMVC 40 /*tamanho das colunas vendas*/

typedef enum{FALSE,TRUE}boolean;

typedef struct {
  char produtoID[7];  /* AA1234 - [A-Z][A-Z][1000-1999] */
  float preco;        /* [0.0-999.99] */
  int qtd;            /* [1-200] */
  char promocao;      /* "P" || "N" */
  char clienteID[6];  /* A1234 - [A-Z][1000-5000] */
  int data;           /* Mes - [1-12] */
  int filial;         /* [1-3] */
} venda;
  
int parseLinha(char *linha, char *mapaProduto, char *mapaCliente){
  int i=0;
  char venda[7][7]; /*char produtoID[7];char preço[7];char ccc[4];char d[2];char e[6];char f[3];char g[2];*/
  char *var;
  int flag = 0;
  
  var = strtok(linha, " ");
  strcpy(venda[i] , var);
  while ((var = strtok(NULL, " ")) != NULL){ 
    i++;
    strcpy(venda[i] , var);
  }
  if (strlen(venda[0]) != 6) /*verifica tamanho de produto*/
    flag = 1;
  if (flag == 0 && strlen(venda[4]) != 5) /*verifica tamanho de cliente*/
    flag = 2;
  if (flag == 0 && (mapaProduto[retornaCodProduto(venda[0])] == 0x00))
    flag = 3; 
  if (flag == 0 && (mapaCliente[retornaCodCliente(venda[4])] == 0x00))
    flag = 4;
 return flag;
}

int preencheArrayVendas(FILE *ficheiro, char *tabela, char *mapaProduto, char *mapaCliente){
  int i = 0;
  char buffer[TAMVC];
  char linha[TAMVC];

  while ((i<TAMVL) && (fgets(buffer, TAMVC-1, ficheiro)!=NULL)){
    strcpy(linha, strtok(buffer, "\r\n"));
    if (parseLinha(linha, mapaProduto, mapaCliente) == 0){
      strcpy(&tabela[i*TAMVC], linha);
      i++;
    }
  }
  printf("Ficheiro carregado para a memoria no formato %d x %d.\n", TAMVL, TAMVC);
  printf("%d linhas encontradas.\n", i);
  return i;
}


