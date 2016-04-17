#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"

#ifndef API_CLIENTES_H
#define API_CLIENTES_H

typedef char* Cliente;

typedef struct ListaClientes *CatalogoClientes;

CatalogoClientes iniciaCatClientes();

CatalogoClientes copiaCatClientes(CatalogoClientes catCli);

CatalogoClientes insereCliente(CatalogoClientes catCli, Cliente c);

Boolean existeCliente(CatalogoClientes catCli, Cliente c);

int totalClientes(CatalogoClientes catCli);

int totalClientesLetra(CatalogoClientes catCli, char letra);

void removeCatClientes(CatalogoClientes catCli);

void* retornaDadosCliente(CatalogoClientes catCli, Cliente c);

#endif
