#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "semantico.h"

PilhaExpressao *pilhaOperadores;
PilhaExpressao *pilhaOperandos;
int contatemp;


int estadoExpressao;

void inicializaSemantico()
{
    inicializaPilhaExpressao(&pilhaOperandos);
    inicializaPilhaExpressao(&pilhaOperadores);
    estadoExpressao = ESTADO_EXP_A;
    contatemp = 0;

}



/*
    Manipulacao da Pilha Expressao
*/

void inicializaPilhaExpressao(PilhaExpressao **P){
    *P = NULL;
}

void empilhaElemento(token *tokenElemento, PilhaExpressao **P)
{
    PilhaExpressao *paux, *pCopia;

    pCopia = *P;

    paux = (PilhaExpressao *) malloc (sizeof(PilhaExpressao));

    paux ->token = (token *) malloc (sizeof(token));
    paux ->token = tokenElemento;

    paux ->elementoAnterior = NULL;


    if ( *P != NULL)
        paux ->elementoAnterior = pCopia;

    *P = paux;

    printf("\n Empilhou %s ",((*P)->token)->valor);
}

PilhaExpressao* desempilhaElemento(PilhaExpressao **P)
{
    PilhaExpressao *paux;
    inicializaPilhaExpressao(&paux);
    paux = (PilhaExpressao *) malloc (sizeof(PilhaExpressao));

    paux = *P;

    if(*P!=NULL)
    {
        *P = paux->elementoAnterior;
        return paux;
    }

    return NULL;

}

token* consultaTopo(PilhaExpressao *P)
{
    if(P!=NULL)
    {
        token *tokenAux = (token *) malloc (sizeof(token));

        tokenAux = P->token;

        return tokenAux;
    }

    return NULL;
}

int processamentoExpressoes(int estado)
{

}

void processa_semantico(token *tokenEncontrado, Automato *automato)
{
    token *tokenOperador = (token *) malloc (sizeof(token));
    token *tokenOperandoA = (token *) malloc (sizeof(token));
    token *tokenOperandoB = (token *) malloc (sizeof(token));


    //Verifica se esta lendo expressoes
    if(strcmp(automato->ID,"expressao")==0)
    {

        printf("\n Tipo do token %d, valor do token %s e estado da expressao %d ",tokenEncontrado->tipo,tokenEncontrado->valor,estadoExpressao);


        switch(estadoExpressao)
        {
            case ESTADO_EXP_A:

                switch(tokenEncontrado->tipo)
                {
                    case IDENTIFICADOR:

                            empilhaElemento(tokenEncontrado, &pilhaOperandos);
                            estadoExpressao = ESTADO_EXP_D;

                        break;

                    case INTEIRO:

                            empilhaElemento(tokenEncontrado, &pilhaOperandos);
                            estadoExpressao = ESTADO_EXP_D;

                        break;

                    case DELIMITADOR:

                        if(strcmp(tokenEncontrado->valor,"(")==0)
                        {
                            empilhaElemento(tokenEncontrado, &pilhaOperadores);
                            estadoExpressao = ESTADO_EXP_B;
                        }


                        break;


                }


                break;

            case ESTADO_EXP_B:

                estadoExpressao = ESTADO_EXP_C;

                processa_semantico(tokenEncontrado, automato);

                break;


            case ESTADO_EXP_C:

                if(tokenEncontrado->tipo == IDENTIFICADOR)
                {
                    empilhaElemento(tokenEncontrado, &pilhaOperandos);
                    estadoExpressao = ESTADO_EXP_D;
                }
                else
                if(tokenEncontrado->tipo == INTEIRO)
                {
                    empilhaElemento(tokenEncontrado, &pilhaOperandos);
                    estadoExpressao = ESTADO_EXP_D;
                }
                else
                if(strcmp(tokenEncontrado->valor,")")==0)
                {

                    int continuaLoop = 1;

                    while(continuaLoop == 1)
                    {

                        token *tokenTopo = consultaTopo(pilhaOperadores);

                        if(tokenTopo->valor == "(")
                        {
                            desempilhaElemento(&pilhaOperadores);
                            continuaLoop = 0;
                        }
                        else
                        {
                            geraCodigoExpressao(&tokenOperador, &tokenOperandoA,&tokenOperandoB);
                        }

                    }

                    estadoExpressao = ESTADO_EXP_D;

                }
                break;

            case ESTADO_EXP_D:

                if((strcmp(tokenEncontrado->valor,"+")==0)||(strcmp(tokenEncontrado->valor,"-")==0))
                {

                    int continuaLoop = 1;

                    while(continuaLoop == 1)
                    {

                        token *tokenTopo = consultaTopo(pilhaOperadores);

                        if(tokenTopo==NULL)
                        {
                            empilhaElemento(tokenEncontrado,&pilhaOperadores);
                            continuaLoop = 0;
                        }
                        else
                        if((strcmp(tokenTopo->valor,"+")==0)
                            ||(strcmp(tokenTopo->valor,"-")==0)
                            ||(strcmp(tokenTopo->valor,"*")==0)
                            ||(strcmp(tokenTopo->valor,"/")==0)
                           )
                        {
                            geraCodigoExpressao(&tokenOperador, &tokenOperandoA,&tokenOperandoB);
                        }
                        else
                        {
                            empilhaElemento(tokenEncontrado,&pilhaOperadores);
                            continuaLoop = 0;
                        }
                    }

                }
                else
                    if((strcmp(tokenEncontrado->valor,"*")==0)||(strcmp(tokenEncontrado->valor,"/")==0))
                    {
                        int continuaLoop = 1;

                        while(continuaLoop == 1)
                        {
                            token *tokenTopo = consultaTopo(pilhaOperadores);

                            if(tokenTopo==NULL)
                            {
                                empilhaElemento(tokenEncontrado,&pilhaOperadores);
                                continuaLoop = 0;
                            }
                            else
                            if((strcmp(tokenTopo->valor,"*")==0)||(strcmp(tokenTopo->valor,"/")==0))
                            {
                                geraCodigoExpressao(&tokenOperador, &tokenOperandoA,&tokenOperandoB);
                            }
                            else
                            {
                                empilhaElemento(tokenEncontrado,&pilhaOperadores);
                                continuaLoop = 0;
                            }
                        }

                    }


                estadoExpressao = ESTADO_EXP_A;
                break;


        }

    }
    else
    {
        if(estadoExpressao==ESTADO_EXP_D)
        {
            token *tokenTopo = consultaTopo(pilhaOperadores);

            while (tokenTopo!=NULL)
            {
                geraCodigoExpressao(&tokenOperador, &tokenOperandoA,&tokenOperandoB);
                tokenTopo = consultaTopo(pilhaOperadores);
            }

            estadoExpressao = ESTADO_EXP_A;
        }
        else
        {
            if(estadoExpressao != ESTADO_EXP_A)
                printf("\nErro na expressao %d ",estadoExpressao);
        }
    }


}

