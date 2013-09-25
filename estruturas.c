#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "estruturas.h"
#include <string.h>


/*
    Manipula��o de listas
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

/*
    Manipulacao de Tokens
*/

void inicializaToken(token **T)
{
    *T = NULL;
}

void insereToken(int tipo, char *valor, token **T)
{
    token *taux, *pLoop;

    if ( *T != NULL) {
        pLoop = *T;
        while( pLoop->proxToken != NULL){
            pLoop = pLoop->proxToken;
        }
    }

    taux = (token *) malloc (sizeof(token));

    int tamanho = strlen(valor);
    taux ->valor = (char*) malloc (tamanho * sizeof(char));
    strcpy (taux ->valor, valor);
    taux ->tipo = tipo;
    taux ->proxToken = NULL;

    if ( *T != NULL)
        pLoop->proxToken = taux;
    else
        *T = taux;
}

/*
token* criaToken(int tipo, char *valor) {

    token *taux;
    if (valor == NULL)
		valor = "";


    taux = (token *) malloc (sizeof(token));
	int tamanho = strlen(valor);
    taux ->valor = (char*) malloc (tamanho * sizeof(char));
	tamanho = strlen(valor);
    strcpy (taux ->valor, valor);
    taux ->tipo = tipo;

    return taux;
}
*/

/*
    manipula��o palavras reservadas
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


/*
    manipula��o de tabela de simbolos
*/

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
