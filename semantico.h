#ifndef SEMANTICO_H_INCLUDED
#define SEMANTICO_H_INCLUDED
#include "constantes.h"
#include "automato.h"
#include "estruturas.h"

typedef struct _pilhaExpressao{
    token *token;
    struct _pilhaExpressao *elementoAnterior;
}PilhaExpressao;

void inicializaPilhaExpressao(PilhaExpressao **);
void empilhaElemento(token *tokenEmpilhar, PilhaExpressao **P);
PilhaExpressao* desempilhaElemento(PilhaExpressao **P);
token* consultaTopo(PilhaExpressao *P);

void processa_semantico(token *token, Automato *automatoEmUso);

#endif // SEMANTICO_H_INCLUDED
