#include <stdlib.h>
#include "avl-strings.h"
#include "API-Utils.h"
#include "API-Clientes.h"
#include "API-Produtos.h"

#ifndef API_FILIAIS_H
#define API_FILIAIS_H

typedef struct ListaFilial *CatalogoFilial;

typedef struct ListaDecrescente *listaDecrescente;

CatalogoFilial iniciaCatFilial(CatalogoClientes catCli);

CatalogoFilial insereVendaFilial(CatalogoFilial catFil, Cliente c, Produto p, int qtd, float preco, int mes, char tipo);

void removeCatFilial(CatalogoFilial catFil);

int totalCompras(CatalogoFilial catFil);

BTree clientesGold (CatalogoClientes catCli, CatalogoFilial catFil, int* j, BTree bt); /*query 7*/

void clientesContemProduto (CatalogoClientes catCli, CatalogoFilial catFil , Produto p, ListaGenerica genN, ListaGenerica genP); /*query 8*/
/*
void comprasDecrescente (CatalogoFilial catFil , Cliente c, int mes, listaDecrescente* ld , int* j);

void iniciaListaDecrescente (listaDecrescente* ld);
*/
#endif
