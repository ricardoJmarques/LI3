#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"

#ifndef API_PRODUTOS_H
#define API_PRODUTOS_H

/* catalogo de clientes */
typedef char* Produto;

typedef char** ListaProdutos;

typedef struct StructProdutos *CatalogoProdutos;

CatalogoProdutos iniciaCatProdutos();

CatalogoProdutos copiaCatProdutos(CatalogoProdutos catProd);

CatalogoProdutos insereProduto(CatalogoProdutos catProd, Produto p);

Boolean existeProduto(CatalogoProdutos catProd, Produto p);

int totalProdutos(CatalogoProdutos catProd);

int totalProdutosLetra(CatalogoProdutos catProd, char letra);

void removeCatProdutos(CatalogoProdutos catProd);
void removeCatProdutos2(CatalogoProdutos catProd);

void* retornaDadosProduto(CatalogoProdutos catProd, Produto p);

void insereDadosProduto(CatalogoProdutos catProd, Produto p, void *dados);

int imprimeProdutosLetra (CatalogoProdutos catProd , char letra);

void retornaProdutos(CatalogoProdutos catProd , char** str, int* j);

ListaProdutos retornaListaProdutos (CatalogoProdutos catProd);

void removeListaProdutos(ListaProdutos ListP, int tamanho);

#endif
