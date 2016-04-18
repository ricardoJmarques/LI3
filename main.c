#include <stdlib.h>
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Faturacao.h"
#include "API-Filiais.h"
#include "API-Ficheiros.h"

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

  teste3 = iniciaCatFaturacao(nfiliais);
  teste4 = iniciaCatFilial(teste, nfiliais);

  abreFicheiroVendas(teste3, teste4, teste, teste2);

  printf("Total de Vendas: %d.\n", totalVendas(teste3));
  /*printf("Total de Compras: %d.\n", totalCompras(teste4));*/

  removeCatFaturacao(teste3, nfiliais);
  removeCatFilial(teste4, nfiliais);
  removeCatClientes(teste);
  removeCatProdutos(teste2);

  
  return 0;
}
