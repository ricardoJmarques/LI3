#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef AVL_STRINGS_H
#define AVL_STRINGS_H

typedef struct btree *BTree;

BTree insertAVL(BTree t, char *str, int *grow, void *dados);
BTree insertRight(BTree t, char *str, int *grow, void *dados);
BTree insertLeft(BTree t, char *str, int *grow, void *dados);
BTree balanceRight(BTree t);
BTree balanceLeft(BTree t);
BTree rotateRight(BTree t);
BTree rotateLeft(BTree t);
int exists(BTree t, char *str);
void* retornaDados (BTree t, char *str);
BTree deleteAvl (BTree t);
char** criaArrayString(BTree catalogo, int tamStrint, int tamAVL);
BTree avlCopy(BTree t);
void insereDados(BTree t, char *str, void* dados);
#endif
