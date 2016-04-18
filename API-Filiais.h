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

/*
int totalProdutosVenda(CatalogoFilial catFil, int mes, int filial);

Boolean existeVenda(CatalogoFilial catFil, Produto p, int filial, int mes);
*/
void removeCatFilial(CatalogoFilial catFil, int nfiliais);
/*
int totalVendas(CatalogoFilial catFil);
*/
#endif
