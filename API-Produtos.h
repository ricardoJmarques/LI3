#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"

#ifndef API_PRODUTOS_H
#define API_PRODUTOS_H

/* catalogo de clientes */
typedef char* Produto;

typedef struct ListaProdutos *CatalogoProdutos;

CatalogoProdutos iniciaCatProdutos();

CatalogoProdutos copiaCatProdutos(CatalogoProdutos catProd);

CatalogoProdutos insereProduto(CatalogoProdutos catProd, Produto p);

Boolean existeProduto(CatalogoProdutos catProd, Produto p);

int totalProdutos(CatalogoProdutos catProd);

int totalProdutosLetra(CatalogoProdutos catProd, char letra);

void removeCatProdutos(CatalogoProdutos catProd);

#endif
