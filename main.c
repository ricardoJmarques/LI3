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
/*  CatalogoFilial teste4;
*/

  teste = iniciaCatClientes();
  teste2 = iniciaCatProdutos();
  teste3 = iniciaCatFaturacao(nfiliais);
/*  teste4 = iniciaCatFilial(nfiliais); 
*/
  teste = abreFicheiroClientes(teste);
  teste2 = abreFicheiroProdutos(teste2);
  abreFicheiroVendas(teste3, teste, teste2);

  printf("Total de Clientes: %d.\n", totalClientes(teste));
  printf("Total de Produtos: %d.\n", totalProdutos(teste2));
  printf("Total de Vendas: %d.\n", totalVendas(teste3));

  removeCatClientes(teste);
  removeCatProdutos(teste2);
  removeCatFaturacao(teste3, nfiliais);
/*  removeCatFilial(teste4, nfiliais);
*/
  return 0;
}
