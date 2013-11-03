#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "sintatico.h"



ListaAutomatos *listaAutomatos;
Automato *automatoEmUso;
Estado *estadoEmUso;
PilhaEstados *pilhaEstados;


void inicializarSintatico()
{
    inicializarListaAutomatos(&listaAutomatos);
    inicializarAutomato(&automatoEmUso);
    inicializarEstado(&estadoEmUso,0,0,1);
    inicializaPilha(&pilhaEstados);

    carregarAutomatos(&listaAutomatos);

    //Extrai o primeiro automato da lista
    automatoEmUso = listaAutomatos->automato;

    //Extrai o primeiro estado do primeiro automato
    estadoEmUso = estadoInicial(automatoEmUso);


    ListaAutomatos *lAux;
    inicializarListaAutomatos(&lAux);

    lAux = listaAutomatos;


    while(lAux!=NULL)
    {
        printAutomato(lAux->automato);
        lAux = lAux ->prox;
    }




}

void enviaTokenSintatico(token *token)
{
    printf("\n Estado em uso %d, Maquina em uso %c",estadoEmUso->estado,*(automatoEmUso->ID));

    if((automatoEmUso!=NULL)&&(estadoEmUso!=NULL))
    {
        //Verifica se existe uma chamada de submaquina na etapa corrente
        if(estadoEmUso->chamadaSubMaquina!=NULL)
        {

            empilhaEstado(automatoEmUso,estadoEmUso,&pilhaEstados);
            automatoEmUso = estadoEmUso->chamadaSubMaquina->proxAutomato;
            estadoEmUso = estadoInicial(automatoEmUso);

            printf("\n Chamada de submaquina para  %c",*(automatoEmUso->ID));

            enviaTokenSintatico(token);
        }
        else
        {
            ListaTransicao *listaTransicaoAux = estadoEmUso->listaTransicao;

            while(listaTransicaoAux!=NULL)
            {
                Transicao *transicaoAux = listaTransicaoAux->transicao;

                if(strcmp(transicaoAux->terminal, token->valor) == 0)
                {
                    estadoEmUso = transicaoAux->proximoEstado;

                    printf("\n Transicao para %d com token %s",(estadoEmUso->estado),(transicaoAux->terminal));

                    listaTransicaoAux = NULL;
                }
                else
                {
                    printf("\n Procura o proximo token");
                    listaTransicaoAux = listaTransicaoAux->prox;
                }


            }
        }

    }

}

void inicializarListaAutomatos(ListaAutomatos **L)
{
    *L = NULL;
}

