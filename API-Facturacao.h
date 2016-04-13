#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"

#ifndef API_FACTURACAO_H
#define API_FACTURACAO_H

typedef struct venda *catFacturacao;

catFacturacao iniciaCatFacturacao();
catFacturacao insereVenda(catFacturacao cat, char *venda);
int totalProdutosVenda(catFacturacao cat, int mes, char tipo);

#endif
