#include <stdlib.h>
#include "API-Produtos.h"
#include "API-Faturacao.h"

#define FMTAM 12
#define FCTAM 26
#define MINCLIENTE 1000
#define MAXCLIENTE 5000
#define MINPRODUTO 1000
#define MAXPRODUTO 1999

typedef struct ListaFaturacao{/*lista de clientes*/
  CatalogoProdutos catMes[FMTAM];
  int vendasValidas[FMTAM];
} lf1;
	
typedef struct Venda{
  int qtdN;
  float precoN;
  int qtdP;
  float precoP;
  } *venda;

venda insereVenda(venda v, int qtd, float preco, char tipo){
  if (v!=NULL){
    if (tipo == 'N')
      v->qtdN += qtd;
    else
      v->qtdP += qtd;
    return v;
  }
  else {
    venda aux;
    aux = (venda)malloc(sizeof(struct Venda));
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

CatalogoFaturacao iniciaCatFaturacao(CatalogoProdutos catProd, int nfiliais){
  int i, j;
  CatalogoFaturacao catFact = malloc(sizeof(struct ListaFaturacao)*nfiliais);
  for (i=0;i<nfiliais;i++){
    for (j = 0; j<FMTAM; j++){
      catFact[i].catMes[j] = copiaCatProdutos(catProd);
      catFact[i].vendasValidas[j] = 0;
    }
  }
  return catFact;
}

CatalogoFaturacao insereCompraFaturacao(CatalogoFaturacao catFact, Produto p, int qtd, float preco, int mes, char tipo, int filial){
  int i, j;
  venda vd;
  i = filial-1;
  j = mes - 1;
    
  if ((vd=(venda)retornaDadosProduto(catFact[i].catMes[j], p)) == NULL){
    vd = insereVenda(vd, qtd, preco, tipo);
    insereDadosProduto(catFact[i].catMes[j], p, vd);
  }
  else{
    vd = insereVenda(vd, qtd, preco, tipo);
  }

  catFact[i].vendasValidas[j]++;
  return catFact;
}

void removeCatFaturacao(CatalogoFaturacao catFact, int nfiliais){
  int i,j;
  for (i=0; i<nfiliais; i++){
    for (j=0; j<FMTAM; j++){
          removeCatProdutos(catFact[i].catMes[j]);
    }
  }
  free(catFact);
}

int totalVendas(CatalogoFaturacao catFact, int nfiliais){
  int i,j,total;
  total=0;
  for (i=0; i<nfiliais; i++){
    for (j=0; j<FMTAM; j++){
      total += catFact[i].vendasValidas[j];
    }
  }
  return total;
}

int quantidadeVendida (CatalogoFaturacao catFact, int mes , Produto p , int filial , int np){

/*0=venda normal 1=promocao na variavel np (depois faço parse na main com um menu so para esta query)*/

int resultado;
venda vd;
resultado = 0.0;
  
  switch(filial){
    case 1:

      vd = (venda)retornaDadosProduto(catFact[0].catMes[mes-1] , p);
      if(vd != NULL){
        if(np == 0){
          resultado = (vd->qtdN);
        }
        else resultado = (vd->qtdP);
      }
      break;
    
    case 2:
      
      vd = (venda)retornaDadosProduto(catFact[1].catMes[mes-1] , p);
      if(vd != NULL){
        if(np == 0){
          resultado = (vd->qtdN);
        }
        else resultado = (vd->qtdP);
      }
      break;
    
    case 3:
      
      vd = (venda)retornaDadosProduto(catFact[2].catMes[mes-1] , p);
      if(vd != NULL){
        if(np == 0){
          resultado = (vd->qtdN);
        }
        else resultado = (vd->qtdP);
      }
      break;
    
    default:
      
      vd = (venda)retornaDadosProduto(catFact[0].catMes[mes-1] , p);
      if(vd != NULL){
        if(np == 0 ){
          resultado += (vd->qtdN);
        }
        else resultado += (vd->qtdP);
      }
      
      vd = (venda)retornaDadosProduto(catFact[1].catMes[mes-1] , p);
      if(vd != NULL){
        if(np == 0){
          resultado += (vd->qtdN);
        }
        else resultado += (vd->qtdP);
      }
      
      vd = (venda)retornaDadosProduto(catFact[2].catMes[mes-1] , p);
      if(vd != NULL){
        if(np == 0){
          resultado += (vd->qtdN);
        }
        else resultado += (vd->qtdP);
      }
      break;
  }

  return resultado;

}


/*
int produtosNinguemComprou (CatalogoProdutos catProd, CatalogoFaturacao catFact){


  int j,i,k;
  char** str;
  char** resultado;
  char* p;
  str = malloc(sizeof(char*));
  j=0;
  k=0;
  for(i=0;i<26;i++){
    avlInorder(catProd->lista[i] ,str,  &j);
  }

  resultado = malloc(sizeof(char*) * j);
  for(i=0 ; i<j ; i++){
    p = malloc(sizeof(char) * strlen(str[i]));
    p = strcpy(p,str[i]);
    for(j=0 ; j<=11 ; j++){
      if(retornaDadosProduto(catFact[0].catMes[j], p) == NULL && retornaDadosProduto(catFact[1].catMes[j], p) == NULL && retornaDadosProduto(catFact[2].catMes[j], p) == NULL)
        resultado[k]=malloc(sizeof(char) * strlen(p));
        strcpy(resultado[k],p);
        k++;
    }
  }

  return k;
}
*/
/*
int produtosNinguemComprou (CatalogoFaturacao catFact){
  

  for(i=0 ; i<=11 ; i++){
    int j0,j1,j2;
    char** str0,str1,str2;
    str0 = malloc(sizeof(char*));
    str1 = malloc(sizeof(char*));
    str2 = malloc(sizeof(char*));
    j0=0;
    j1=0;
    j2=0;
    avlInorder(catProd->lista[i] , str0 , &j0);
    avlInorder(catProd->lista[i] , str1 , &j1);
    avlInorder(catProd->lista[i] , str2 , &j2);
    for(j=0 ; j<=11 ; j++){
      if(retornaDadosProduto(catFact[0].catMes[j], p) == NULL && retornaDadosProduto(catFact[1].catMes[j], p) == NULL && retornaDadosProduto(catFact[2].catMes[j], p) == NULL) 
    }
  }
}
*/