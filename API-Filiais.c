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

typedef struct ListaMes{
  CatalogoProdutos catMes[FMTAM];
} *listaMes;

typedef struct ListaFilial{/*lista de clientes*/
  CatalogoClientes cliente;
  int comprasValidas;
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
  int tamanho;
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

listaMes iniciaListaMes(){
  int i;
  listaMes lm = (listaMes)malloc(sizeof(struct ListaMes));
  for(i=0;i<FMTAM;i++){
    lm->catMes[i] = iniciaCatProdutos();
  }
  return lm;
}

void removeListaMes(listaMes lm){
  int i;
  for(i=0;i<FMTAM;i++){
    removeCatProdutos(lm->catMes[i]);
  }
  /*free(lm);*/
}

CatalogoFilial iniciaCatFilial(CatalogoClientes catCli){
  int i;
  CatalogoFilial catFil = malloc(sizeof(struct ListaFilial));
  catFil->cliente = copiaCatClientes(catCli);
  catFil->comprasValidas = 0;
  return catFil;
}

CatalogoFilial insereVendaFilial(CatalogoFilial catFil, Cliente c, Produto p, int qtd, float preco, int mes, char tipo){
  int i;
  listaMes lstMes;
  CatalogoProdutos catProd;
  compra cp;
  
  i = mes - 1;
    
  if ((lstMes=(listaMes)retornaDadosCliente(catFil->cliente, c)) == NULL){
    lstMes = iniciaListaMes();
    insereDadosCliente(catFil->cliente, c, lstMes);
  }
  
  catProd = lstMes->catMes[i];
  
  if (!existeProduto(catProd, p))
    insereProduto(catProd, p);
  
  if ((cp=(compra)retornaDadosProduto(catProd, p)) == NULL){
    cp = insereCompra(cp, qtd, preco, tipo);
    insereDadosProduto(catProd, p, cp);
  }
  else{
    cp = insereCompra(cp, qtd, preco, tipo);
  }
  catFil->comprasValidas++;
  return catFil;
}

void removeCatFilial(CatalogoFilial catFil){
  int i,j;
  char c;
  char ch[10];
  listaMes lm;
  c = 'A';
  for (i=0; i<FCTAM; i++){
    for (j=MINCLIENTE; j<=MAXCLIENTE; j++){
      sprintf(ch,"%c%d",c , j);
      if ((lm = (listaMes)retornaDadosCliente(catFil->cliente, ch)) != NULL){
        removeListaMes(lm);
        }
      }
    c++;
    }
  removeCatClientes(catFil->cliente);
  free(catFil);
}

int totalCompras(CatalogoFilial catFil){
  return catFil->comprasValidas;
}
  
/*
int totalCompras(CatalogoFilial catFil){
  int i,j,total;
  total=0;
  for (i=0; i<FMTAM; i++){
      total += catFil->comprasValidas[i];
  }
  return total;
}
*/
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
    if(retornaDadosCliente(catFil->cliente, ListaC[i]) != NULL){
      resultado++;
      /*escreve para lista*/
    }
  }
  removeListaClientes(ListaC, k);
  return resultado;
}

int clientesContemProduto (CatalogoClientes catCli, CatalogoFilial catFil , Produto p){
  int i,j,k,totalP,totalN,flag;
  compra cp;
  ListaClientes ListaC;
  listaMes lstMes;

  ListaC = retornaListaClientes(catCli);
  k=totalClientes(catCli);
  totalN=0;
  totalP=0;
  flag=0;
  for(j=0;j<k;j++){
    if((lstMes=(listaMes)retornaDadosCliente(catFil->cliente, ListaC[j])) != NULL){
      for(i=0; flag==0 && i<FMTAM; i++){
        if((cp = (compra) retornaDadosProduto(lstMes->catMes[i] , p)) != NULL){
          flag = 1;
          if(cp->qtdP != 0) totalP++;
          if(cp->qtdN != 0) totalN++;
          /*mete na string*/
        }
      }
      flag = 0;
    }
  }
  printf("totalN=%d\n", totalN);
  printf("totalP=%d\n", totalP);
  return 0;
}
/*
void comprasDecrescente (CatalogoFilial catFil , Cliente c, int mes ,   listaDecrescente* ld , int* j){
  *//*listaDecrescente* listd;
  listd = malloc(sizeof(struct ListaDecrescente) * totalProdutos);*/
/*  int i;
  CatalogoProdutos catProd;
  ListaProdutos listP;
  compra cp;

  
  catProd = (CatalogoProdutos)retornaDadosCliente(catFil->catMes[mes-1], c);
  listP = retornaListaProdutos(catProd);

  ld = (listaDecrescente*)realloc(ld ,totalProdutos(catProd) );

  for(i=0;listP[i]!=NULL;i++){
    printf("for%s\n",listP[i] );
  }

  for(i=0;listP[i]!=NULL;i++){
    ld[*j]=malloc(sizeof(struct ListaDecrescente));
    ld[*j]->string =(char*)malloc(sizeof(char) * strlen(listP[i]));
    strcpy(ld[*j]->string , listP[i]);
    cp = (compra)retornaDadosProduto(catProd , listP[i]);
    ld[*j]->qtd = ((cp->qtdN) + (cp->qtdP));
    printf("string = %s\n", ld[*j]->string );
    printf("qtd = %d\n", ld[*j]->qtd );
    (*j)++;
  }

}

void iniciaListaDecrescente (listaDecrescente* ld){
  ld = malloc ((sizeof(struct ListaDecrescente)));
  ld->tamanho = 0; *//*<----- faço o primeiro malloc ; é preciso */
/*}

void quick_sort (int *a, int n) {
    int i, j, p, t;
    if (n < 2)
        return;
    p = a[n / 2];
    for (i = 0, j = n - 1;; i++, j--) {
        while (a[i] < p)
            i++;
        while (p < a[j])
            j--;
        if (i >= j)
            break;
        t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
    quick_sort(a, i);
    quick_sort(a + i, n - i);
}*/
