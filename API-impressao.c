#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#if ((__APPLE__) || (__linux__)) /* Deteta se o SO é linux ou mac para usar comando de limpar a tela */
#define SYSTEM 1
#elif (_WIN32)                   /* Deteta se o SO é Windows para usar comando de limpar a tela */
#define SYSTEM 0
#endif					         /* Nao limpa a tela de um sistema que não é ou UNIX ou Windows */


#define PageSize 35

void imprimeString (char ** cat , int size){
	int i, numpagina,j, nump, k , controlo,l,controloDigito;
	char* cmd;

    controlo = 1;
    controloDigito = 1;
	if(size%PageSize != 0)
		nump = (size/PageSize)+2;
	else nump = size/PageSize+1;

	printf("numero de paginas = %d\n", nump);

	for(numpagina=1; numpagina < nump ; numpagina++){

		if(controlo == 0)
			numpagina--;


		controlo=1;

		printf("Proxima pagina [proxima]\n");
		printf("Pagina anterior [anterior]\n");
		printf("Saltar para a pagina [numero da pagina]\n");
		printf("limpar ecra [clear]\n");
		printf("Sair [exit]\n");
		scanf("%s" , cmd);



		for(l=0 , controloDigito =1; cmd[l]!='\0' && controloDigito ;l++){
			if( ! isdigit(cmd[l])){
				controloDigito = 0;
			}
		}

		if(!controloDigito){
			if(!strcmp(cmd , "exit"))
				return;
			else{
				if(!strcmp(cmd , "proxima")){
					/*faz nada*/
				}
				else{
					if(!strcmp(cmd , "anterior")){
						numpagina = numpagina -2;
					}
					else{
						if(!strcmp(cmd , "clear")){
							controlo = 0;
							if (SYSTEM) system ("clear");
							if (!SYSTEM) system ("cls");
						}
						else{
							printf("comando invalido\n");
							controlo = 0;
						}
					}
				}
			}
		}
		else{
			k=atoi(cmd);
			if(k>0 && k < nump){
				numpagina = k;
			}

			else {
				printf("numero de pagina invalido\n");
				controlo = 0;
			}
		}

		while (getchar() != '\n' );

		if(controlo == 1){
			if (SYSTEM) system ("clear");
			if (!SYSTEM) system ("cls");
		}

		printf("numpagina = %d\n", numpagina );

		for(i=(numpagina-1)*PageSize , j=0; controlo && i<size && j<PageSize ; i++ , j++)
			printf("%s\n",cat[i]);

	}

}
