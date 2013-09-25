#include "lexico.h"
#include <string.h>

/*
    ESTADO 0 : Estado inicial
    ESTADO 1 : Estado de erro
*/

noLista *NoPalavraReservada;
noLista *NoSimbolo;
noLista *NoString;
token *TokenLista;

void adicionarCharNaString(char caracter, char* stringOriginal) {
	int tamanho = strlen(stringOriginal);
	stringOriginal[tamanho] = caracter;
	stringOriginal[tamanho + 1] = '\0';
}

void inicializarLexico()
{
    inicializaLista(&NoPalavraReservada);
    inicializaLista(&NoSimbolo);
    inicializaLista(&NoString);
    inicializaToken(&TokenLista);
    populaTabelaPalavrasReservadas(&NoPalavraReservada);

    inicializarAutomato();

    //imprimeLista(NoPalavraReservada);

}

void imprimeLista(noLista *lista) {

    noLista *paux;

    paux = lista;

    while(paux!=NULL){
        printf("\nidentificador %d",paux->id);
        printf("\npalavra %s",paux->valor);
        printf("\n");
        paux = paux->prox;
    }
    printf("\n");

}

void imprimeTokens(token *Tlista) {

    token *taux;

    taux = Tlista;

    while(taux!=NULL){
        printf("\n tipo %d",taux->tipo);
        printf("\n valor %s",taux->valor);
        printf("\n");
        taux = taux->proxToken;
    }
    printf("\n");

}

void extrairTokens(FILE *programaFonte)
{
    char caracterLido;
    int proximoEstado = 0;
    int estadoAtual = 0;
    int tipoSaida = 0;
    char tokenFormado[200];

    tokenFormado[0] = '\0';

    while (fscanf(programaFonte, "%c", &caracterLido) != EOF){

        estadoAtual = proximoEstado;

        //obtem o proximo estado a partir do caracter atual
        proximoEstado = obterProximoEstado(estadoAtual, caracterLido, &tipoSaida);
        //printf("\n proximo estado: %d - tipo saida: %d \n ",proximoEstado,tipoSaida);

        //estado de erro
        if(proximoEstado == 1)
        {
            printf("Erro no lexico");
        }
        else
        {
            //caso o automato tenha retornado algum tipo de saída, considera que um token foi identificado
            if(tipoSaida > 0)
            {
                //printf("%s",tokenFormado);
                registrarTokenEncontrado(tokenFormado,tipoSaida);
                //printf("\n ultimo caracter lido %c \n",caracterLido);
                //reinicia o token
                tokenFormado[0] = '\0';
            }
            else
            {
                if(proximoEstado>1)
                    adicionarCharNaString(caracterLido, tokenFormado);
            }
        }


    }

    imprimeTokens(TokenLista);
}

void registrarTokenEncontrado(char* tokenEncontrado, int tipo)
{




    long tamanho = strlen(tokenEncontrado);
    int cont = 1;
    char palavraSemAspas[tamanho - 2];

    switch(tipo)
    {

        case INTEIRO:
            insereToken(INTEIRO,tokenEncontrado,&TokenLista);
            break;

        case FLOAT:
            insereToken(FLOAT,tokenEncontrado,&TokenLista);
            break;

        case STRING:

            while (cont < tamanho - 1) {
                palavraSemAspas[cont - 1] = tokenEncontrado[cont];
                cont ++;
            }

            char *target = malloc(strlen(tokenEncontrado));
            strcpy(target, palavraSemAspas);

            adicionaSimboloLista(target, NoString);


            insereToken(STRING,target,&TokenLista);

            break;

        //deals with string
        default:

            //    Verifica se palavra esta na lista de palavras reservadas!
            //imprimeLista(NoPalavraReservada);

            if (buscaSimboloLista(tokenEncontrado, NoPalavraReservada) > 0) {
                insereToken(PALAVRARESERVADA,tokenEncontrado,&TokenLista);
            }
            else
                if (buscaSimboloLista(tokenEncontrado, NoSimbolo) > 0) {
                    insereToken(tipo,tokenEncontrado,&TokenLista);
                }
                else
                {
                    adicionaSimboloLista(tokenEncontrado, &NoSimbolo);
                    insereToken(tipo,tokenEncontrado,&TokenLista);
                }

            break;
    }


}
