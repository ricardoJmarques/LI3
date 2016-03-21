#include <stdio.h>
#include <stdlib.h>

typedef struct btree {
	int balance; // left=-1 right =1 balanced=0
	int value;
	struct btree *left, *right;
} Node;

typedef Node *BTree;

BTree insertAVL(BTree t, int x, int *grow);
BTree insertRight(BTree t, int x, int *grow);
BTree insertLeft(BTree t, int x, int *grow);
BTree balanceRight(BTree t);
BTree balanceLeft(BTree t);
BTree rotateRight(BTree t);
BTree rotateLeft(BTree t);