void carregarAutomatos(ListaAutomatos **L)
{

    /*
        E = T "+" E | T.

        initial: 0
        final: 1, 3
        (0, T) -> 1
        (1, "+") -> 2
        (2, E) -> 3

    */


    Automato *automatoE = NULL;

    automatoE = (Automato *) malloc (sizeof(Automato));

    automatoE->ID = "E";
    automatoE->listaEstados = NULL;


    /*
        T = "int" | "int" "*" T | "(" E ")".

        initial: 0
        final: 1, 5
        (0, "int") -> 1
        (0, "(") -> 2
        (1, "*") -> 3
        (2, E) -> 4
        (3, T) -> 5
        (4, ")") -> 5

    */


    Automato *automatoT = (Automato *) malloc (sizeof(Automato));

    automatoT->ID = "T";
    automatoT->listaEstados = NULL;

    Estado* estadoE0;
    Estado* estadoE1;
    Estado* estadoE2;
    Estado* estadoE3;

    inicializarEstado(&estadoE0,0,0,1);

    inicializarEstado(&estadoE1,1,1,0);

    inicializarEstado(&estadoE2,2,0,0);

    inicializarEstado(&estadoE3,3,1,0);

    Transicao* transicaoE0 = (Transicao *) malloc (sizeof(Transicao));
    transicaoE0->proximoEstado = estadoE2;

    strcpy(transicaoE0->terminal,"+");

    ListaTransicao* listaTransicaoE;
    inicializarListaTransicao(&listaTransicaoE);

    adicionarListaTransicao(transicaoE0,&listaTransicaoE);

    estadoE1->listaTransicao = (ListaTransicao *) malloc (sizeof(ListaTransicao));
    estadoE1->listaTransicao = listaTransicaoE;


    ChamadaSubMaquina* chamada1 = (ChamadaSubMaquina *) malloc (sizeof(ChamadaSubMaquina));
    chamada1->proxAutomato = automatoT;
    chamada1->estadoRetorno = estadoE1;

    estadoE0->chamadaSubMaquina = (ChamadaSubMaquina *) malloc (sizeof(ChamadaSubMaquina));
    estadoE0->chamadaSubMaquina = chamada1;

    ChamadaSubMaquina* chamada2 = (ChamadaSubMaquina *) malloc (sizeof(ChamadaSubMaquina));
    chamada2->proxAutomato = automatoE;
    chamada2->estadoRetorno = estadoE3;

    estadoE2->chamadaSubMaquina = (ChamadaSubMaquina *) malloc (sizeof(ChamadaSubMaquina));
    estadoE2->chamadaSubMaquina = chamada2;


    ListaEstados *listaEstadosE;

    inicializarListaEstados(&listaEstadosE);

    adicionarListaEstados(estadoE0,&listaEstadosE);
    adicionarListaEstados(estadoE1,&listaEstadosE);
    adicionarListaEstados(estadoE2,&listaEstadosE);
    adicionarListaEstados(estadoE3,&listaEstadosE);

    automatoE->listaEstados = (ListaEstados *) malloc (sizeof(ListaEstados));
    automatoE->listaEstados = listaEstadosE;


    Estado* estadoT0;
    Estado* estadoT1;
    Estado* estadoT2;
    Estado* estadoT3;
    Estado* estadoT4;
    Estado* estadoT5;

    inicializarEstado(&estadoT0,0,0,1);
    inicializarEstado(&estadoT1,1,1,0);
    inicializarEstado(&estadoT2,2,0,0);
    inicializarEstado(&estadoT3,3,0,0);
    inicializarEstado(&estadoT4,4,0,0);
    inicializarEstado(&estadoT5,5,1,0);


    Transicao* transicaoT00 = (Transicao *) malloc (sizeof(Transicao));
    transicaoT00->proximoEstado = estadoT1;

    strcpy(transicaoT00->terminal,"int");


    Transicao* transicaoT01 = (Transicao *) malloc (sizeof(Transicao));
    transicaoT01->proximoEstado = estadoT2;

    strcpy(transicaoT01->terminal,"(");

    ListaTransicao* listaTransicaoT0;

    inicializarListaTransicao(&listaTransicaoT0);

    adicionarListaTransicao(transicaoT00,&listaTransicaoT0);
    adicionarListaTransicao(transicaoT01,&listaTransicaoT0);

    estadoT0->listaTransicao = (ListaTransicao *) malloc (sizeof(ListaTransicao));
    estadoT0->listaTransicao = listaTransicaoT0;

    Transicao* transicaoT10 = (Transicao *) malloc (sizeof(Transicao));
    transicaoT10->proximoEstado = estadoT3;

    strcpy(transicaoT10->terminal,"*");

    ListaTransicao* listaTransicaoT1;

    inicializarListaTransicao(&listaTransicaoT1);

    adicionarListaTransicao(transicaoT10,&listaTransicaoT1);

    estadoT1->listaTransicao = (ListaTransicao *) malloc (sizeof(ListaTransicao));
    estadoT1->listaTransicao = listaTransicaoT1;

    Transicao* transicaoT40 = (Transicao *) malloc (sizeof(Transicao));
    transicaoT40->proximoEstado = estadoT5;

    strcpy(transicaoT40->terminal,")");

    ListaTransicao* listaTransicaoT4;

    inicializarListaTransicao(&listaTransicaoT4);

    adicionarListaTransicao(transicaoT40,&listaTransicaoT4);

    estadoT4->listaTransicao = (ListaTransicao *) malloc (sizeof(ListaTransicao));
    estadoT4->listaTransicao = listaTransicaoT4;


    ChamadaSubMaquina* chamadaT2 = (ChamadaSubMaquina *) malloc (sizeof(ChamadaSubMaquina));
    chamadaT2->proxAutomato = automatoE;
    chamadaT2->estadoRetorno = estadoT4;

    estadoT2->chamadaSubMaquina = (ChamadaSubMaquina *) malloc (sizeof(ChamadaSubMaquina));
    estadoT2->chamadaSubMaquina = chamadaT2;

    ChamadaSubMaquina* chamadaT3 = (ChamadaSubMaquina *) malloc (sizeof(ChamadaSubMaquina));
    chamadaT3->proxAutomato = automatoT;
    chamadaT3->estadoRetorno = estadoT5;

    estadoT3->chamadaSubMaquina = (ChamadaSubMaquina *) malloc (sizeof(ChamadaSubMaquina));
    estadoT3->chamadaSubMaquina = chamadaT3;



    ListaEstados *listaEstadosT;

    inicializarListaEstados(&listaEstadosT);

    adicionarListaEstados(estadoT0,&listaEstadosT);
    adicionarListaEstados(estadoT1,&listaEstadosT);
    adicionarListaEstados(estadoT2,&listaEstadosT);
    adicionarListaEstados(estadoT3,&listaEstadosT);
    adicionarListaEstados(estadoT4,&listaEstadosT);
    adicionarListaEstados(estadoT5,&listaEstadosT);

    automatoT->listaEstados = (ListaEstados *) malloc (sizeof(ListaEstados));
    automatoT->listaEstados = listaEstadosT;


    adicionarListaAutomatos(automatoE,&listaAutomatos);
    adicionarListaAutomatos(automatoT,&listaAutomatos);

}

