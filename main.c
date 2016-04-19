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
  CatalogoFilial teste4;

  teste = iniciaCatClientes();
  teste2 = iniciaCatProdutos();
  
  teste = abreFicheiroClientes(teste);
  teste2 = abreFicheiroProdutos(teste2);

  printf("Total de Clientes: %d.\n", totalClientes(teste));
  printf("Total de Produtos: %d.\n", totalProdutos(teste2));

  teste3 = iniciaCatFaturacao(teste2, nfiliais);
  teste4 = iniciaCatFilial(teste, nfiliais);

  abreFicheiroVendas(teste3, teste4, teste, teste2);

  printf("Total de Vendas: %d.\n", totalVendas(teste3, nfiliais));
  printf("Total de Compras: %d.\n", totalCompras(teste4, nfiliais));
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
  
  return 0;


}
