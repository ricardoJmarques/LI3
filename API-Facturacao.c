#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"

#define TAMCAT 24 /* numero de arvores do catalogo; 12 meses P + 12 meses N */

typedef struct prodVenda{
  int qtd;
  float preco;
  int filial;
} pVenda;

typedef pVenda *ppVenda;

typedef struct venda{
  BTree lista;
  int tamanho;
  int crescimento;
} listaMesVendas;	
	
typedef listaMesVendas *catFacturacao;
	
catFacturacao iniciaCatFacturacao(){
  int i;
  catFacturacao cat;
  cat = (catFacturacao) malloc(sizeof(struct venda) * (TAMCAT*2));
  for (i=0; i<TAMCAT*2; i++){
    cat[i].lista = NULL;
    cat[i].tamanho = 0;
    cat[i].crescimento = 0;
  }
  return cat;
}

catFacturacao insereVenda(catFacturacao cat, char *venda){
  int i, j;
  char v[7][7]; /*char produtoID[7];char preço[7];char qtd[4];char PN[2];char cliente[6];char MES[3];char Filial[2];*/
  char *var;
  ppVenda pp;
  
  i=0;
  var = strtok(venda, " ");
  strcpy(v[i] , var);
  while ((var = strtok(NULL, " ")) != NULL){ 
    i++;
    strcpy(v[i] , var);
  }
  
  if (verificaAlpha(v[0][0]) && 
      verificaAlpha(v[0][1]) &&
      verificaNumero(&v[0][2], 1000, 1999)){

      
    pp = (ppVenda)malloc(sizeof(struct prodVenda));
    var = (char*)malloc(sizeof(char) * (strlen(v[0]) +1));
    strcpy(var, v[0]);
    pp->qtd = atoi(v[2]);
    pp->preco = atof(v[1]);
    pp->filial = atoi(v[6]);

    if (v[3][0] == 'N') j=0; else j=1;
    i = (j*TAMCAT) + atoi(v[5]) - 1;
  
    cat[i].lista = insertAVL(cat[i].lista, var, &cat[i].crescimento, pp);
    cat[i].tamanho++;

  }
  return cat;
}

int totalProdutosVenda(catFacturacao cat, int mes, char tipo){
  int i, j;
  if (tipo == 'N') j=0; else j=1;
    i = (j*TAMCAT) + mes - 1;

  return cat[i].tamanho;
}

void retornaCoisas(catFacturacao cat, char *produto, int mes, char tipo){
    ppVenda pp;
    int i, j;
    char *c;
    if (tipo == 'N') j=0; else j=1;
    i= j*TAMCAT + mes - 1;
    pp = (ppVenda) retornaDados (cat[i].lista, produto);
    if (pp)
      printf("Quantidade: %d. Preço: %0.2f. Filial: %d.\n", pp->qtd, pp->preco, pp->filial);
    else
      printf("Não existem dados.\n"); 

}
