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
    if (tipo == 'N'){
      v->qtdN += qtd;
      if(v->precoN == 0)
        v->precoN = preco;
    }
    else{
      v->qtdP += qtd;
      if(v->precoP == 0)
        v->precoP = preco;
    }
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

int quantidadeVendida (CatalogoFaturacao catFact, int mes , Produto p , int filial , int np){/*query 3*/

/*0=venda normal 1=promocao na variavel np (depois faço parse na main com um menu so para esta query)*/

int resultado;
venda vd;
resultado = 0;
  
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

void totalIntervalo (CatalogoFaturacao catFact, int mesi, int mess, int nfiliais , int* totalvendas , float* totalfaturado){ 
  int i,j,k,l;
  venda vd;
  char** str;
  str= malloc(sizeof(char*) * 200000);
  k=0;


  retornaProdutos(catFact[0].catMes[0] , str, &k); /*cria array com os produtos*/


  for(i=0;i<nfiliais;i++){
    for(j=mesi-1;j<=mess-1;j++){
      for(l=0;l<k;l++){
          if((vd = (venda)retornaDadosProduto(catFact[i].catMes[j] , str[l])) != NULL){
            (*totalvendas) += (vd->qtdN);
            (*totalvendas) += (vd->qtdP);
            (*totalfaturado) += ((vd->qtdN)*(vd->precoN));
            (*totalfaturado) += ((vd->qtdP)*(vd->precoP));
          }
      }
      

    }
  }
}


int produtosNinguemComprou (CatalogoProdutos catProd, CatalogoFaturacao catFact, int nfiliais){/*recebe a str*/
  
  int i,j,k,l , resultado,controlo;
  venda vd;
  char** str;
  str= malloc(sizeof(char*) * 200000);
  k=0;
  retornaProdutos(catProd , str, &k);
  resultado = 0;

  for(l=0;l<k;l++){
    controlo=1;
    for(i=0;i<nfiliais;i++){
      for(j=0;j<FMTAM;j++){
        if(retornaDadosProduto(catFact[i].catMes[j], str[l]) != NULL)
          controlo=0;
      }
    }
    if(controlo==1)
      resultado++;/*meter para a string*/
  }

    return resultado;

}
