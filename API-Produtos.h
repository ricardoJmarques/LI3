#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"

#ifndef API_PRODUTOS_H
#define API_PRODUTOS_H

/* catalogo de clientes */
typedef  struct listaProdutos *catProdutos;

catProdutos iniciaCatProdutos();
catProdutos insereProduto(catProdutos PROD, char *produto);
Boolean existeProduto(catProdutos prod, char *produto);
int totalProdutos(catProdutos prod);
int totalProdutosLetra(catProdutos prod, char letra);
void removeCatProdutos(catProdutos prod);

#endif
