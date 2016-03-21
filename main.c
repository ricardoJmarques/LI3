#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Vendas.h"
#include "API-Utils.h"

int main(){
  char *clientes = NULL;
  char *produtos = NULL;
  char *vendas = NULL;
  char *mapaProdutos = NULL;
  char *mapaClientes = NULL;
  
  int tamClientes = 0;
  int tamProdutos = 0;
  int tamVendas = 0;
  FILE *fichClientes;
  FILE *fichProdutos;
  FILE *fichVendas;

  mapaClientes = (char *)malloc(sizeof(char) * 26 * 10000);
  memset(mapaClientes, 0x00, sizeof(char) * 26 * 10000);

  mapaProdutos = (char *)malloc(sizeof(char) * 26 * 26 * 1000);
  memset(mapaProdutos, 0x00, sizeof(char) * 26 * 26 * 1000);

  fichClientes = fopen("fichTeste/Clientes.txt", "r");
  if (fichClientes != NULL){
    printf("Ficheiro Clientes.txt aberto com sucesso\n"); 
    clientes = criaArray(20000, 10);
    if(clientes != NULL)
      tamClientes = preencheArray(fichClientes, clientes, 20000, 10);
    else
      printf("erro qefsfndifgnifdgn\n");
    fclose(fichClientes);
    if (tamClientes != 0 && mapaClientes != NULL)
      criaMapaCliente(mapaClientes, clientes, tamClientes);
  } 
  
  fichProdutos = fopen("fichTeste/Produtos.txt", "r");
  if (fichProdutos != NULL){
    printf("Ficheiro Produtos.txt aberto com sucesso\n");
    produtos = criaArray(200000, 10);
    if (produtos != NULL)
      tamProdutos = preencheArray(fichProdutos, produtos, 200000, 10);
    fclose(fichProdutos);
    if (tamProdutos != 0 && mapaProdutos != NULL)
      criaMapaProduto(mapaProdutos, produtos, tamProdutos);
  }


  fichVendas = fopen("fichTeste/Vendas_1M.txt", "r");
  if (fichVendas != NULL){
    vendas = criaArray(1000000, 40);
    if (vendas != NULL)
      tamVendas = preencheArrayVendas(fichVendas, vendas, mapaProdutos, mapaClientes);
    fclose(fichVendas);
  }

  if (clientes != NULL)
    free(clientes);
  if (produtos != NULL)
    free(produtos);
  if (vendas != NULL)
    free(vendas);
  if (mapaClientes != NULL)
    free(mapaClientes);
  if (mapaProdutos != NULL)
    free(mapaProdutos);

  printf("Clientes: %d | Produtos: %d | Vendas: %d\n", tamClientes, tamProdutos, tamVendas);
  return 0;
}
