#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlstrings.h"

int main () {
	int grow=0;
	BTree new;
	char nova[]= "FD1083";
	char nova1[]="AF1146";
	char nova2[]="DV1294";
	char nova3[]="FZ1089";
	char nova4[]="ZZ0459";
	new = insertAVL (NULL, nova, &grow);
	new = insertAVL (new, nova1, &grow);
	new = insertAVL (new, nova2, &grow);
	new = insertAVL (new, nova3, &grow);

	printf("new->string = %s\n", new->string );
	printf("new->left->string = %s\n", (new->left)->string );
	printf("new->right->string = %s\n", (new->right)->string );
	printf("new->right->right->string = %s\n", ((new->right)->right)->string );
	printf ("exists = %d \n",exists(new, nova4));

	/*new = removeAvl(new , nova4);*/
}

BTree insertAVL(BTree t, char* str, int *grow) { 
	if (t==NULL) { 
	int n;
	n = strlen(str);
	t = (BTree)malloc(sizeof(struct btree));
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

/*--------------FUNCOES PROCURA REMOCAO ETC...--------------*/

int exists (BTree t, char *str) {
	int n;
	BTree aux;
	aux = t;
	while(aux!=NULL){
		n = strcmp(aux->string , str);
		if(n == 0)
			return 1;
		else{
			if (n > 0)
				aux = aux->left;
			else aux = aux->right;
		}
	}
	return 0;
}
/*
BTree removeAvl (BTree t, char *str){
	if(exists(t , str)){
		while(aux!=NULL){
			n = strcmp(aux->string , str);
			if(n == 0)
			else{
				if (n > 0)
					aux = aux->left;
				else aux = aux->right;
			}
		}
	return 0;
		
	}
	return t;
}
*/
/*
void removeAll 

*/