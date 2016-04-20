#include <stdlib.h>
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Faturacao.h"
#include "API-Filiais.h"
#include "API-Ficheiros.h"
#include "API-impressao.h"

#define nfiliais 3

int main(){
  
  CatalogoClientes teste;
  CatalogoProdutos teste2;
  CatalogoFaturacao teste3;
  CatalogoFilial teste4[nfiliais];
  int totalvendas;
  float totalfaturado;
  totalvendas=0;
  totalfaturado=0;
  int t1,t2,t3;
  char* c = "AF1184";

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
  /*
  removeCatFaturacao(teste3, nfiliais);
  removeCatFilial(teste4, nfiliais);
  removeCatClientes(teste);
  removeCatProdutos(teste2);
  */
  /*printf("query2=%d\n", imprimeProdutosLetra(teste2 , 'A') );*/

  /*printf("total faturado %d\n" , quantidadeVendida(teste3 , 6,  "AF1184" , 4, 0) );*/

  /*int totalFaturado(CatalogoFaturacao catFact, int mes , Produto p , int filial , int np)*/

  /*produtosNinguemComprou(teste2, teste3);*/

  /*totalIntervalo (teste3, 1, 12, nfiliais , &totalvendas , &totalfaturado);
  printf("%d\n", totalvendas );
  printf("%f\n", totalfaturado );*/

 /* printf("%d\n",produtosNinguemComprou (teste2, teste3 )); */

  /*printf("%d\n" , clientesGold (teste, teste4 ,nfiliais , totalClientes(teste)));*/

  /*clientesContemProduto (teste , teste4, c , 2 , totalClientes(teste));*/
  
  return 0;


}
