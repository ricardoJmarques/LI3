#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Clientes.h"
#include "API-Produtos.h"

#ifndef API_FACTURACAO_H
#define API_FACTURACAO_H

typedef struct ListaFaturacao *CatalogoFaturacao;

CatalogoFaturacao iniciaCatFacturacao(int nfiliais);
catFacturacao insereVenda(catFacturacao cat, catClientes cli, catProdutos pro, char *venda);
int totalProdutosVenda(catFacturacao cat, int mes, int filial);
Boolean existeVenda(catFacturacao cat, char *produto, int filial, int mes);
void removeCatFacturacao(catFacturacao fact, int filiais);
int totalVendas(catFacturacao cat);

void retornaCoisas(catFacturacao cat, char *produto, int mes, int filial);

#endif
