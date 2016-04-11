#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl-strings.h"

BTree insertAVL(BTree t, char *str, int *grow) { 
	if(t==NULL) { 
	  int n;
	  n = strlen(str) + 1;
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

BTree deleteAvl(BTree t)  {
    if (t){
	    deleteAvl(t->left);
	    t->left = NULL;
	    deleteAvl(t->right);
	    t->right = NULL;
	    free(t);
    }
    return NULL;  
}

void criaArrayStringaux(BTree t, int tamString ,char** str, int* i){
	if(t){
		str[*i] = malloc(sizeof(char) * tamString); /*aloca a string */
		strcpy(str[*i] , t->string); /*copia a string*/
		(*i)++; /* incrementa o indice*/
		criaArrayStringaux(t->left , tamString ,str, i); /* cria a string para o ramo da esquerda*/
		criaArrayStringaux(t->right , tamString,str, i); /* cria a string para o ramo da direita*/

	}
}

char** criaArrayString(BTree catalogo, int tamString, int tamAVL){
	char** str;
	int i=0; /*indice do array*/
	str  = malloc (sizeof(char*) * tamAVL); /*aloca o array de strings*/
	criaArrayStringaux(catalogo , tamString, str,  &i);
	return str;

}

