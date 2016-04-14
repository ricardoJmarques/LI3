#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Clientes.h"
#include "API-Produtos.h"

#ifndef API_FACTURACAO_H
#define API_FACTURACAO_H

typedef struct venda *catFacturacao;

catFacturacao iniciaCatFacturacao();
catFacturacao insereVenda(catFacturacao cat, catClientes cli, catProdutos pro, char *venda);
int totalProdutosVenda(catFacturacao cat, int mes, int filial);
Boolean existeVenda(catFacturacao cat, char *cliente, int filial, int mes);
void removeCatFacturacao(catFacturacao fact, int filiais);

#endif
