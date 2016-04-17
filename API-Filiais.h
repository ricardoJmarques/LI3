#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Clientes.h"
#include "API-Produtos.h"

#ifndef API_FILIAIS_H
#define API_FILIAIS_H

typedef struct ListaFilial *CatalogoFilial;

CatalogoFilial iniciaCatFilial(int nfiliais);

CatalogoFilial insereCompra(CatalogoFilial catFil, Cliente c, int qtd, float preco, int mes, char tipo, int filial);

int totalProdutosCompra(CatalogoFilial catFil, int mes, int filial);

Boolean existeCompra(CatalogoFilial catFil, Produto p, int filial, int mes);

void removeCatFilial(CatalogoFilial catFil, int nfiliais);

int totalCompras(CatalogoFilial catFil);

#endif
