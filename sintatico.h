#ifndef SINTATICO_H_INCLUDED
#define SINTATICO_H_INCLUDED

typedef struct _listaAutomatos{
    Automato* automato;
    struct _listaAutomatos *prox;
}ListaAutomatos;

void inicializarSintatico();

void inicializarListaAutomatos(ListaAutomatos **lista);

void carregarAutomatos(ListaAutomatos **lista);

#endif // SINTATICO_H_INCLUDED