void geraCodigoExpressao(token **tokenOperadorAux, token **tokenOperandoA, token **tokenOperandoB)
{

    PilhaExpressao *pilhaExpressaoAux = (PilhaExpressao *) malloc (sizeof(PilhaExpressao));


    //Desempilha Operador
    pilhaExpressaoAux = (PilhaExpressao *) desempilhaElemento(&pilhaOperadores);

    if(pilhaExpressaoAux!=NULL)
        *tokenOperadorAux = (pilhaExpressaoAux)->token;
    else
        *tokenOperadorAux = NULL;

    //Desempilha Operando B
    if(pilhaOperandos!=NULL)
    {
        pilhaExpressaoAux = (PilhaExpressao *) desempilhaElemento(&pilhaOperandos);

        if(pilhaExpressaoAux!=NULL)
            *tokenOperandoB = (pilhaExpressaoAux)->token;
        else
            *tokenOperandoB = NULL;


    }
    else
    {
        *tokenOperandoB = NULL;
    }


    //Desempilha Operando A

    if(pilhaOperandos!=NULL)
    {

        pilhaExpressaoAux = (PilhaExpressao *) desempilhaElemento(&pilhaOperandos);

        if(pilhaExpressaoAux!=NULL)
            *tokenOperandoA = (pilhaExpressaoAux)->token;
        else
            *tokenOperandoA = NULL;

    }
    else
    {
        *tokenOperandoA = NULL;
    }

    if(*tokenOperandoA!=NULL)
    {
        if (((*tokenOperandoA)->tipo) == INTEIRO)
            printf("\n LV %s",(*tokenOperandoA)->valor);
        else
            printf("\n LD %s",(*tokenOperandoA)->valor);
    }


    if(*tokenOperandoB!=NULL)
    {
        if(strcmp((*tokenOperadorAux)->valor,"+")==0)
        {
            printf("\n + %s",(*tokenOperandoB)->valor);
        }
        else
            if(strcmp((*tokenOperadorAux)->valor,"-")==0)
            {
                printf("\n - %s",(*tokenOperandoB)->valor);
            }
            else
                if(strcmp((*tokenOperadorAux)->valor,"*")==0)
                {
                    printf("\n * %s",(*tokenOperandoB)->valor);
                }
                else
                    if(strcmp((*tokenOperadorAux)->valor,"/")==0)
                    {
                        printf("\n / %s",(*tokenOperandoB)->valor);
                    }


    }

    contatemp++;


    char result[50] = "\0";
    sprintf( result, "%d", contatemp );

    char variable[50] = "\0";
    strcpy (variable,"temp");
    strcat (variable,result);


    printf("\n MM %s",variable);

    token *tokenAux = (token *) malloc (sizeof(token));
    tokenAux->tipo = IDENTIFICADOR;
    int tamanho = strlen(variable)+1;
    tokenAux ->valor = (char*) malloc (tamanho * sizeof(char));
    strcpy(tokenAux->valor,variable);

    empilhaElemento(tokenAux,&pilhaOperandos);



}



