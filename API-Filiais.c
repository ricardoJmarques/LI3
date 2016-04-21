#include <stdlib.h>
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Filiais.h"

#define FMTAM 12
#define FCTAM 26
#define MINCLIENTE 1000
#define MAXCLIENTE 5000
#define MINPRODUTO 1000
#define MAXPRODUTO 1999

typedef struct ListaFilial{/*lista de clientes*/
  CatalogoClientes catMes[FMTAM];
  int comprasValidas[FMTAM];
} lf1;
	
typedef struct Compra{
  int qtdN;
  float precoN;
  int qtdP;
  float precoP;
  } *compra;

typedef struct ListaDecrescente{
  char* string;
  int qtd;
}*ld1;

compra insereCompra(compra c, int qtd, float preco, char tipo){
  if (c!=NULL){
    if (tipo == 'N'){
      c->qtdN += qtd;
      c->precoN = preco;
    }
    else {
      c->qtdP += qtd;
      c->precoP = preco;
    }
    return c;
  }
  else {
    compra aux;
    aux = (compra)malloc(sizeof(struct Compra));
    if (tipo == 'N'){
      aux->qtdN = qtd;
      aux->precoN = preco;
      aux->qtdP = 0;
      aux->precoP = 0;
    }
    else{
      aux->qtdP = qtd;
      aux->precoP = preco;
      aux->qtdN = 0;
      aux->precoN = 0;
    }
    return aux;
  }
}

CatalogoFilial iniciaCatFilial(CatalogoClientes catCli){
  int i;
  CatalogoFilial catFil = malloc(sizeof(struct ListaFilial));
  for (i = 0; i<FMTAM; i++){
    catFil->catMes[i] = copiaCatClientes(catCli);
    catFil->comprasValidas[i] = 0;
  }
  return catFil;
}

CatalogoFilial insereVendaFilial(CatalogoFilial catFil, Cliente c, Produto p, int qtd, float preco, int mes, char tipo){
  int i;
  CatalogoProdutos catProd;
  compra cp;
  i = mes - 1;
    
  if ((catProd=(CatalogoProdutos)retornaDadosCliente(catFil->catMes[i], c)) == NULL){
    catProd = iniciaCatProdutos();
    insereDadosCliente(catFil->catMes[i], c, catProd);
    insereProduto(catProd, p);
  }

  if ((cp=(compra)retornaDadosProduto(catProd, p)) == NULL){
    cp = insereCompra(cp, qtd, preco, tipo);
    insereDadosProduto(catProd, p, cp);
  }
  else{
    cp = insereCompra(cp, qtd, preco, tipo);
  }

  catFil->comprasValidas[i]++;
  return catFil;
}

void removeCatFilial(CatalogoFilial catFil){
  int i,j,k;
  char c;
  char ch[10];
  CatalogoProdutos catProd;
  CatalogoClientes catCli;
  for (i=0; i<FMTAM; i++){
    c = 'A';
    for (j=0; j<FCTAM; j++){
      for (k=MINCLIENTE; k<=MAXCLIENTE; k++){
        sprintf(ch,"%c%d",c , k);
        if ((catProd = (CatalogoProdutos)retornaDadosCliente(catFil->catMes[i], ch)) != NULL){
        removeCatProdutos2(catProd);
        }
      }
    c++;
    }
  removeCatClientes(catFil->catMes[i]);
  }
  free(catFil);
}

int totalCompras(CatalogoFilial catFil){
  int i,j,total;
  total=0;
  for (i=0; i<FMTAM; i++){
      total += catFil->comprasValidas[i];
  }
  return total;
}
/*
void comprasDecrescente (CatalogoFilial catFil , Cliente c, int mes , int totalProdutos){
  listaDecrescente* listd;
  listd = malloc(sizeof(struct ListaDecrescente) * totalProdutos);

}

*/


int clientesGold (CatalogoClientes catCli, CatalogoFilial catFil){ /*query x*/
  int i,j,k,resultado,controlo, tt;
  CatalogoProdutos catProd;
  ListaClientes ListaC;
  ListaC = retornaListaClientes(catCli);
  resultado = 0;
  k=totalClientes(catCli);
  for(i=0;i<k;i++){
    controlo=1;
    for(j=0;controlo == 1 && j<FMTAM;j++){
      if(retornaDadosCliente(catFil->catMes[j], ListaC[i]) != NULL){
        controlo=0;
      }
    }
    if(controlo==0)
      resultado++;/*meter para a string*/
  }
    removeListaClientes(ListaC, k);
    return resultado;
}

int clientesContemProduto (CatalogoClientes catCli, CatalogoFilial catFil , Produto p){
  int i,j,k,totalP,totalN;
  CatalogoProdutos catProd;
  compra cp;
  ListaClientes ListaC;

  ListaC = retornaListaClientes(catCli);
  k=totalClientes(catCli);
  totalN=0;
  totalP=0;
  
  for(i=0;i<FMTAM;i++){
    for(j=0;j<k;j++){
      if((catProd = (CatalogoProdutos)retornaDadosCliente(catFil->catMes[i] , ListaC[j])) != NULL){
        if((cp = (compra) retornaDadosProduto(catProd , p)) != NULL){
          if(cp->qtdP != 0) totalP++;
          if(cp->qtdN != 0) totalN++;
          /*mete na string*/
        }
      }
    }
  }
  printf("totalN=%d\n", totalN);
  printf("totalP=%d\n", totalP);
  return 0;
}

void comprasDecrescente (CatalogoFilial catFil , Cliente c, int mes ,   listaDecrescente* ld , int* j){
  /*listaDecrescente* listd;
  listd = malloc(sizeof(struct ListaDecrescente) * totalProdutos);*/
  int i;
  CatalogoProdutos catProd;
  ListaProdutos listP;
  compra cp;
  
  catProd = (CatalogoProdutos)retornaDadosCliente(catFil->catMes[mes-1], c);
  listP = retornaListaProdutos(catProd);
	
  ld=realloc(ld , totalProdutos(catProd));

  for(i=0;listP[i]!=NULL;i++){
    printf("for%s\n",listP[i] );
  }

  for(i=0;listP[i]!=NULL;i++){
    ld[*j]->string = malloc(sizeof(char) * strlen(listP[i]));
    strcpy(ld[*j]->string , listP[i]);
    cp = (compra)retornaDadosProduto(catProd , listP[i]);
    ld[*j]->qtd = ((cp->qtdN) + (cp->qtdP));
    (*j)++;
    printf("string = %s\n", ld[*j]->string );
    printf("qtd = %d\n", ld[*j]->qtd );
  }

}

void iniciaListaDecrescente (listaDecrescente* ld){
  ld = malloc (sizeof(struct ListaDecrescente)); /*<----- faço o primeiro malloc ; é preciso */
}
