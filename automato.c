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
    listaAux ->transicao = (Transicao *) malloc (sizeof(Transicao));;
    listaAux ->transicao = T;
    listaAux->prox = NULL;


    if ( *L != NULL)
        listaLoop->prox = listaAux;
    else
    {
        *L = (ListaTransicao *) malloc (sizeof(ListaTransicao));
        *L = listaAux;
    }

}

void inicializarEstado(Estado ** E, int numeroEstado, int estadoFinal, int estadoInicial)
{
    *E = NULL;
    *E = (Estado *) malloc (sizeof(Estado));

    (*E)->estadoInicial = estadoInicial;
    (*E)->estadoFinal = estadoFinal;
    (*E)->estado = numeroEstado;
    (*E)->listaTransicao = NULL;
    (*E)->chamadaSubMaquina = NULL;
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
    listaAux ->estado = (Estado *) malloc (sizeof(Estado));
    listaAux ->estado = E;
    listaAux->prox = NULL;

    if ( *L != NULL)
        listaLoop->prox = listaAux;
    else
    {
        *L = (ListaEstados *) malloc (sizeof(ListaEstados));
        *L = listaAux;
    }

}

void inicializarAutomato(Automato **A)
{
    *A = NULL;

}

void printAutomato(Automato *A)
{
    Estado *estadoAtual;

    Transicao *transicaoAtual = (Transicao *) malloc (sizeof(Transicao));
    //transicaoAtual = NULL;



    if(A != NULL)
    {

        ListaEstados *listaEstados = (ListaEstados *) A->listaEstados;
        estadoAtual = listaEstados->estado;

        printf("\n\n Automato  %s ",(A->ID));

        //Percorre todos os estados do automato
        while(estadoAtual!=NULL)
        {


            printf("\n Estado  %d ",estadoAtual->estado);

            if(estadoAtual->estadoInicial==1)
                printf("  - Estado Inicial ");

            if(estadoAtual->estadoFinal==1)
                printf("  - Estado Final ");

            if(estadoAtual->listaTransicao !=NULL){


                ListaTransicao *listaTransicao = estadoAtual->listaTransicao;

                //Verifica as transicoes do estado
                while(listaTransicao!=NULL)
                {
                    transicaoAtual = listaTransicao->transicao;

                    Estado *proximoEstado = (Estado *)transicaoAtual->proximoEstado;

                    //int estadoFuturo = (transicaoAtual->proximoEstado)->estado;
                    printf("\n Transicao para %d com token %s",(proximoEstado->estado),(transicaoAtual->terminal));

                    listaTransicao = listaTransicao->prox;
                }

            }

            if(estadoAtual->chamadaSubMaquina!= NULL)
            {
                Automato *proximoAutomato = (Automato *)estadoAtual->chamadaSubMaquina->proxAutomato;
                Estado *estadoRetorno = (Estado *)estadoAtual->chamadaSubMaquina->estadoRetorno;
                printf("\n Chamada de submaquina %s, estado de retorno %d ",(proximoAutomato->ID),estadoRetorno->estado);
            }

            if(listaEstados->prox != NULL)
            {
                listaEstados = listaEstados->prox;
                estadoAtual = listaEstados->estado;
            }
            else
            {
                estadoAtual = NULL;
            }



            printf("\n");
        }
    }


}

Estado *estadoInicial(Automato *A)
{
    if(A!=NULL)
    {
        if(A->listaEstados!=NULL)
        {
            //Assume que o peimrio estado da lista de estados é o estado inicial
            ListaEstados *lAux = (ListaEstados *)A->listaEstados;



            return lAux->estado;

        }
        return NULL;
    }
    return NULL;
}

Estado* buscarEstadoPorNumero(ListaEstados *listaEstados,int numero)
{

    while(listaEstados!=NULL)
    {
        if(listaEstados->estado->estado==numero)
        {
            return listaEstados->estado;
        }
        listaEstados = listaEstados->prox;
    }

    return NULL;
}