void adicionarListaAutomatos(Automato* A,ListaAutomatos **L)
{
    ListaAutomatos *listaAux, *listaLoop;

    if ( *L != NULL) {
        listaLoop = *L;
        while( listaLoop->prox != NULL){
            listaLoop = listaLoop->prox;
        }
    }

    listaAux = (ListaAutomatos *) malloc (sizeof(ListaAutomatos));
    listaAux ->automato = (Automato *) malloc (sizeof(Automato));
    listaAux ->automato = A;
    listaAux->prox = NULL;

    if ( *L != NULL)
        listaLoop->prox = listaAux;
    else
    {
        *L = (ListaAutomatos *) malloc (sizeof(ListaAutomatos));
        *L = listaAux;
    }
}



/*
    Manipulacao da Pilha
*/

void inicializaPilha(PilhaEstados **P){
    *P = NULL;
}

void empilhaEstado(Automato *automato, Estado *estado, PilhaEstados **P)
{
    PilhaEstados *paux, *pCopia;

    pCopia = *P;

    paux = (PilhaEstados *) malloc (sizeof(PilhaEstados));

    paux ->estadoRetorno = (Estado *) malloc (sizeof(Estado));
    paux ->estadoRetorno = estado;

    paux ->automatoRetorno = (Automato *) malloc (sizeof(Automato));
    paux ->automatoRetorno = automato;

    paux ->estadoAnterior = NULL;


    if ( *P != NULL)
        paux ->estadoAnterior = pCopia;


    *P = paux;


}

PilhaEstados* desempilhaEstado(PilhaEstados **P)
{
    PilhaEstados *paux;
    inicializaPilha(&paux);
    paux = (PilhaEstados *) malloc (sizeof(PilhaEstados));

    paux = *P;

    if(*P!=NULL)
    {
        *P = paux->estadoAnterior;
        return paux;
    }

    return NULL;

}



void semantico_tbd()
{

}
