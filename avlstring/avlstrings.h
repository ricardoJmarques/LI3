
typedef struct btree {
	int balance;
	int hidden; /* 0 visivel 1 escondido*/ 
	char* string;
	struct btree *left, *right;
} Node;

typedef Node *BTree;

BTree insertAVL(BTree t, char *str, int *grow);
BTree insertRight(BTree t, char* str, int *grow);
BTree insertLeft(BTree t, char* str, int *grow);
BTree balanceRight(BTree t);
BTree balanceLeft(BTree t);
BTree rotateRight(BTree t);
BTree rotateLeft(BTree t);
void gdbbreak(BTree t);
int exists (BTree t, char *str);
BTree removeAvl (BTree t, char *str);