#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Filiais.h"

#define FMTAM 12
#define MINCLIENTE 1000
#define MAXCLIENTE 5000

typedef struct ListaFilial{
  BTree lista;
  int tamanho;
  int crescimento;
} lf1;
	
typedef struct ListaCompras{
  BTree lista;
  int tamanho;
  int crescimento;
  } *listacompra;

typedef struct Compra{
  int qtdN;
  float precoN;
  int qtdP;
  float precoP;
  } *compra;


CatalogoFilial iniciaCatFilial(CatalogoClientes catCli){
  /*int i;*/
  CatalogoFilial catFil;
  catFil = (CatalogoFilial)copiaCatClientes(catCli); /*Copia Catalogo de Clientes*/
  return catFil;
}

listacompra iniciaListaCompras(){
  int i;
  listacompra lc = (listacompra)malloc(sizeof(struct ListaCompras) * FMTAM);
  for (i=0; i<FMTAM; i++){
    lc[i].lista = NULL;
    lc[i].tamanho = 0;
    lc[i].crescimento = 0;
  }
  return lc;
}

void removeListaCompras(listacompra lc){
  int i;
  for(i=0; i<FMTAM; i++)
    deleteAvl(lc[i].lista);
  free(lc);
}

CatalogoFilial insereVendaFilial(CatalogoFilial catFil, Cliente c, Produto p, int qtd, float preco, int mes, char tipo){
  int i;
  listacompra lc;
  compra cp;
  char *ch;
  printf("Cliente: %s. Produto: %s. Quantidade: %d. Preco: %0.2f. Mes: %d. Tipo: %c\n",c,p,qtd,preco,mes,tipo);
  if (verificaAlpha(c[0]) && verificaNumero(&c[1], MINCLIENTE, MAXCLIENTE)){
    i=c[0]-'A';
    if((lc = retornaDados(catFil[i].lista, c)) == NULL){
      lc = iniciaListaCompras();
      ch = (char*)malloc(sizeof(char)*(strlen(c)+1));
      catFil[i].lista = insertAVL(catFil[i].lista, ch, &catFil[i].crescimento, lc);
    }
    else{
      i=mes-1;
      if((cp=retornaDados(lc[i].lista, p)) == NULL){
        cp = (compra)malloc(sizeof(struct Compra));
        ch = (char*)malloc(sizeof(char)*(strlen(p)+1));
        strcpy(ch, p);
        if (tipo == 'N'){
          cp->qtdN = qtd;
          cp->precoN = preco;
          cp->qtdP = 0;
          cp->precoP = 0;
        }
        else{
          cp->qtdP = qtd;
          cp->precoP = preco;
          cp->qtdN = 0;
          cp->precoN = 0;
        }
        lc[i].lista = insertAVL(lc[i].lista, ch, &lc[i].crescimento, cp);
      }
      else {
        if (tipo == 'N'){
          cp->qtdN += qtd;
          cp->precoN += preco;
        }
        else{
          cp->qtdP += qtd;
          cp->precoP += preco;
        }
      }
    }
  }
  return catFil;
}

void removeCatFilial(CatalogoFilial catFil){
  int i,j;
  char c;
  char ch[10];
  listacompra lc;
  c = 'A';
  for (i=0; i<26; i++){
    for (j=1000; j<=5000; j++){
      sprintf(ch,"%c%d",c , j);
      if ((lc = retornaDados(catFil[i].lista, ch)) != NULL){
        removeListaCompras(lc);
      }
    }
    c++;
  }
  removeCatClientes((CatalogoClientes) catFil);
}

