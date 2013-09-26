#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "estruturas.h"
#include <string.h>


/*
    Manipulação de listas
*/

void inicializaLista(noLista **L){
    *L = NULL;
}


void insereNo(int id, char *valor, noLista **L){
    noLista *paux, *pLoop;

    if ( *L != NULL) {
        pLoop = *L;
        while( pLoop->prox != NULL){
            pLoop = pLoop->prox;
        }
    }


    paux = (noLista *) malloc (sizeof(noLista));
    paux ->id = id;
    paux ->valor = valor;
    paux ->prox = NULL;


    if ( *L != NULL)
        pLoop->prox = paux;
    else
        *L = paux;

}


noLista* procuraLista(char *valor, noLista *L){
    noLista *paux;

    paux = L;

    while(paux != NULL){

        if(strcmp(paux->valor, valor) == 0) return paux;
        paux = paux->prox;
    }
    return paux;
}

int ultimoIdentificador(noLista **L) {

    noLista *aux, *prox;
    aux = *L;
    if (aux != NULL) {
        prox = aux->prox;
        while (prox != NULL) {

            aux = prox;
            prox = aux->prox;
        }

        return aux->id;

    } else {
        return -1;
    }

}

int adicionaSimboloLista(char *palavra, noLista **lista) {

    int identificadorAnterior = ultimoIdentificador(lista);
    int identificador;
    if (identificadorAnterior < 0) {
        identificador = 1;
    } else {
        identificador = identificadorAnterior + 1;
    }

    insereNo(identificador, palavra, lista);
    return identificador;

}

int buscaSimboloLista(char *palavra, noLista *lista) {

    noLista *resultado;
    resultado = procuraLista(palavra, lista);

    if (resultado == NULL) {
        return 0;
    } else {

        return resultado->id;
    }
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

/*
    Manipulacao de Tokens
*/

void inicializaToken(token **T)
{
    *T = NULL;
}

//apenas gera o token, nao insere na ista ligada
token* geraToken(int tipo, char *valor)
{
    token *taux;

    taux = (token *) malloc (sizeof(token));

    int tamanho = strlen(valor)+1;
    taux ->valor = (char*) malloc (tamanho * sizeof(char));

    strcpy (taux ->valor, valor);
    taux ->tipo = tipo;
    taux ->proxToken = NULL;

    return taux;
}

token* insereToken(int tipo, char *valor, token **T)
{
    token *taux, *pLoop;



    if ( *T != NULL) {
        pLoop = *T;
        while( pLoop->proxToken != NULL){
            pLoop = pLoop->proxToken;
        }
    }

    taux = (token *) malloc (sizeof(token));

    int tamanho = strlen(valor)+1;
    taux ->valor = (char*) malloc (tamanho * sizeof(char));
    strcpy (taux ->valor, valor);
    taux ->tipo = tipo;
    taux ->proxToken = NULL;

    if ( *T != NULL)
        pLoop->proxToken = taux;
    else
        *T = taux;


    return taux;
}


/*
    popula a tabela de palavras reservadas
*/

void populaTabelaPalavrasReservadas(noLista **palavraReservada) {

    FILE *entrada;
    int id = 1;

    entrada = fopen("palavrasreservadas.txt" , "r");

    char *palavraLida;

    while (fscanf(entrada, "%s", palavraLida) == 1)
    {

        char * palavraNova = malloc(strlen(palavraLida) + 1);
        strcpy(palavraNova, palavraLida);

        insereNo(id, palavraNova, palavraReservada);

        id++;
    }

    fclose(entrada);
}

