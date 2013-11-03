#ifndef SINTATICO_H_INCLUDED
#define SINTATICO_H_INCLUDED
#include "automato.h"

typedef struct _listaAutomatos{
    Automato* automato;
    struct _listaAutomatos *prox;
}ListaAutomatos;

void inicializarSintatico();

void inicializarListaAutomatos(ListaAutomatos **lista);

void adicionarListaAutomatos(Automato* A,ListaAutomatos **L);

void carregarAutomatos(ListaAutomatos **lista);

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

#endif // SINTATICO_H_INCLUDED
