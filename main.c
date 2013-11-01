#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "lexico.h"
#include "sintatico.h"

int main()
{

    FILE *programaFonte;

    programaFonte = fopen("ape-entrada.txt","r");
    if(!programaFonte)
    {
        printf( "Erro na abertura do arquivo fonte");
        exit(0);
    }

    inicializarLexico();

    token* tokenLido;

    //realiza a leitura de tokens até o lexico retornar o tipo NO_TOKENS

    tokenLido = extraiProximoToken(programaFonte);

    while (tokenLido->tipo != NO_TOKENS)
    {

        printf("\n\n  Tipo: %d",tokenLido->tipo);
        printf("\n Valor: %s",tokenLido->valor);

        tokenLido = extraiProximoToken(programaFonte);
    }

    //apenas para imprimir o token to tipo NO_TOKENS

    printf("\n\n  Tipo: %d",tokenLido->tipo);
    printf("\n Valor: %s",tokenLido->valor);

    fclose(programaFonte);

    return 0;
}
