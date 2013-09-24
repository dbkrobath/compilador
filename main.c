#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "lexico.h"

int main()
{

    FILE *programaFonte;

    programaFonte = fopen("input.txt","r");
    if(!programaFonte)
    {
        printf( "Erro na abertura do arquivo");
        exit(0);
    }

    inicializarLexico();
    extrairTokens(programaFonte);
    return 0;
}
