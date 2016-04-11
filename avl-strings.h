#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef AVL_STRINGS_H
#define AVL_STRINGS_H

typedef struct btree {
	int balance; 
	char *string;
	struct btree *left, *right;
}Node;

typedef Node *BTree;

BTree insertAVL(BTree t, char *str, int *grow);
BTree insertRight(BTree t, char* str, int *grow);
BTree insertLeft(BTree t, char* str, int *grow);
BTree balanceRight(BTree t);
BTree balanceLeft(BTree t);
BTree rotateRight(BTree t);
BTree rotateLeft(BTree t);
int exists(BTree t, char *str);
BTree deleteAvl (BTree t);
char** criaArrayString(BTree catalogo, int tamStrint, int tamAVL);

#endif
