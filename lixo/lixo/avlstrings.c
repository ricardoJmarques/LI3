#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlstrings.h"

int main () {
	int grow=0;
	BTree new;
	char nova[]= "E";
	char nova1[]="F";
	char nova2[]="A";
	char nova3[]="B";
	char nova4[]="C";
	new = insertAVL (NULL, nova3, &grow);
	new = insertAVL (new, nova2, &grow);
	new = insertAVL (new, nova4, &grow);
	new = insertAVL (new, nova, &grow);

	printf("new->string = %s\n", new->string );
	printf("new->left->string = %s\n", (new->left)->string );
	printf("new->right->string = %s\n", (new->right)->string );
	printf("new->right->right->hidden = %d\n", ((new->right)->right)->hidden );
	
	/*printf ("exists = %d \n",exists(new, nova3));	
	new = removeAvl(new , nova3);
	printf("new->right->right->hidden = %d\n", ((new->right)->right)->hidden );
	printf ("exists = %d \n",exists(new, nova3));*/
	printf("exists %d\n", exists(new, nova) );
	removeAvl(new , nova);

	printf("new->string = %s\n", new->string );
	printf("new->left->string = %s\n", (new->left)->string );
	printf("new->right->string = %s\n", (new->right)->string );
	printf("new->right->right->hidden = %d\n", ((new->right)->right)->hidden);
	printf("exists %d\n", exists(new, nova) );
	new = insertAVL (new, nova, &grow);
	printf("exists %d\n", exists(new, nova) );
	new = deleteAvl(new);
	printf("new->string = %s\n", new->string );


}

BTree insertAVL(BTree t, char* str, int *grow) { 
	int n;
	if (t==NULL) { 
	n = strlen(str);
	t = (BTree)malloc(sizeof(struct btree));
	t->string = malloc(sizeof(char) * n);
	strcpy(t->string , str);
	t->right = t->left = NULL;
	t->balance = 0;
	t->hidden = 0;
	*grow = 1;
	}
	else{
		n = strcmp(t->string , str);
		if(n == 0 && t->hidden == 1){
			t->hidden = 0;
			*grow = 0;
			return t;

		}

		
		else{

			if (n < 0) 
					t = insertRight(t,str,grow); 
			else
				t = insertLeft(t,str,grow); 
		}
	}
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
/*
int exists (BTree t, char* str) {
	int n;
	BTree aux;
	aux = t;
	while(aux!=NULL){
		n = strcmp(aux->string , str);
		if(n == 0 && t->hidden == 0){
			printf("existe? %s t->hidden = %d\n", aux->string,  aux->hidden);
			return 1;
		}
		else{
			if (n > 0)
				aux = aux->left;
			else aux = aux->right;
		}
	}
	return 0;
}*/

int exists (BTree t, char *str) {
	int n;
	BTree aux;
	aux = t;
	while(aux!=NULL){
		n = strcmp(aux->string , str);
		if(n == 0 && aux->hidden == 0)
			return 1;
		else{
			if (n > 0)
				aux = aux->left;
			else aux = aux->right;
		}
	}
	return 0;
}

BTree removeAvl (BTree t, char *str){
	int n;
	BTree aux;
	aux = t;
	while (aux!= NULL){
		n=strcmp(aux->string,str);
		if (n==0){
			aux->hidden = 1;
			break;
		}
		else{
			if(n<0){
				aux = aux->right;			
			}
			else {
				aux = aux->left;
			}
		}
	}

	return t;
}
/*
void deleteAvl (BTree t){
	if(t!=NULL){
		if(t->right == NULL && t->left == NULL){
			free(t->string);	
			free(t);
		}
		else{
			deleteAvl(t->right);
			deleteAvl(t->left);
		}

	}
}

*/

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



/*
void removeAvl (BTree t, char *str){
	int n,k,j;
	int* side; side para saber de que lado vem a procura 1 = right  -1 = left
	BTree aux;
	BTree* stack; stack que guarda os nodos que foram precorridos
	aux = t;
	k=0;j=0;
	stack[0]=t;
	k++;
	while (t!= NULL){
		n=strcmp(aux->string,str);
		if (n==0)
			delete(t,aux,stack,k,side,j);
		else{
			if(n<0){
				aux = t;
				t = t->right;
				stack[k]=aux;
				k++;
				side[j]=1;
				j++;			
			}
			else {
				aux = t;
				t = t->left;
				stack[k]=aux;
				k++;
				side[j]=-1;
				j++;
			}
		
		}
	}
}

void delete (BTree t , BTree parent, BTree* stack, int k, int* side, int j){
	int i;
	BTree aux, it ;
	aux = t;

	if (t->right != NULL && t->left != NULL){
		if(side[j] == 1){
			parent->right = t->left;
			for(aux=t; aux->left != NULL; aux = aux->left);
			aux->right = t->right;
			free(t->string);
			free(t);
			for(i=0; i<k-1 ; i++){
				if(side[i] == 1)
					balanceRight(stack[i]);
				else balanceLeft(stack[i]);
			}

		}


	}

	
	if(t->right == NULL){ ultimo?
		if(side == 1){
			parent->right = t->left;
			free(aux);
		}


	}
	
}

*/