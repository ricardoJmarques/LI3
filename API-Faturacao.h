#include <stdlib.h>
#include "API-Produtos.h"

#ifndef API_FACTURACAO_H
#define API_FACTURACAO_H

typedef struct ListaFaturacao *CatalogoFaturacao;

CatalogoFaturacao iniciaCatFaturacao(CatalogoProdutos catProd, int nfiliais);

CatalogoFaturacao insereCompraFaturacao(CatalogoFaturacao catFact, Produto p, int qtd, float preco, int mes, char tipo, int filial);

void removeCatFaturacao(CatalogoFaturacao catFact, int nfiliais);

int totalVendas(CatalogoFaturacao catFact, int nfiliais);

int quantidadeVendida(CatalogoFaturacao catFact, int mes , Produto p , int filial , int np);

void totalIntervalo (CatalogoFaturacao catFact, int mesi, int mess, int nfiliais , int* totalvendas , float* totalfaturado);

ListaGenerica produtosNinguemComprou (CatalogoProdutos catProd, CatalogoFaturacao catFact , int nfiliais, ListaGenerica lg);

#endif
