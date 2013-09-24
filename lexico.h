#ifndef LEXICO_H_INCLUDED
#define LEXICO_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include "automato.h"
#include "estruturas.h"
#include "constantes.h"



void extrairTokens(FILE *programaFonte);

void inicializarLexico();

#endif // LEXICO_H_INCLUDED
