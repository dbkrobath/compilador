#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"

int main()
{
    int** tabelaSimbolos;

    FILE *programaFonte;

    programaFonte = fopen("input.txt","r");
    if(!programaFonte)
    {
        printf( "Erro na abertura do arquivo");
        exit(0);
    }

    inicializarTabelaSimbolos(tabelaSimbolos)
    extrairTokens(programaFonte);
    return 0;
}
