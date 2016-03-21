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
void gdbbreak(BTree t); //para fazer breaks quando me apetecer no gdb


int main () {
	int grow=0;
	BTree new;
	new = insertAVL (NULL,100,&grow);
	new = insertAVL (new,50,&grow);
	new = insertAVL (new,30,&grow);
	new = insertAVL (new,10,&grow);
	new = insertAVL (new,20,&grow);
	new = insertAVL (new,15,&grow);
	new = insertAVL (new,48,&grow);
	new = insertAVL (new,88,&grow);
	new = insertAVL (new,12,&grow);
	new = insertAVL (new,16,&grow);
	new = insertAVL (new,798,&grow);
	new = insertAVL (new,13,&grow);
	new = insertAVL (new,56,&grow);
	new = insertAVL (new,48,&grow);
	new = insertAVL (new,31,&grow);
	new = insertAVL (new,42,&grow);
	gdbbreak ( new );
}

BTree insertAVL(BTree t, int x, int *grow) { //função principal de inserção na AVL
	if (t==NULL) { //quando chega a uma folha da arvore cria um nodo 
	t = (BTree)malloc(sizeof(struct btree));
	t->value=x;
	t->right = t->left = NULL;
	t->balance = 0;
	*grow = 1;
	}
	else 
		if (x>(t->value)) // testa se o valor a inserir e maior que o valor do nodo
				t = insertRight(t,x,grow); // insere a direita
		else
			t = insertLeft(t,x,grow); // insere a esquerda se o valor a inserir for menor que o valor do nodo
	return t;
}

BTree insertRight(BTree t, int x, int *grow) { //insere no ramo da direita
	t->right = insertAVL(t->right,x,grow); // procura na arvore uma folha adequada
	if (*grow) // a variável grow assinala o crescimento da arvore, ou seja, quando for adicionado um nodo (fazer malloc) grow passa a 1
		switch (t->balance) {
			case -1: //se inseriu a direita e a arvore estiver pesada à esquerda fica balanceada (0)
				t->balance = 0;
				*grow = 0;
				break;
			case 0:	// se inseriu a direita e a arvore estiver balanceada fica pesada a direita (1)
				t->balance = 1;
				*grow = 1; //a variavel grow fica a 1 pq a arvore cresceu e será balancear na proxima vez que se insira um nodo nessa árvore
				break;
			case 1: // se inseriu a direita e a arvore estiver pesada a direita e necessario balancear à direita
				t = balanceRight(t);
				*grow = 0;
		}
	return t;
}

BTree insertLeft(BTree t, int x, int *grow) { //insere no ramo da esquerda
	t->left = insertAVL(t->left,x,grow); //procura na arvore um folha adequada
	if (*grow)	// a variável grow assinala o crescimento da arvore, ou seja, quando for adicionado um nodo (fazer malloc) grow passa a 1
		switch (t->balance) {
			case -1: // se inseriu a esquerda e a arvore estiver pesada a esquerda e necessario balancar a esquerda
				t = balanceLeft(t);
				*grow = 0; 
				break;
			case 0: // se inseriu a esquerda e a arvore estiver balanceada fica pesada a esquerda
				t->balance = -1;
				*grow = 1; //a variavel grow fica a 1 pq a arvore cresceu e será balancear na proxima vez que se insira um nodo nessa sub-árvore
				break;
			case 1: // se inseriu a esquerda e a arvore estiver balanceada a direita fica balanceada
				t->balance = 0;
				*grow = 0;
		}
	return t;
}

BTree balanceRight(BTree t) { 
	BTree aux;
	if (t->right->balance==1) { // deteta se e rotação simples ou dupla
	t = rotateLeft(t); // Rotacao simples a esquerda
	t->balance = 0; //corrige os fator de balanço da arvore
	t->left->balance = 0;
	}
	else {
	//Dupla rotacao
	t->right = rotateRight(t->right); // rotação a direita
	t = rotateLeft(t); // rotação a esquerda
	switch (t->balance) { // corrige o fator balanceador das sub-arvores 
		case 0: // se a arvore estivesse balanceada continua balanceada
			t->left->balance = 0;
			t->right->balance = 0;
			break;
		case -1: // se a arvore estivesse pesada a esquerda a sub-arvore da direita fica pesada a direita depois das rotações, e a da esquerda fica balanceada
			t->left->balance = 0;
			t->right->balance = 1;
			break;
		case 1: // // se a arvore estivesse pesada a direita a sub-arvore da esquerda fica pesada a esquerda depois das rotações, e a da direita fica balanceada
			t->left->balance = -1;
			t->right->balance = 0;
	}
	t->balance = 0; // balanceia a raiz da arvore que foi balanceada
	}
	return t;
}

BTree balanceLeft(BTree t) { 
	BTree aux;
	if (t->left->balance==-1) { //deteta se e rotação simples ou dupla
	t = rotateRight(t); // rotação simples a direita
	t->balance = 0; //corrige os fatores balanceadores da arvore
	t->right->balance = 0;
	}
	else {
	//Dupla rotacao
	t->left = rotateLeft(t->left); //rotação a esquerda
	t = rotateRight(t); //rotação a direita
	switch (t->balance) { // corrige o fator balanceador das sub-arvores
		case 0: //se a arvore estivesse balanceada continua balanceada, tal como as suas sub-arvores
			t->left->balance = 0;
			t->right->balance = 0;
			break;
		case -1: //se a arvore estivesse pesada a esqerda, a sub-arvore da esquerda fica pesada a direita e a sub-arvore da direita fica balanceada 
			t->left->balance = 1;
			t->right->balance = 0;
			break;
		case 1:	// se a arvore estivesse pesada a direita, a sub-arvore da esquerda fica balanceada e a sub-arvore da direita fica pesada a esquerda
			t->left->balance = 0;
			t->right->balance = -1;
	}
	t->balance = 0; //balanceia a raiz da arvore que foi balanceada 
	}
	return t;
}

BTree rotateRight(BTree t) { /* rotação simples a direita        	  t->(5)        t->(4)<-aux  	*/
	BTree aux;											    /*  	     /             / \			*/
	if ((! t) || (! t->left)){								/*    aux->(4)   =>      (3) (5)		*/
	}							    						/*  	   /      						*/
	else {													/*	  	 (3)           					*/
		aux = t->left;
 		t->left = aux->right;																					
		aux->right = t;											
		t = aux;												
	}
return t;
}

BTree rotateLeft(BTree t) { /* rotação simples a esquerda      t->(3)			 t->(4)<-aux 		*/
	BTree aux;												/*		  \				/ \				*/
	if ((! t) || (! t->right)) {							/*	 aux->(4)   =>    (3) (5)			*/
	}														/*			\							*/
	else {													/*		    (5)							*/
	aux = t->right;											
	t->right = aux->left;									
	aux->left = t;											
	t = aux;												
	}														
return t;
}

void gdbbreak (BTree t) {
	printf("cyka blyat\n");
}
