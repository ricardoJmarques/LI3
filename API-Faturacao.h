#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Clientes.h"
#include "API-Produtos.h"

#ifndef API_FACTURACAO_H
#define API_FACTURACAO_H

typedef struct ListaFaturacao *CatalogoFaturacao;

CatalogoFaturacao iniciaCatFaturacao(int nfiliais);
CatalogoFaturacao insereVenda(CatalogoFaturacao catFact, Produto p, int qtd, float preco, int mes, char tipo, int filial);
int totalProdutosVenda(CatalogoFaturacao cat, int mes, int filial);
Boolean existeVenda(CatalogoFaturacao cat, char *produto, int filial, int mes);
void removeCatFaturacao(CatalogoFaturacao fact, int filiais);
int totalVendas(CatalogoFaturacao cat);

void retornaCoisas(CatalogoFaturacao cat, char *produto, int mes, int filial);

#endif
