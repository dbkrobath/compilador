#include "sintatico.h"
#include "automato.h"

ListaAutomatos *listaAutomatos;

void inicializarSintatico()
{
    inicializarListaAutomatos(&listaAutomatos);
    carregarAutomatos(&listaAutomatos)
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


    Automato *automatoE = (Automato *) malloc (sizeof(Automato));

    automatoE->ID = "E";


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


    Estado* estadoE0 = (Estado *) malloc (sizeof(Estado));
    Estado* estadoE1 = (Estado *) malloc (sizeof(Estado));
    Estado* estadoE2 = (Estado *) malloc (sizeof(Estado));
    Estado* estadoE3 = (Estado *) malloc (sizeof(Estado));

    estadoE0->estadoInicial = 1;
    estadoE1->estadoFinal = 1;
    estadoE3->estadoFinal = 1

    ListaEstados* listaEstadosE = (ListaEstados *) malloc (sizeof(ListaEstados));

    inicializarEstado(&listaEstadosE);

    adicionarListaEstados(estadoE0,&listaEstadosE);
    adicionarListaEstados(estadoE1,&listaEstadosE);
    adicionarListaEstados(estadoE2,&listaEstadosE);
    adicionarListaEstados(estadoE3,&listaEstadosE);

    automatoE->listaEstados = listaEstadosE;

    Transicao* transicaoE0 = (Transicao *) malloc (sizeof(Transicao));
    transicao1->proximoEstado = estadoE2;
    transicao1->terminal = "+";

    ListaTransicao* listaTransicaoE = (ListaTransicao *) malloc (sizeof(ListaTransicao));



    adicionarListaTransicao(transicaoE0,&listaTransicaoE);

    estadoE1->listaTransicao = listaTransicaoE;


    ChamadaSubMaquina* chamada1 = (ChamadaSubMaquina *) malloc (sizeof(ChamadaSubMaquina));
    chamada1->proxAutomato = automatoT;
    chamada1->estadoRetorno = estadoE1;

    estadoE0->chamadaSubMaquina = chamada1;


    Estado* estadoT0 = (Estado *) malloc (sizeof(Estado));
    Estado* estadoT1 = (Estado *) malloc (sizeof(Estado));
    Estado* estadoT2 = (Estado *) malloc (sizeof(Estado));
    Estado* estadoT3 = (Estado *) malloc (sizeof(Estado));
    Estado* estadoT4 = (Estado *) malloc (sizeof(Estado));
    Estado* estadoT5 = (Estado *) malloc (sizeof(Estado));


    estadoT0->estadoInicial = 1;
    estadoT1->estadoFinal = 1;
    estadoT5->estadoFinal = 1;

    Transicao* transicaoT00 = (Transicao *) malloc (sizeof(Transicao));
    transicao1->proximoEstado = estadoT1;
    transicao1->terminal = "int";

    Transicao* transicaoT01 = (Transicao *) malloc (sizeof(Transicao));
    transicao1->proximoEstado = estadoT2;
    transicao1->terminal = "(";

    ListaTransicao* listaTransicaoT0 = (ListaTransicao *) malloc (sizeof(ListaTransicao));
    estadoT0->listaTransicao = listaTransicaoT0;

    adicionarListaTransicao(transicaoT00,&listaTransicaoT0);
    adicionarListaTransicao(transicaoT01,&listaTransicaoT0);



    Transicao* transicaoT10 = (Transicao *) malloc (sizeof(Transicao));
    transicao1->proximoEstado = estadoT3;
    transicao1->terminal = "*";

    adicionarListaTransicao(transicaoT10,&listaTransicaoT1);

    ListaTransicao* listaTransicaoT1 = (ListaTransicao *) malloc (sizeof(ListaTransicao));
    estadoT1->listaTransicao = listaTransicaoT1;

    Transicao* transicaoT40 = (Transicao *) malloc (sizeof(Transicao));
    transicao1->proximoEstado = estadoT5;
    transicao1->terminal = ")";

    ListaTransicao* listaTransicaoT4 = (ListaTransicao *) malloc (sizeof(ListaTransicao));
    estadoT4->listaTransicao = listaTransicaoT4;

    adicionarListaTransicao(transicaoT40,&listaTransicaoT4);

    ListaTransicao* listaTransicaoT1 = (ListaTransicao *) malloc (sizeof(ListaTransicao));
    estadoT1->listaTransicao = listaTransicaoT1;


    ChamadaSubMaquina* chamadaT2 = (ChamadaSubMaquina *) malloc (sizeof(ChamadaSubMaquina));
    chamadaT2->proxAutomato = automatoE;
    chamadaT2->estadoRetorno = estadoT4;

    estadoT2->chamadaSubMaquina = chamadaT2;



    ChamadaSubMaquina* chamadaT3 = (ChamadaSubMaquina *) malloc (sizeof(ChamadaSubMaquina));
    chamadaT3->proxAutomato = automatoT;
    chamadaT3->estadoRetorno = estadoT5;

    estadoT3->chamadaSubMaquina = chamadaT3;

}

void semantico_tbd()
{

}
