#ifndef SINTATICO_H_INCLUDED
#define SINTATICO_H_INCLUDED
#define MaxStr 2000
#include "automato.h"
#include "constantes.h"
#include "xml_parse_lib/xml_parse_lib.h"

typedef struct _listaAutomatos{
    Automato* automato;
    struct _listaAutomatos *prox;
}ListaAutomatos;

int aceitouLinguagem;

void inicializarSintatico();

void inicializarListaAutomatos(ListaAutomatos **lista);

void adicionarListaAutomatos(Automato* A,ListaAutomatos **L);

void carregarAutomatos(ListaAutomatos **lista);

void carregarAutomatosJFLAP(ListaAutomatos **lista);


/*
    PILHA
*/

typedef struct _pilhaEstados{
    Estado *estadoRetorno;
    Automato *automatoRetorno;
    struct _pilhaEstados *estadoAnterior;
}PilhaEstados;

void inicializaPilha(PilhaEstados **);
void empilhaEstado(Automato *automato, Estado *estado, PilhaEstados **P);
PilhaEstados* desempilhaEstado(PilhaEstados **P);


void enviaTokenSintatico(token *token);

Automato* buscarAutomatoPorID(ListaAutomatos *listaAutomatos,char ID[40]);

#endif // SINTATICO_H_INCLUDED
