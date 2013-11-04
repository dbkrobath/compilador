#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "lexico.h"
#include "sintatico.h"

int main()
{

    FILE *programaFonte;

    programaFonte = fopen("ape-entrada-completo.txt","r");
    if(!programaFonte)
    {
        printf( "Erro na abertura do arquivo fonte");
        exit(0);
    }

    inicializarLexico();
    inicializarSintatico();

    token* tokenLido;

    //realiza a leitura de tokens até o lexico retornar o tipo NO_TOKENS

    tokenLido = extraiProximoToken(programaFonte);

    while (tokenLido->tipo != NO_TOKENS)
    {
        printf("\n \n Valor: %s   - Tipo: %d",tokenLido->valor,tokenLido->tipo);
        enviaTokenSintatico(tokenLido);

        //printf("\n\n  Tipo: %d",tokenLido->tipo);

        tokenLido = extraiProximoToken(programaFonte);
    }

    //apenas para imprimir o token to tipo NO_TOKENS
    enviaTokenSintatico(tokenLido);

    if(aceitouLinguagem==1)
        printf("\n\n\nAceitou a linguagem\n\n");
    else
        printf("\n\n\nNao aceitou a linguagem\n\n");

   // printf("\n\n  Tipo: %d",tokenLido->tipo);


    fclose(programaFonte);

    return 0;
}
