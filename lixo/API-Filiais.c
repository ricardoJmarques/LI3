#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Filiais.h"

#define TAMCAT 12 /* numero de arvores do catalogo; 12 meses */

typedef struct prodVenda{
  int qtdn; /* quantidade comprada em regime normal*/
  int qtdp; /* quantidade comprada em promocao*/
  float precon; /* preco normal*/
  float precop; /* preco promocao*/
} pVendafilial;

typedef pVendafilial *ppVendaFilial;

typedef struct venda{
  BTree lista;
  int tamanho;
  int crescimento;
} listaMesVendas;	
	
/*typedef struct venda *catFacturacao;*/
	
catFilial iniciaCatFilial(){
  int i;
  catFilial cat;
  cat = (catFilial) malloc(sizeof(struct venda) * (TAMCAT));
  for (i=0; i<TAMCAT; i++){
    cat[i].lista = NULL;
    cat[i].tamanho = 0;
    cat[i].crescimento = 0;
  }
  return cat;
}

catFilial insereVendaFilialClientes (catFilial cat, char* venda){
    int i;
    char v[7][7]; /*char produtoID[7];char preço[7];char qtd[4];char PN[2];char cliente[6];char MES[3];char Filial[2];*/
    char *var;
    ppVendaFilial pp;
  
    i=0;

    var = strtok(venda, " ");
    strcpy(v[i] , var);
    while ((var = strtok(NULL, " ")) != NULL){ 
        i++;
        strcpy(v[i] , var);
  }


}

catFilial insereVendaFilialProdutos (catFilial cat, char* venda) ?????