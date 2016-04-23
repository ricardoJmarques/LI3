#include <stdlib.h>
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Filiais.h"
#include "avl-strings.h"

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


BTree clientesGold (CatalogoClientes catCli, CatalogoFilial catFil, int* l, BTree bt){ /*query x*/
  int i,j,k,controlo, grow;
  CatalogoProdutos catProd;
  ListaClientes ListaC;
  ListaC = retornaListaClientes(catCli);
  k=totalClientes(catCli);
  grow=0;
  bt = NULL;
  for(i=0;i<k;i++){
    if(retornaDadosCliente(catFil->cliente, ListaC[i]) != NULL){
      if(exists(bt , ListaC[i]) == 0){
        (*l)++;
        bt = insertAVL(bt, ListaC[i] , &grow, NULL);
      }
    }
  }
  removeListaClientes(ListaC, k);
  return bt;
}

void clientesContemProduto (CatalogoClientes catCli, CatalogoFilial catFil , Produto p, ListaGenerica genN, ListaGenerica genP){/*query 8*/
  int i,j,k,flag;
  compra cp;
  ListaClientes ListaC;
  listaMes lstMes;
  ListaC = retornaListaClientes(catCli);
  k=totalClientes(catCli);
  flag=0;
  for(j=0;j<k;j++){
    if((lstMes=(listaMes)retornaDadosCliente(catFil->cliente, ListaC[j])) != NULL){
      for(i=0; flag==0 && i<FMTAM; i++){
        if((cp = (compra) retornaDadosProduto(lstMes->catMes[i] , p)) != NULL){
          flag = 1;
          if(cp->qtdP != 0) genP = insereListaGen(genP, ListaC[j]);
          if(cp->qtdN != 0) genN = insereListaGen(genN, ListaC[j]);
        }
      }
      flag = 0;
    }
  }
}

void comprasMes (CatalogoFilial catFil, Cliente c, int filial, int** totalNP){

	int i,j,k;
	listaMes lstMes;
	CatalogoProdutos catProd;
	ListaProdutos lstProds;
	compra cp;

	k=0;

	catProd = iniciaCatProdutos();

	/*lstMes=(listaMes)retornaDadosCliente(catFil->cliente, c);*/

	if((lstMes=(listaMes)retornaDadosCliente(catFil->cliente, c)) != NULL){

		for(i=0;i<FMTAM;i++){
			k=0;
			catProd = lstMes->catMes[i];
			lstProds = malloc(sizeof(char) * totalProdutos(catProd) * FMTAM );
			retornaProdutos (catProd , lstProds, &k);

			for(j=0; j<k && k!=0; j++){
				cp = (compra)retornaDadosProduto(catProd , lstProds[j]);
				totalNP[filial][i] += ((cp->qtdN) + (cp->qtdP));
			}
			removeListaProdutos(lstProds , k);
		}
	}
}



