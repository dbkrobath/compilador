#ifndef LEXICO_H_INCLUDED
#define LEXICO_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include "automatoLex.h"
#include "estruturas.h"
#include "constantes.h"



void extrairTokens(FILE *programaFonte);

token* retornarTokenEncontrado(char* tokenEncontrado, int tipo);

void inicializarLexico();

int verificaEspacador(char caracter);

#endif // LEXICO_H_INCLUDED
