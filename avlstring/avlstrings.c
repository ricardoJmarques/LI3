#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlstrings.h"


int main () {
	int grow=0;
	BTree new;
	char nova[] = "FD1083";
	new = insertAVL (NULL, nova, &grow);
	printf("%s\n", new->string );
	char nova1[] = "AF1146";
	new = insertAVL (new, nova1, &grow);
	printf("%s\n", (new->left)->string );

}

BTree insertAVL(BTree t, char *str, int *grow) { 
	if (t==NULL) { 
	t = (BTree)malloc(sizeof(struct btree));
	int n = strlen(str);
	t->string = malloc(sizeof(char) * n);
	strcpy(t->string , str);
	t->right = t->left = NULL;
	t->balance = 0;
	*grow = 1;
	}
	else 
		if (strcmp(t->string , str) < 0) 
				t = insertRight(t,str,grow); 
		else
			t = insertLeft(t,str,grow); 
	return t;
}

BTree insertRight(BTree t, char* str, int *grow) {
	t->right = insertAVL(t->right,str,grow);
	if (*grow)
		switch (t->balance) {
			case -1: 
				t->balance = 0;
				*grow = 0;
				break;
			case 0:	
				t->balance = 1;
				*grow = 1; 
				break;
			case 1: 
				t = balanceRight(t);
				*grow = 0;
		}
	return t;
}

BTree insertLeft(BTree t, char* str, int *grow) { 
	t->left = insertAVL(t->left,str,grow); 
	if (*grow)	
		switch (t->balance) {
			case -1: 
				t = balanceLeft(t);
				*grow = 0; 
				break;
			case 0: 
				t->balance = -1;
				*grow = 1; 
				break;
			case 1: 
				t->balance = 0;
				*grow = 0;
		}
	return t;
}

BTree balanceRight(BTree t) { 
	BTree aux;
	if (t->right->balance==1) { 
	t = rotateLeft(t); 
	t->balance = 0; 
	t->left->balance = 0;
	}
	else {
	
	t->right = rotateRight(t->right);
	t = rotateLeft(t); 
	switch (t->balance) { 
		case 0: 
			t->left->balance = 0;
			t->right->balance = 0;
			break;
		case -1: 
			t->left->balance = 0;
			t->right->balance = 1;
			break;
		case 1: 
			t->left->balance = -1;
			t->right->balance = 0;
	}
	t->balance = 0; 
	}
	return t;
}

BTree balanceLeft(BTree t) { 
	BTree aux;
	if (t->left->balance==-1) { 
	t = rotateRight(t); 
	t->balance = 0; 
	t->right->balance = 0;
	}
	else {
	
	t->left = rotateLeft(t->left); 
	t = rotateRight(t); 
	switch (t->balance) { 
		case 0: 
			t->left->balance = 0;
			t->right->balance = 0;
			break;
		case -1:
			t->left->balance = 1;
			t->right->balance = 0;
			break;
		case 1:	
			t->left->balance = 0;
			t->right->balance = -1;
	}
	t->balance = 0; 
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