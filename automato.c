#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "automato.h"

void inicializarListaTransicao(ListaTransicao **L)
{
    *L = NULL;
}

void adicionarListaTransicao(Transicao* T,ListaTransicao **L)
{
    ListaTransicao *listaAux, *listaLoop;

    if ( *L != NULL) {
        listaLoop = *L;
        while( listaLoop->prox != NULL){
            listaLoop = listaLoop->prox;
        }
    }

    listaAux = (ListaTransicao *) malloc (sizeof(ListaTransicao));
    listaAux ->transicao = T;


    if ( *L != NULL)
        listaLoop->prox = listaAux;
    else
        *L = listaAux;
}

void inicializarListaEstados(ListaEstados **L)
{
    *L = NULL;
}

void adicionarListaEstados(Estado* E,ListaEstados **L)
{
    ListaEstados *listaAux, *listaLoop;


    if ( *L != NULL) {
        listaLoop = *L;
        while( listaLoop->prox != NULL){
            listaLoop = listaLoop->prox;
        }
    }

    listaAux = (ListaEstados *) malloc (sizeof(ListaEstados));
    listaAux ->estado = E;


    if ( *L != NULL)
        listaLoop->prox = listaAux;
    else
        *L = listaAux;
}

void inicializarAutomato(Automato **A)
{
    *A = NULL;
}

void printAutomato(Automato *A)
{
    Automato *Aux;

    Estado *estadoAtual;
    Transicao *transicaoAtual;


    if(A != NULL)
    {
        Aux = A;

        estadoAtual = Aux->estadoAtual;

        //Percorre todos os estados do automato
        while(estadoAtual!=NULL)
        {

            printf("\n Estado  $d ",estadoAtual);

            if(estadoAtual->listaTransicao !=NULL){

                transicaoAtual = estadoAtual->listaTransicao->transicao;

                //Verifica as transicoes do estado
                while(transicaoAtual!=NULL)
                {
                    printf("\n Transicao %d com token %c",transicaoAtual->proximoEstado,transicaoAtual->terminal);

                    //transicaoAtual = estadoAtual->listaTransicao->prox;
                }

                if(estadoAtual->chamadaSubMaquina!= NULL)
                {
                    //printf("\n Chamada de submaquina %c ",estadoAtual->chamadaSubMaquina->proxAutomato->ID);

                }

            }
            else
            {
                estadoAtual = NULL;
            }

            //estadoAtual = Aux->listaEstados->prox;
            printf("\n");
        }
    }


}
