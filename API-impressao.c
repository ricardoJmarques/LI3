#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define PageSize 150

/*FAZER UMA STRUCT PARA CAMUFLAR O TIPO CHAR** */

/*
void imprimeString (char ** cat , int size);
int verificaNumero(char *num, int min, int max);

int main(){

	char** str;
	int i;
	str = malloc(sizeof(char*));

	for(i=0 ; i<18 ; i++){
		str[i] = malloc(sizeof(char) * 5);
		str[i] = "cyka blyat";
	}

	imprimeString(str , 18);
}
*/

void imprimeString (char** cat , int size){
	int i, numpagina,j, nump, k , controlo;
	int cmd;

	if(size%PageSize != 0)
		nump = (size/PageSize)+1;
	else nump = size/PageSize;

	printf("%d\n", nump);

	for(numpagina=0; numpagina < nump ; numpagina++){

		printf("teste=%s\n", cat[0] );
		controlo=1;

		printf("Proxima pagina [-1]\n");
		printf("Pagina anterior [-2]\n");
		printf("Saltar para a pagina [numero da pagina]\n");
		printf("Sair [-3]\n");
		scanf("%d" , &cmd);

		/*
		if(!strcmp(cmd,"exit"))
			return;
		else{
			if(!strcmp(cmd,"exit"))
				numpagina = numpagina-2;
			else{
				if(!strcmp(cmd,"proxima")){
				nao faz nada 
				}
				else{
					for(j=0,k=1 ; cmd[j]!='\n' && k ; j++){
						if(!isdigit(cmd[j])){
							k=0;
							break;
						}
					}
					if(k){
						k=atoi(cmd);
						if(k>0 && k<= nump)
							numpagina = k-1;
					}

					else{ 
						printf("comando invalido\n");
						controlo = 0;
					}
				}
			}
		}
		*/

		switch(cmd){
			case -2:
				numpagina = numpagina -2;
				break;

			case -1:
				break;

			case -3:
				return;

			default :
				if(cmd>0 && cmd<= nump){
					numpagina = cmd;
				}

				else{ 
					printf("numero de pagina invalido\n");
					controlo=0;
				}
				break;

		}

		while (getchar() != '\n' );

		printf("numpagina = %d\n", numpagina );

		for(i=numpagina*PageSize , j=0; controlo && i<size && j<PageSize ; i++ , j++)
			puts(cat[i]);

		printf("i = %d\n", i );

		printf("------------------------NOVA PAGINA-------------------------\n");

	}

}
