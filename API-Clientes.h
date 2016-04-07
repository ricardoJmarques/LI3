#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"

#ifndef API_CLIENTES_H
#define API_CLIENTES_H

/* catalogo de clientes */
typedef struct listaClientes *catClientes;

catClientes iniciaCatClientes();
catClientes insereCliente(catClientes ccs, char *cliente);
Boolean existeCliente(catClientes ccs, char* cliente);
int totalClientes(catClientes ccs);
int totalClientesLetra(catClientes ccs, char letra);
void removeCatClientes(catClientes ccs);

#endif
