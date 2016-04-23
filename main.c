#include <stdlib.h>
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Faturacao.h"
#include "API-Filiais.h"
#include "API-Ficheiros.h"
#include "API-impressao.h"

#define nfiliais 3

int main(){

  int i,j;
  CatalogoClientes teste;
  CatalogoProdutos teste2;
  CatalogoFaturacao teste3;
  CatalogoFilial teste4[nfiliais];
  int totalvendas;
  float totalfaturado;
  int t1,t2,t3;
  ListaGenerica genN, genP;
/*  ListaClientes ListaC;
  listaDecrescente* ld;*/
  totalvendas=0;
  totalfaturado=0;
  char **qwe1;
  char **qwe2;
  char* c = "Z5000";
/*  char* cli = "Z5000";*/

  teste = iniciaCatClientes();
  teste2 = iniciaCatProdutos();
  
  teste = abreFicheiroClientes(teste);
  teste2 = abreFicheiroProdutos(teste2);

  printf("Total de Clientes: %d.\n", totalClientes(teste));
  printf("Total de Produtos: %d.\n", totalProdutos(teste2));

  teste3 = iniciaCatFaturacao(teste2, nfiliais);
  teste4[0] = iniciaCatFilial(teste);
  teste4[1] = iniciaCatFilial(teste);
  teste4[2] = iniciaCatFilial(teste);

  abreFicheiroVendas(teste3, teste4, teste, teste2);


  printf("Total de Vendas: %d.\n", totalVendas(teste3, nfiliais));
  t1 = totalCompras(teste4[0]);
  t2 = totalCompras(teste4[1]);
  t3 = totalCompras(teste4[2]);
    
  printf("Total de Compras Filial 1: %d.\n", t1);
  printf("Total de Compras Filial 1: %d.\n", t2);
  printf("Total de Compras Filial 1: %d.\n", t3);
  printf("Total de Compras todas as Filiais: %d.\n", t1+t2+t3);

  /*printf("query2=%d\n", imprimeProdutosLetra(teste2 , 'A') );*/

  /*printf("total faturado %d\n" , quantidadeVendida(teste3 , 6,  "AF1184" , 4, 0) );*/

  /*int totalFaturado(CatalogoFaturacao catFact, int mes , Produto p , int filial , int np)*/

  /*produtosNinguemComprou(teste2, teste3);*/

  /*totalIntervalo (teste3, 1, 12, nfiliais , &totalvendas , &totalfaturado);
  printf("%d\n", totalvendas );
  printf("%f\n", totalfaturado );*/

/* inicio da query 4 */
  /*genN = initListaGen(totalProdutos(teste2));
   
  genN = produtosNinguemComprou (teste2, teste3, nfiliais, genN);
  qwe1 = retornaListaGen(genN);
  j = retornaPosListaGen(genN);
  for (i=0; i<j; i++){
    printf("Produtos não comprado: %s\n", qwe1[i]);
  }
  printf("total Produtos não comprados: %d\n", j);
  removeListaGen(genN);
  /* fim da query 4 */


  /*printf("Clientes gold Filial 1: %d\n" , clientesGold (teste, teste4[0]));
  printf("Clientes gold Filial 2: %d\n" , clientesGold (teste, teste4[1]));
  printf("Clientes gold Filial 3: %d\n" , clientesGold (teste, teste4[2]));

/*query 8 inicio */

  /*genN = initListaGen(totalClientes(teste));
  genP = initListaGen(totalClientes(teste));
  clientesContemProduto(teste , teste4[1], c, genN, genP);
  

  qwe1 = retornaListaGen(genN);
  qwe2 = retornaListaGen(genP);

  j = retornaPosListaGen(genN);
  /*imprimeString (qwe1 , j);*/
  /*for (i=0; i<j; i++){
    printf("Cliente: %s\n", qwe1[i]);
  }
  printf("total Normal: %d\n", j);
  
  
  j = retornaPosListaGen(genP);
  /*imprimeString (qwe2 , j);*/
  /*for (i=0; i<j; i++){
    printf("Cliente: %s\n", qwe2[i]);
  }
  printf("total Promocao: %d\n", j);
  removeListaGen(genN);
  removeListaGen(genP);


  /*query 5*/

  int totalNP[nfiliais][12];
  memset(totalNP, 0, sizeof(totalNP[0][0]) * nfiliais * 12);


  for(i=0;i<nfiliais;i++){
  	comprasMes (teste4[i], c, i,totalNP);
  	printf("----------------------------\n");
  }

  for(i=0 ; i<nfiliais ; i++){
  	if(i==0)
  		printf("      ");
  	printf("filial %d  ", i+1);
  }

  printf("\n");

  for(i=0 , j=1 ;i<12;i++){
  	printf("mes=%d   ", i+1 );
  	for(j=0;j<nfiliais;j++){
  		printf("%d         ", totalNP[j][i]);
  	}
  	printf("\n");

  }


/* query 8 fim */

/*  iniciaListaDecrescente(ld);
  i=0;
  comprasDecrescente (teste4[0] , cli, 4, ld , &i );
  comprasDecrescente (teste4[1] , cli, 4, ld , &i );
  comprasDecrescente (teste4[2] , cli, 4, ld , &i );
  */ 
  removeCatFaturacao(teste3, nfiliais);
  removeCatFilial(teste4[0]);
  removeCatFilial(teste4[1]);
  removeCatFilial(teste4[2]);
  removeCatClientes(teste);
  removeCatProdutos(teste2);
 
  return 0;


}
