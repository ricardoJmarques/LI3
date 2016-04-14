#include <stdlib.h>

#ifndef API_UTILS_H
#define API_UTILS_H

typedef enum {FALSE,TRUE} Boolean;

Boolean verificaAlpha(char caracter);

Boolean verificaNumero(char *num, int min, int max);

#endif
