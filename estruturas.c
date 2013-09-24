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

/*
    Manipulacao de Tokens
*/

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


/*
    manipulação palavras reservadas
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

int buscaSimboloPalavraReservada(char *palavra, noLista **lista) {

    noLista *resultado;

    resultado = procuraLista(palavra, lista);

    if (resultado == NULL) {
        return 0;
    } else {
        return resultado->id;

    }

}

/*
    manipulação da tabela de strings
*/

int adicionaString(char *palavra, noLista **strings) {

    int identificadorAnterior = ultimoIdentificador(strings);
    int identificador;
    if (identificadorAnterior < 0) {
        identificador = 1;
    } else {
        identificador = identificadorAnterior + 1;
    }


    insereNo(identificador, palavra, strings);
    return identificador;

}

int buscaTabelaStrings(char *palavra, noLista **strings) {

    noLista *resultado;
    resultado = procuraLista(palavra, strings);

    if (resultado == NULL) {
        return 0;
    } else {
        //printf("achou alguma coisas %d", resultado->identificador);
        return resultado->id;
    }

}

int buscaTabelaSimbolos(char *palavra, noLista **simbolos) {

    noLista *resultado;
    resultado = procuraLista(palavra, simbolos);

    if (resultado == NULL) {
        return 0;
    } else {

        //printf("achou alguma coisas %d", resultado->identificador);
        return resultado->id;
    }
}
