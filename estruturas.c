#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "estruturas.h"
#include <string.h>


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


noLista* procuraLista(char *valor, noLista **L){
    noLista *paux;

    paux = *L;

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
