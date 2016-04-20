#include <stdio.h>
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Faturacao.h"
#include "API-Filiais.h"

#ifndef API_FICHEIROS_H
#define API_FICHEIROS_H

CatalogoClientes abreFicheiroClientes(CatalogoClientes catCli);

CatalogoProdutos abreFicheiroProdutos(CatalogoProdutos catProd);

void abreFicheiroVendas(CatalogoFaturacao catFact, CatalogoFilial *catFil, CatalogoClientes catCli, CatalogoProdutos catProd);

#endif
