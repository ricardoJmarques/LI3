#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "API-Clientes.h"
#include "API-Produtos.h"
#include "API-Faturacao.h"
#include "API-Filiais.h"
#include "API-Ficheiros.h"
#include "API-impressao.h"
#include "avl-strings.h"
#include <time.h>
/*time.h*/
#if ((__APPLE__) || (__linux__)) 
#define SYSTEM 1
#elif (_WIN32)                   
#define SYSTEM 
#endif

#define nfiliais 3


int main (){

	char cmd;
	int comando,carregamento ,i,j,k , c;
	int controloDeCiclo;
	CatalogoClientes teste;
	CatalogoProdutos teste2;
	CatalogoFaturacao teste3;
	CatalogoFilial teste4[nfiliais];
	ListaGenerica genN, genP;
	int t1,t2,t3;
	char* cli;
	char** str;
	char **qwe1;
  	char **qwe2;
  	int** totalNP;
  	int totalvendas;
  	float totalfaturado;
  	int mesi,mess;
  	int controlo;
  	BTree bt;
  	clock_t begin, end;
	double time_spent;
	int totalvendidoP,totalvendidoN;
	float totalfaturadoP, totalfaturadoN;
	
	carregamento = 0;
	controloDeCiclo = 1;


	if (SYSTEM)  {system ("clear");}
	if (!SYSTEM) {system ("cls");}  

	/*ESTE MENU INICIAL SÓ IRÁ SER APRESENTADO QUANDO O PROGRAMA É INICIADO. O MENU DE OPÇÕES PARA 
	O UTILIZADOR SERÁ O QUE IRÁ SEMPRE SER CONSULTADO CONFORME O RETRUCESSO DAS OPERAÇÕES*/
	printf("********************************************************************************\n");
	printf("*                 Laboratório de Informática 3 - 2015/2016                     *\n");
	printf("********************************************************************************\n");
	printf("*        PROJETO:  															   *\n");
	printf("*                   GereVendas                                                 *\n");
	printf("*                                                                              *\n");
	printf("*        DEVELOPERS:                                                           *\n");
	printf("*                   Ricardo Jorge da Silva Braga Marques - a55723              *\n");
	printf("*                   João Carlos Faria Padrão - a76438                          *\n");
	printf("*                   Rafael Dias Alves - a72629                                 *\n");
	printf("*                                                                              *\n");
	printf("*        GRUPO:                                                                *\n");
	printf("*                   nº73                                                       *\n");
	printf("*                                                                              *\n");
	printf("*        ORIENTADOR DO PROJETO/GRUPO:                                          *\n");
	printf("*                   Fernando Mário Junqueira Martins                           *\n");
	printf("*                                                                              *\n");
	printf("********************************************************************************\n");
	printf("Prima ENTER\n");
	getchar();
	


	if (SYSTEM)  {system ("clear");}
	if (!SYSTEM) {system ("cls");}

	begin = clock();

	teste = iniciaCatClientes();
	teste2 = iniciaCatProdutos();
					  
	teste = abreFicheiroClientes(teste);
	teste2 = abreFicheiroProdutos(teste2);

	printf("Total de Clientes: %d.\n", totalClientes(teste));
	printf("Total de Produtos: %d.\n", totalProdutos(teste2));

	teste3 = iniciaCatFaturacao(teste2, nfiliais);
	teste4[0] = iniciaCatFilial(teste);
	teste4[1] = iniciaCatFilial(teste);
	teste4[2] = iniciaCatFilial(teste);

	abreFicheiroVendas(teste3, teste4, teste, teste2);

	printf("Total de Vendas: %d.\n", totalVendas(teste3, nfiliais));
	t1 = totalCompras(teste4[0]);
	t2 = totalCompras(teste4[1]);
	t3 = totalCompras(teste4[2]);
						    
	printf("Total de Compras Filial 1: %d.\n", t1);
	printf("Total de Compras Filial 1: %d.\n", t2);
	printf("Total de Compras Filial 1: %d.\n", t3);
	printf("Total de Compras todas as Filiais: %d.\n", t1+t2+t3);

	end = clock();

	time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
 
	printf("tempo = %f\n", time_spent );


	while(controloDeCiclo!=0){

		printf("****************************************************************************************************************\n");
		printf("*                                               --MENU--                                                       *\n");
		printf("* 1 - Recarregar dados                                                                                         *\n");
		printf("* 2 - Listagem e contabilização de produtos iniciados por um determinado carater                               *\n");
		printf("* 3 - Dado um mês e o codigo de produto apresentar total de vendas e total faturado                            *\n");
		printf("* 4 - Apresentar lista ordenada dos códigos de produto que ninguem comprou                                     *\n");
		printf("* 5 - Dado um cliente apresenta uma tabela com o numero total de produtos comprados mês a mês                  *\n");
		printf("* 6 - Contabilizar total de vendas e total faturado consoante um intervalo de tempo                            *\n");
		printf("* 8 - Dado um produto e uma filial apresenta os clientes que compraram o produto                               *\n");
		printf("* 14 - Sair                                                                                                    *\n");
		printf("****************************************************************************************************************\n");


		printf ("Digite o numero da operação pretendida: ");
		scanf ("%d", &comando);
		

		switch (comando)
	    {
	    	case 1:
		            if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");

						begin = clock();
						
						removeCatFaturacao(teste3, nfiliais);
					    removeCatFilial(teste4[0]);
					    removeCatFilial(teste4[1]);
					    removeCatFilial(teste4[2]);
					    removeCatClientes(teste);
					    removeCatProdutos(teste2);

					    teste = iniciaCatClientes();
						teste2 = iniciaCatProdutos();
						  
						teste = abreFicheiroClientes(teste);
						teste2 = abreFicheiroProdutos(teste2);

						printf("Total de Clientes: %d.\n", totalClientes(teste));
						printf("Total de Produtos: %d.\n", totalProdutos(teste2));

						teste3 = iniciaCatFaturacao(teste2, nfiliais);
						teste4[0] = iniciaCatFilial(teste);
						teste4[1] = iniciaCatFilial(teste);
						teste4[2] = iniciaCatFilial(teste);

		    			abreFicheiroVendas(teste3, teste4, teste, teste2);


						printf("Total de Vendas: %d.\n", totalVendas(teste3, nfiliais));
						t1 = totalCompras(teste4[0]);
						t2 = totalCompras(teste4[1]);
						t3 = totalCompras(teste4[2]);
						    
						printf("Total de Compras Filial 1: %d.\n", t1);
						printf("Total de Compras Filial 1: %d.\n", t2);
						printf("Total de Compras Filial 1: %d.\n", t3);
						printf("Total de Compras todas as Filiais: %d.\n", t1+t2+t3);

						end = clock();

			           	time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
	 
			           	printf("tempo = %f\n", time_spent );


					getchar();
					getchar();

		            if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");
	    	break;
	    	
	    	case 2: /*check*/
		            if (SYSTEM)  
		            	system ("clear");
					else{
						system ("cls");
					}
		            while(getchar() != '\n');
		           	printf("Introduza a letra:");
		           	scanf("%c" , &cmd);

					begin = clock();

		           	k=0;
		           	str = imprimeProdutosLetra(teste2 , cmd , &k);
		           	
		           	end = clock();

		           	time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
 
		           	printf("tempo = %f\n", time_spent );

		           	imprimeString(str , k);	

		            if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");
	    	break;
	    	
	    	case 3:
		            if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");
		          
		           	while(getchar() != '\n');
		           	
		           	printf("Valores filial a filial[1]\nValores totais[2]\n");
		           	scanf("%d" , &c);
		           	printf("Introduza o mes\n");
		           	scanf("%d" , &mess);
		           	printf("Introduza o codigo do produto\n");
		           	cli = malloc(sizeof(char) * 7);
		           	scanf("%s" , cli);

		           	totalvendidoP=0;
		           	totalfaturadoP=0.0;
		           	totalvendidoN=0;
		           	totalfaturadoN=0.0;

		           	begin = clock();

		           	if(c==1){
		           		for(i=0;i<nfiliais;i++){

		           			totalvendidoP=quantidadeVendida(teste3,mess,cli,i,1);
		           			totalvendidoN=quantidadeVendida(teste3,mess,cli,i,0);
		           			totalfaturadoP=quantidadeFaturada(teste3,mess,cli,i,1);
		           			totalfaturadoN=quantidadeFaturada(teste3,mess,cli,i,0);

			           		printf("total faturado em Promocao na filial %d = %f\n",i, totalfaturadoP);
			           		printf("total faturado em regime normal na filial %d = %f\n",i, totalfaturadoN);
			           		printf("quantidade vendida em Promocao na filial %d = %d\n",i, totalvendidoP);
			           		printf("quantidade vendida em regime normal na filial %d = %d\n",i, totalvendidoN);
		           		}
		           	}
		           	else{
		           		
		           			totalvendidoP=quantidadeVendida(teste3,mess,cli,4,1);
		           			totalvendidoN=quantidadeVendida(teste3,mess,cli,4,0);
		           			totalfaturadoP=quantidadeFaturada(teste3,mess,cli,4,1);
		           			totalfaturadoN=quantidadeFaturada(teste3,mess,cli,4,0);

		           		printf("total faturado em Promocao = %f\n", totalfaturadoP);
		           		printf("total faturado em regime normal = %f\n", totalfaturadoN);
		           		printf("quantidade vendida em Promocao = %d\n", totalvendidoP);
		           		printf("quantidade vendida em regime normal = %d\n", totalvendidoN);
		           	}

		           	end = clock();

		           	time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
 
		           	printf("tempo = %f\n", time_spent );

		           	getchar();
		           	getchar();

		            if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");
	    	break;
	    	
	    	case 4:
		            if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");
	            	
	            	begin = clock();

					genN = initListaGen(totalProdutos(teste2));
					   
			        genN = produtosNinguemComprou (teste2, teste3, nfiliais, genN);
					qwe1 = retornaListaGen(genN);
					j = retornaPosListaGen(genN);

					end = clock();

		           	time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
 
		           	printf("tempo = %f\n", time_spent );
										
					printf("\ntotal Produtos não comprados: %d\n\n", j);
					imprimeString(qwe1 , j);
					removeListaGen(genN);

		            if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");
			break;
	    	
	    	case 5:
		            if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");

					while(getchar() != '\n');
		           	printf("Introduza o codigo do cliente:");
		           	cli = malloc(sizeof(char) * 6);
		           	scanf("%s" , cli);

		           	begin = clock();

		           	totalNP = (int **)malloc(nfiliais * sizeof(int*));
					for(i = 0; i < nfiliais; i++) 
						totalNP[i] = (int *)malloc(12 * sizeof(int));

					for(i=0;i<nfiliais;i++){
						for(j=0;j<12;j++){
							totalNP[i][j]=0;
						}
					}
	            	

				   for(i=0 ; i<nfiliais ; i++){
				   	comprasMes(teste4[i] , cli, i, totalNP);
				   }

				   end = clock();

		           time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
 
		           printf("tempo = %f\n", time_spent );

				  	for(i=0 ; i<nfiliais ; i++){
				  		if(i==0)
				  			printf("      ");
				  		printf("filial %d  ", i+1);
				  	}

				  	printf("\n");

				  	for(i=0 , j=1 ;i<12;i++){
				  		printf("mes=%d   ", i+1 );
				  		for(j=0;j<nfiliais;j++){
				  			printf("%d         ", totalNP[j][i]);
				  		}
				  		printf("\n");

				  	}

				  	getchar();
				  	getchar();

		            if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");
	    	break;
	    	
	    	case 6:
		            if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");
					
					while(getchar() != '\n');
					
					controlo = 0;
					while(controlo != 2){
			           	printf("Introduza o primeiro mes:");     	
			           	scanf("%d" , &mesi);

			           	if(mesi<1 || mesi>12){
			           		printf("mes invalido\n");
			           		controlo=0;
			           	}
			           	else
			           		controlo++;

			           	printf("Introduza o ultimo mes:");
			           	scanf("%d", &mess);

			           	if(mess<1 || mess>12 || mess<=mesi){
			           		printf("mes invalido\n");
			           		controlo=0;
			           	}
			           	else
			           		controlo++;

			        }

			        begin = clock();

			        totalvendas=0;totalfaturado=0.0;
					totalIntervalo(teste3 , mesi, mess, nfiliais , &totalvendas , &totalfaturado);

					end = clock();

		          	time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
 
		           	printf("tempo = %f\n", time_spent );

					printf("total faturado=%f\n", totalfaturado);
					printf("quantidade total=%d\n",  totalvendas);
					getchar();
					getchar();

		            if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");
	    	break;
	    		    	
	    	case 8:
		            if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");
	            
		          	while(getchar() != '\n');
		           	printf("Introduza o codigo do cliente:");
		           	cli = malloc(sizeof(char) * 6);
		           	scanf("%s" , cli);

		           	begin = clock();

		           	genN = initListaGen(totalClientes(teste));
					genP = initListaGen(totalClientes(teste));
					
					for(i=0;i<nfiliais;i++){
						clientesContemProduto(teste , teste4[1], cli, genN, genP);
					}

					qwe1 = retornaListaGen(genN);
					qwe2 = retornaListaGen(genP);

					end = clock();

		          	time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
 
		           	printf("tempo = %f\n", time_spent );

					j = retornaPosListaGen(genN);
					for (i=0; i<j; i++){
					  printf("Cliente: %s\n", qwe1[i]);
					}
					printf("total Normal: %d\n", j);
					  
					printf("\n\n");

					j = retornaPosListaGen(genP);
					for (i=0; i<j; i++){
					  printf("Cliente: %s\n", qwe2[i]);
					}
					printf("total Promocao: %d\n", j);

					getchar();
					getchar();
					
					removeListaGen(genN);
					removeListaGen(genP);

		            if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");
	    	break;
	    	
	    	case 14:
			        if (SYSTEM)  
			            	system ("clear");
						else 
							system ("cls"); 
					
					removeCatFaturacao(teste3, nfiliais);
					removeCatFilial(teste4[0]);
				    removeCatFilial(teste4[1]);
				 	removeCatFilial(teste4[2]);
					removeCatClientes(teste);
					removeCatProdutos(teste2);

			    	printf("\tAté á proxima!\n\t  Obrigado.\n\n");
					controloDeCiclo = 0;

			break;
			
			default:

				while(getchar() != '\n');
			
				if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");

	            printf ("\tATENÇÃO!\nOperação Inválida!\n");
				
				if (SYSTEM)  
		            	system ("clear");
					else 
						system ("cls");
		}

	}
}
