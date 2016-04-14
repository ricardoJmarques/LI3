#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Facturacao.h"
#include "API-Clientes.h"
#include "API-Produtos.h"

#define TAMCAT 12 /* numero de arvores do catalogo; 12 meses por Filial */

typedef struct prodVenda{
  int qtdN;
  int qtdP;
  float precoN;
  float precoP;
/*  int filial;*/
} pVenda;

typedef pVenda *ppVenda;

typedef struct venda{
  BTree lista;
  int tamanho;
  int crescimento;
} listaMesVendas;	
	
/*typedef struct venda *catFacturacao;*/
	
catFacturacao iniciaCatFacturacao(){
  int i, j;
  catFacturacao cat;
  cat = (catFacturacao)malloc(sizeof(struct venda) * (TAMCAT*3));
  for (j=0; j<3; j++){
    for (i=0; i<TAMCAT; i++){
      cat[j*TAMCAT+i].lista = NULL;
      cat[j*TAMCAT+i].tamanho = 0;
      cat[j*TAMCAT+i].crescimento = 0;
    }
  }
  return cat;
}

catFacturacao insereVenda(catFacturacao cat, catClientes cli, catProdutos pro, char *venda){
  int i;
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
  i = ((atoi(v[6])-1) * TAMCAT) + (atoi(v[5]) - 1 );
  if (existeVenda(cat, v[0],  atoi(v[6]), atoi(v[5]))){
    pp = (ppVenda)retornaDados (cat[i].lista, v[0]);
    if (v[3][0] == 'N'){
        pp->qtdN += atoi(v[2]);
      }
      else{
        pp->qtdP += atoi(v[2]);
      }
  }
  else {
    if (existeProduto(pro, v[0]) && existeCliente(cli, v[4])){
      pp = (ppVenda)malloc(sizeof(struct prodVenda));
      var = (char*)malloc(sizeof(char) * (strlen(v[0]) +1));
      strcpy(var, v[0]);
      if (v[3][0] == 'N'){
        pp->qtdN = atoi(v[2]);
        pp->precoN = atof(v[1]);
        pp->qtdP = 0;
        pp->precoP = 0;
      }
      else{
        pp->qtdP = atoi(v[2]);
        pp->precoP = atof(v[1]);
        pp->qtdN = 0;
        pp->precoN = 0;
      }
      cat[i].lista = insertAVL(cat[i].lista, var, &cat[i].crescimento, pp);
      cat[i].tamanho++;
    }
  }
  return cat;
}

int totalProdutosVenda(catFacturacao cat, int mes, int filial){
  int i;
  i = ((filial-1)*TAMCAT)+(mes-1);
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
      printf("Quantidade: %d. Preço: %0.2f. Filial: %d.\n", pp->qtdN, pp->precoN);
    else
      printf("Não existem dados.\n"); 
}

Boolean existeVenda(catFacturacao cat, char *cliente, int filial, int mes){
  Boolean b = FALSE;
  int i;
  if (verificaAlpha(cliente[0]))
    i = ((filial-1)*TAMCAT)+(mes-1);
    if (exists(cat[i].lista, cliente))
      b = TRUE;
  return b;
}

void removeCatFacturacao(catFacturacao fact, int filiais){
  int i, j;
  j = TAMCAT * filiais;
  for (i=0; i<j; i++){
    deleteAvl(fact[i].lista);
  }
  free(fact);
}
