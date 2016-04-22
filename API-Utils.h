#include <stdlib.h>
#include <string.h>

#ifndef API_UTILS_H
#define API_UTILS_H

typedef enum {FALSE,TRUE} Boolean;

typedef struct ListaGen *ListaGenerica;

Boolean verificaAlpha(char caracter);

Boolean verificaNumero(char *num, int min, int max);

ListaGenerica initListaGen(int n);

ListaGenerica insereListaGen(ListaGenerica lg, char* string);

int retornaPosListaGen(ListaGenerica lg);

int retornaTamMaxListaGen(ListaGenerica lg);

char** retornaListaGen(ListaGenerica lg);

void removeListaGen(ListaGenerica lg);

#endif
