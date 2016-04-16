#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl-strings.h"

typedef struct btree {
	int balance; 
	char *string;
	void *dados;
	struct btree *left, *right;
}Node;

/*typedef struct btree *BTree;*/

BTree insertAVL(BTree t, char *str, int *grow, void *dados) { 
	if(t==NULL) { 
	  t = (BTree)malloc(sizeof(struct btree));
	  t->string = str;
      t->dados = dados;
	  t->right = t->left = NULL;
	  t->balance = 0;
	  *grow = 1;
	}
	else 
	  if (strcmp(t->string , str) < 0) 
	    t = insertRight(t,str,grow,dados); 
	  else
		t = insertLeft(t,str,grow,dados); 
	return t;
}

BTree insertRight(BTree t, char* str, int *grow, void *dados) {
	t->right = insertAVL(t->right,str,grow,dados);
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

BTree insertLeft(BTree t, char* str, int *grow, void *dados) { 
	t->left = insertAVL(t->left,str,grow,dados); 
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
	if (t->right->balance==1) { 
	t = rotateLeft(t); 
	t->balance = 0; 
	t->left->balance = 0;
	}
	else {
	
	t->right = rotateRight(t->right);
	t = rotateLeft(t);
	if(t->right && t->left){ 
	switch (t->balance && t->left && t->right) { 
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
			break;
	}
	t->balance = 0; 
	}
	}


	return t;
}

BTree balanceLeft(BTree t) { 
	if (t->left->balance==-1) { 
	t = rotateRight(t); 
	t->balance = 0; 
	t->right->balance = 0;
	}
	else {
	
		t->left = rotateLeft(t->left); 
		t = rotateRight(t); 
		if(t->right && t->left){
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
				break;
		}
	t->balance = 0;
	} 
	}
	return t;
}

BTree rotateRight(BTree t) { 
	BTree aux;										
	if ((! t) || (! t->left)){								
	}							    	   						
	else {
		aux = t->left;														  	
 		t->left = aux->right;																					
		aux->right = t;											
		t = aux;												
	}
return t;
}

BTree rotateLeft(BTree t) { 
	BTree aux;												
	if ((! t) || (! t->right)) {							
	}														
	else {													
	aux = t->right;											
	t->right = aux->left;									
	aux->left = t;											
	t = aux;												
	}														
return t;
}
/*

BTree rotateLeft (BTree a) {
	if(a->left){
		BTree b  = a->right;
		a->right = b->left;
		b->left  = a;
		return b;
	}
}

BTree rotateRight (BTree a) {
	if(a->right){
		BTree b  = a->left;
		a->left  = b->right;
		b->right = a;
		return b;
	}

}
*/


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

void* exists2 (BTree t, char *str) {
	int n;
	BTree aux;
	aux = t;
	while(aux!=NULL){
		n = strcmp(aux->string , str);
		if(n == 0)
			return (void*)aux->string;
		else{
			if (n > 0)
				aux = aux->left;
			else aux = aux->right;
		}
	}
	return NULL;
}

void* retornaDados (BTree t, char *str) {
	int n;
	BTree aux;
	aux = t;
	while(aux!=NULL){
		n = strcmp(aux->string , str);
		if(n == 0){
			return (void*)aux->dados;
	    }
		else{
			if (n > 0)
				aux = aux->left;
			else aux = aux->right;
		}
	}
	return NULL;
}

BTree deleteAvl(BTree t)  {
    if (t){
	    deleteAvl(t->left);
	    t->left = NULL;
	    deleteAvl(t->right);
	    t->right = NULL;
	    free(t->string);
        free(t->dados);
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

char** criaArrayString(BTree t, int tamString, int tamAVL){
	char** str;
	int i=0; /*indice do array*/
	str  = malloc (sizeof(char*) * tamAVL); /*aloca o array de strings*/
	criaArrayStringaux(t , tamString, str,  &i);
	return str;
}

BTree avlCopy (BTree t){
	BTree tmp;
	char *c;
	if(t){
	 	tmp = (BTree)malloc(sizeof(struct btree));
		c = (char*)malloc(sizeof(char)*(strlen(t->string)+1));
		strcpy(c, t->string);
		tmp->string = c;
		tmp->dados = NULL;
	  	tmp->balance = t->balance;
	  	tmp->right = avlCopy(t->right);
	  	tmp->left = avlCopy(t->left);
	  	return tmp;
	}
	else return NULL;
}
