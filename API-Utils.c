#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *criaArray(int linhas, int colunas){
  char *array;
  array = (char *)malloc(sizeof(char) * linhas * colunas);
  if (array!=NULL)
    printf("Espaço %d x %d alocado em memoria.\n", linhas, colunas);
  return array;
}

int preencheArray(FILE *ficheiro, char *tabela, int tamLinha, int tamColuna){
  int i = 0;
  char buffer[tamColuna];
  while ((i<tamLinha) && (fgets(buffer, tamColuna-1, ficheiro)!=NULL)){
    strcpy(&tabela[i*tamColuna], strtok(buffer, "\r\n"));
    i++;
  }
  printf("Ficheiro carregado para a memoria no formato %d x %d.\n", tamLinha, tamColuna);
  printf("%d linhas encontradas.\n", i);
  return i;
}


