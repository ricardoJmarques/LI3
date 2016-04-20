#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Clientes.h"
#include "API-Produtos.h"

#ifndef API_FILIAIS_H
#define API_FILIAIS_H

typedef struct ListaFilial *CatalogoFilial;

CatalogoFilial iniciaCatFilial(CatalogoClientes catCli, int nfiliais);

CatalogoFilial insereVendaFilial(CatalogoFilial catFil, Cliente c, Produto p, int qtd, float preco, int mes, char tipo, int filial);

void removeCatFilial(CatalogoFilial catFil, int nfiliais);

int totalCompras(CatalogoFilial catFil, int nfiliais);

int clientesGold (CatalogoClientes catCli, CatalogoFilial catFil , int nfiliais , int totalClientes);

int clientesContemProduto (CatalogoClientes catCli, CatalogoFilial catFil , Produto p , int filial , int totalClientes);

#endif
