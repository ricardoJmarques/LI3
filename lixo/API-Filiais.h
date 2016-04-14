#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"

#ifndef API_FILIAIS_H
#define API_FILIAIS_H

typedef struct venda *catFilial;

catFilial iniciaCatFilial();
catFilial insereVendaFilialProdutos (catFilial cat, char* venda);
catFilial insereVendaFilialClientes (catFilial cat, char* venda)

#endif