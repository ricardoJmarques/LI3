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

compra insereCompra(compra c, int qtd, float preco, char tipo){
  if (c!=NULL){
    if (tipo == 'N')
      c->qtdN += qtd;
    else
      c->qtdP += qtd;
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

CatalogoFilial iniciaCatFilial(CatalogoClientes catCli, int nfiliais){
  int i, j;
  CatalogoFilial catFil = malloc(sizeof(struct ListaFilial)*nfiliais);
  for (i=0;i<nfiliais;i++){
    for (j = 0; j<FMTAM; j++){
      catFil[i].catMes[j] = copiaCatClientes(catCli);
      catFil[i].comprasValidas[j] = 0;
    }
  }
  return catFil;
}

CatalogoFilial insereVendaFilial(CatalogoFilial catFil, Cliente c, Produto p, int qtd, float preco, int mes, char tipo, int filial){
  int i, j;
  CatalogoProdutos catProd;
  compra cp;
  i = filial-1;
  j = mes - 1;
    
  if ((catProd=(CatalogoProdutos)retornaDadosCliente(catFil[i].catMes[j], c)) == NULL){
    catProd = iniciaCatProdutos();
    insereDadosCliente(catFil[i].catMes[j], c, catProd);
    insereProduto(catProd, p);
  }

  if ((cp=(compra)retornaDadosProduto(catProd, p)) == NULL){
    cp = insereCompra(cp, qtd, preco, tipo);
    insereDadosProduto(catProd, p, cp);
  }
  else{
    cp = insereCompra(cp, qtd, preco, tipo);
  }

  catFil[i].comprasValidas[j]++;
  return catFil;
}

void removeCatFilial(CatalogoFilial catFil, int nfiliais){
  int i,j,k,l;
  char c;
  char ch[10];
  CatalogoProdutos catProd;
  CatalogoClientes catCli;
  for (i=0; i<nfiliais; i++){
    for (j=0; j<FMTAM; j++){
      c = 'A';
      for (k=0; k<FCTAM; k++){
        for (l=MINCLIENTE; l<=MAXCLIENTE; l++){
          sprintf(ch,"%c%d",c , l);
          if ((catProd = (CatalogoProdutos)retornaDadosCliente(catFil[i].catMes[j], ch)) != NULL){
          removeCatProdutos2(catProd);
          }
        }
      c++;
      }
    removeCatClientes(catFil[i].catMes[j]);
    }
  }
  free(catFil);
}

int totalCompras(CatalogoFilial catFil, int nfiliais){
  int i,j,total;
  total=0;
  for (i=0; i<nfiliais; i++){
    for (j=0; j<FMTAM; j++){
      total += catFil[i].comprasValidas[j];
    }
  }
  return total;
}


int clientesGold (CatalogoClientes catCli, CatalogoFilial catFil , int nfiliais , int totalClientes){
  int i,j,k,l , resultado,controlo , controlo2;
  CatalogoProdutos catProd;
  char** str;
  str= malloc(sizeof(char*) * totalClientes);
  k=0;
  retornaClientes(catCli , str, &k);
  resultado = 0;
  /*
  for(i=0;i<k;i++)
    printf("%s\n",str[i] );*/

  for(l=0;l<k;l++){
    controlo=1;
    for(i=0;i<nfiliais;i++){
      controlo2 = 1;
      for(j=0;j<FMTAM && controlo2 == 1 ;j++){
        if(retornaDadosCliente(catFil[i].catMes[j], str[l]) != NULL){
          controlo2=0;
        }
      }
      if(controlo2 !=0)
        controlo=0;
    }
    if(controlo==1)
      resultado++;/*meter para a string*/
  }

    return resultado;
}

int clientesContemProduto (CatalogoClientes catCli, CatalogoFilial catFil , Produto p , int filial , int totalClientes){
  int i,k,l,totalP,totalN;
  CatalogoProdutos catProd;
  char** str;
  compra cp;
  str= malloc(sizeof(char*) * totalClientes);
  k=0;
  totalN=0;
  totalP=0;
  retornaClientes(catCli , str, &k);
  
  for(i=0;i<FMTAM;i++){
    for(l=0;l<k;l++){
      if((catProd = (CatalogoProdutos)retornaDadosCliente(catFil[filial-1].catMes[i] , str[l])) != NULL){
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