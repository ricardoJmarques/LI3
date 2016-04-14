#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TAMVL 1000000 /*tamanho das linhas vendas*/
#define TAMVC 40 /*tamanho das colunas vendas*/

int parseLinha(char *linha, char *mapaProduto, char *mapaCliente);

int preencheArrayVendas(FILE *ficheiro, char *tabela, char *mapaProduto, char *mapaCliente);


