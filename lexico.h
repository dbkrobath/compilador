#ifndef LEXICO_H_INCLUDED
#define LEXICO_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include "automato.h"



void extrairTokens(FILE *programaFonte);

void inicializarTabelaSimbolos(FILE *ini);

#endif // LEXICO_H_INCLUDED
