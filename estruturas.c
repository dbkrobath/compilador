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


void insereNo(int id, char *valor, noLista **L, int bloco){
    noLista *paux, *pLoop;

    if ( *L != NULL) {
        pLoop = *L;
        while( pLoop->prox != NULL){
            pLoop = pLoop->prox;
        }
    }


    paux = (noLista *) malloc (sizeof(noLista));
    paux ->id = id;
    strcpy(paux->valor,valor);
    paux->bloco = bloco;
    paux ->prox = NULL;


    if ( *L != NULL)
        pLoop->prox = paux;
    else
        *L = paux;

}


noLista* procuraLista(char *valor, noLista *L){
    noLista *paux;

    paux = L;

    //printf("\n\n comecando a busca ");

    while(paux != NULL){

        //printf("\n comparando valor da lista %s com valor %s ",paux->valor,valor);

        if(strcmp(paux->valor, valor) == 0)
        {

            //printf("\n valores identicos... retorna ");
            return paux;
        }

        paux = paux->prox;
    }

    //printf("\n\n acabou a busca e nao achou o valor %s ",valor);
    return paux;
}

noLista* procuraListaBloco(char *valor, noLista *L, int bloco){
    noLista *paux;

    paux = L;


    while(paux != NULL){


        if(paux->bloco == bloco)
        {
            if(strcmp(paux->valor, valor) == 0)
            {
                return paux;
            }
        }

        paux = paux->prox;
    }

    return paux;
}


int ultimoIdentificador(noLista *L) {

    int id;

    if (L != NULL) {

        while (L  != NULL) {

            id = L->id;
            L = L->prox;
        }

        return id;

    } else {
        return -1;
    }

}

int ultimoIdentificadorBloco(noLista *L) {

    int id;

    if (L != NULL) {

        while (L  != NULL) {

            id = L->id;
            L = L->prox;
        }

        return id;

    } else {
        return -1;
    }

}


int adicionaSimboloLista(char *palavra, noLista **lista) {

    int identificadorAnterior = ultimoIdentificador(*lista);
    int identificador;
    if (identificadorAnterior < 0) {
        identificador = 1;
    } else {
        identificador = identificadorAnterior + 1;
    }

    insereNo(identificador, palavra, lista,0);
    return identificador;

}

int adicionaSimboloListaBloco(char *palavra, noLista **lista, int bloco) {

    int identificadorAnterior = ultimoIdentificador(*lista);
    int identificador;
    if (identificadorAnterior < 0) {
        identificador = 1;
    } else {
        identificador = identificadorAnterior + 1;
    }

    insereNo(identificador, palavra, lista,bloco);
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

int buscaSimboloListaBloco(char *palavra, noLista *lista, int bloco) {

    noLista *resultado;
    resultado = procuraListaBloco(palavra, lista,bloco);

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
        printf("\nbloco %d",paux->bloco);
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
    int id = 1, ret=1;

    entrada = fopen("palavrasreservadas.txt" , "r");

    while (ret == 1)
    {
        char palavraLida[255]="/0";
        ret = fscanf(entrada, "%s", palavraLida);
        char * palavraNova = malloc(strlen(palavraLida) + 1);
        strcpy(palavraNova, palavraLida);

        insereNo(id, palavraNova, palavraReservada,0);

        id++;
    }

    fclose(entrada);
}


