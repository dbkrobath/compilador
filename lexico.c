#include "lexico.h"
#include <string.h>

/*
    ESTADO 0 : Estado inicial
    ESTADO 1 : Estado de erro
*/

noLista *NoPalavraReservada;
noLista *NoSimbolo;
noLista *NoString;

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
    populaTabelaPalavrasReservadas(&NoPalavraReservada);

    imprimeLista(NoPalavraReservada);

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
        proximoEstado = MOCKUPobterProximoEstado(estadoAtual, caracterLido, &tipoSaida);


        //estado de erro
        if(proximoEstado == 1)
        {
            printf("Erro no lexico");
        }
        else
        {
            //caso o automato tenha retornado algum tipo de sa�da, considera que um token foi identificado
            if(tipoSaida > 0)
            {
                printf("%s",tokenFormado);
                registrarTokenEncontrado(tokenFormado,tipoSaida);

                //reinicia o token
                tokenFormado[0] = '\0';
            }
            else
            {
                adicionarCharNaString(caracterLido, tokenFormado);
            }
        }


    }
}

void registrarTokenEncontrado(char* tokenEncontrado, int tipo)
{
    token *token;

    switch(tipo)
    {
        case INTEIRO:
            token = criaToken(INTEIRO, tokenEncontrado);
            break;

        case FLOAT:
            token = criaToken(FLOAT, tokenEncontrado);
            break;

        case STRING:

            //retira aspas da string e depois adiciona na tabela de strings

            long tamanho = strlen(palavra);
            int cont = 1;
            char palavraSemAspas[tamanho - 2];

            while (cont < tamanho - 1) {
                palavraSemAspas[cont - 1] = palavra[cont];
                cont ++;
            }

            char *target = malloc(strlen(palavra));
            strcpy(target, palavraSemAspas);

            adicionaString(target, strings);

            token = criaToken(STRING, target);

            break;
        //deals with string
        default:

            int encontrou = 0;
            //    Verifica se palavra esta na lista de palavras reservadas!
            int resultadoBusca = buscaSimboloPalavraReservada(palavra, palavrasReservadas);
            if (resultadoBusca > 0) {
                encontrou = 1;
                token = criaToken(PALAVRARESERVADA, palavra);
            }


            //    Se não é Palavra reservada verifica ser é simbolo
            if (encontrou == 0) {
                resultadoBusca = buscaTabelaSimbolos(palavra, simbolos);
                if (resultadoBusca > 0) {
                    encontrou = 1;
                    token = criaToken(tipo, palavra);
                }

            }

    //        Não foi encontrado nem na tabela de palavras reservadas  ou de simbolos
            if (encontrou == 0) {

                adicionaSimbolo(palavra, simbolos);
    //            Cria token
                token = criaToken(tipo, palavra);

            }

            break;
    }
}
