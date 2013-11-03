#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "sintatico.h"



ListaAutomatos *listaAutomatos;
Automato *automatoEmUso;
Estado *estadoEmUso;
PilhaEstados *pilhaEstados;

int aceitouLinguagem = 0;

void inicializarSintatico()
{
    inicializarListaAutomatos(&listaAutomatos);
    inicializarAutomato(&automatoEmUso);
    inicializarEstado(&estadoEmUso,0,0,1);
    inicializaPilha(&pilhaEstados);


    //carregarAutomatos(&listaAutomatos);
    carregarAutomatosJFLAP(&listaAutomatos);

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

    if(token->tipo==NO_TOKENS)
    {
        printf("\n\nNo tokens");

        if(estadoEmUso->estadoFinal==1)
        {
            printf("\n Estado final, não tem transicao para o token..., desempilha a pilha");

            PilhaEstados *pilhaEstadosAux = desempilhaEstado(&pilhaEstados);

            if(pilhaEstadosAux != NULL)
            {

                automatoEmUso = pilhaEstadosAux->automatoRetorno;
                estadoEmUso = pilhaEstadosAux->estadoRetorno;

                printf("\n Desempilha e volta para estado %d e automato %c",estadoEmUso->estado,*(automatoEmUso->ID));

                enviaTokenSintatico(token);
            }
            else
            {
                aceitouLinguagem = 1;
                printf("\n A pilha está vazia!!! ");
            }
        }
        else
        {
            aceitouLinguagem = -1;
            printf("\n Linguagem invalida!!! ");
        }
    }
    else
    {

        if((automatoEmUso!=NULL)&&(estadoEmUso!=NULL)&&(aceitouLinguagem >=0))
        {
            printf("\n\n Estado em uso %d, Maquina em uso %c",estadoEmUso->estado,*(automatoEmUso->ID));
            //Verifica se existe uma chamada de submaquina na etapa corrente
            if(estadoEmUso->chamadaSubMaquina!=NULL)
            {
                ChamadaSubMaquina *chamadaAux = estadoEmUso->chamadaSubMaquina;
                Estado *estadoRetorno = chamadaAux->estadoRetorno;

                empilhaEstado(automatoEmUso,estadoRetorno,&pilhaEstados);
                automatoEmUso = estadoEmUso->chamadaSubMaquina->proxAutomato;
                estadoEmUso = estadoInicial(automatoEmUso);

                printf("\n Empilha o estado de retorno %d e chamada de submaquina para  %c",estadoRetorno->estado,*(automatoEmUso->ID));

                enviaTokenSintatico(token);
            }
            else
            {
                ListaTransicao *listaTransicaoAux = estadoEmUso->listaTransicao;

                if(listaTransicaoAux==NULL)
                {
                    if(estadoEmUso->estadoFinal==1)
                    {
                        printf("\n Estado final, não tem transicao para o token..., desempilha a pilha");

                        PilhaEstados *pilhaEstadosAux = desempilhaEstado(&pilhaEstados);

                        if(pilhaEstadosAux != NULL)
                        {

                            automatoEmUso = pilhaEstadosAux->automatoRetorno;
                            estadoEmUso = pilhaEstadosAux->estadoRetorno;

                            printf("\n Desempilha e volta para estado %d e automato %c",estadoEmUso->estado,*(automatoEmUso->ID));

                            enviaTokenSintatico(token);
                        }
                        else
                        {
                            aceitouLinguagem = 1;
                            printf("\n A pilha está vazia!!! ");
                        }
                    }
                    else
                    {
                        aceitouLinguagem = -1;
                        printf("\n Linguagem invalida!!! ");
                    }
                }
                else
                {
                    while(listaTransicaoAux!=NULL)
                    {
                        Transicao *transicaoAux = listaTransicaoAux->transicao;

                        printf("\n Compara %s com o token %s ",transicaoAux->terminal,token->valor);

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

                            if(listaTransicaoAux==NULL)
                            {

                                if(estadoEmUso->estadoFinal==1)
                                {
                                    printf("\n Estado final, não tem transicao para o token..., desempilha a pilha");

                                    PilhaEstados *pilhaEstadosAux = desempilhaEstado(&pilhaEstados);

                                    if(pilhaEstadosAux != NULL)
                                    {

                                        automatoEmUso = pilhaEstadosAux->automatoRetorno;
                                        estadoEmUso = pilhaEstadosAux->estadoRetorno;

                                        printf("\n Desempilha e volta para estado %d e automato %c",estadoEmUso->estado,*(automatoEmUso->ID));

                                        enviaTokenSintatico(token);
                                    }
                                    else
                                    {
                                        aceitouLinguagem = 1;
                                        printf("\n A pilha está vazia!!! ");
                                    }
                                }
                                else
                                {
                                    aceitouLinguagem = -1;
                                    printf("\n Linguagem invalida!!! ");
                                }


                            }
                        }


                    }
                }

            }

        }

    }
}

void inicializarListaAutomatos(ListaAutomatos **L)
{
    *L = NULL;

    Automato *automatoT = (Automato *) malloc (sizeof(Automato));

    strcpy(automatoT->ID,"T");
    automatoT->listaEstados = NULL;
    strcpy(automatoT->XML_File_Name,"automatoT.xml");


    Automato *automatoE = NULL;

    automatoE = (Automato *) malloc (sizeof(Automato));

    strcpy(automatoE->ID,"E");
    automatoE->listaEstados = NULL;
    strcpy(automatoE->XML_File_Name,"automatoE.xml");

    adicionarListaAutomatos(automatoE,L);
    adicionarListaAutomatos(automatoT,L);


}


void carregarAutomatosJFLAP(ListaAutomatos **listaAutomatos)
{
    ListaAutomatos *lAux;
    lAux = *listaAutomatos;

    while(lAux!=NULL)
    {
        printf("\n\n Arquivo do automato : %s ",lAux->automato->XML_File_Name);



        int lendoEstados = 0;
            int estadoNum = 0;
            int estadoInicial= 0;
            int estadoFinal= 0;

        int lendoTransicoes = 0;
            int from = 0;
            int fromNum = 0;
            int to = 0;
            int toNum = 0;
            int read = 0;
            char readTerminal[20];


        ListaEstados *listaEstados;


        inicializaLista(&listaEstados);


        char *fname = lAux->automato->XML_File_Name;
        //strcpy(fname,);

        char tag[MaxStr], contents[MaxStr], tagname[MaxStr], attrname[MaxStr], value[MaxStr];

        float x1, y1, z1, x2, y2, z2, t0, t1;
        int linum=0;
        FILE *infile=0, *outfile=0;

        infile = fopen(fname,"r");
        if (infile==0) {printf("Error: Cannot open input file '%s'.\n",fname); exit(1);}
        xml_parse( infile, tag, contents, MaxStr, &linum );
        while (tag[0]!='\0')
        {
            xml_grab_tag_name( tag, tagname, MaxStr );	/* Get tag name. */

            /* Add your application code here to accept tag-name, such as: */
            //printf("Tag name = '%s'\n", tagname );

            if(strcmp(tagname,"state")==0)
            {
                lendoEstados = 1;

                //printf("Tag name comparaao = '%s'\n", tagname );
            }

            if((lendoEstados==1)&&(strcmp(tagname,"initial")==0))
            {
                estadoInicial = 1;

                //printf("Tag name comparaao = '%s'\n", tagname );
            }

            if((lendoEstados==1)&&(strcmp(tagname,"final")==0))
            {
                estadoFinal = 1;

                //printf("Tag name comparaao = '%s'\n", tagname );
            }

            if((lendoEstados==1)&&(strcmp(tagname,"/state")==0))
            {
                Estado *novoEstado;
                inicializarEstado(&novoEstado,estadoNum,estadoFinal,estadoInicial);
                adicionarListaEstados(novoEstado,&listaEstados);

                printf("\n Criou estado %d, estado inicial %d, estado final %d",novoEstado->estado,novoEstado->estadoInicial,novoEstado->estadoFinal);

                lendoEstados = 0;
                estadoNum = 0;
                estadoInicial = 0;
                estadoFinal = 0;


                //printf("Tag name comparaao = '%s'\n", tagname );
            }

            if(strcmp(tagname,"transition")==0)
            {
                lendoTransicoes = 1;

                //printf("Tag name comparaao = '%s'\n", tagname );
            }

            if((lendoTransicoes==1)&&(strcmp(tagname,"from")==0))
            {
                from = 1;
            }

            if((lendoTransicoes==1)&&(strcmp(tagname,"/from")==0))
            {
                from = 0;
            }

            if((lendoTransicoes==1)&&(strcmp(tagname,"to")==0))
            {
                to = 1;
            }

            if((lendoTransicoes==1)&&(strcmp(tagname,"/to")==0))
            {
                to = 0;
            }

            if((lendoTransicoes==1)&&(strcmp(tagname,"read")==0))
            {
                read = 1;
            }

            if((lendoTransicoes==1)&&(strcmp(tagname,"/read")==0))
            {
                read = 0;
            }

            if((lendoTransicoes==1)&&(strcmp(tagname,"/transition")==0))
            {
                lendoTransicoes = 0;

                Estado *estadoFrom = buscarEstadoPorNumero(listaEstados,fromNum);
                Estado *estadoTo = buscarEstadoPorNumero(listaEstados,toNum);

                if(readTerminal[0]=='"')
                {

                    //Cria uma transicao
                    Transicao* transicao = (Transicao *) malloc (sizeof(Transicao));
                    transicao->proximoEstado = estadoTo;

                    int i = 0;
                    char terminalSemAspas[20] = "\0";

                    for(i= 1;i<strlen(readTerminal)-1;i++)
                    {
                        terminalSemAspas[i-1] = readTerminal[i];
                    }

                    strcpy(transicao->terminal,terminalSemAspas);

                    ListaTransicao *listaTransicao = estadoFrom->listaTransicao;

                    adicionarListaTransicao(transicao,&listaTransicao);

                    estadoFrom->listaTransicao = listaTransicao;

                    printf("\n Criou transicao from %d to %d com o terminal %s ",estadoFrom->estado,estadoTo->estado,transicao->terminal);

                }
                else
                {
                    ChamadaSubMaquina* chamadaSubMaquina = (ChamadaSubMaquina *) malloc (sizeof(ChamadaSubMaquina));
                    Automato *automatoAux = buscarAutomatoPorID(*listaAutomatos,readTerminal);
                    if(automatoAux!=NULL)
                    {
                        chamadaSubMaquina->proxAutomato = automatoAux;
                    }

                    chamadaSubMaquina ->estadoRetorno = estadoTo;

                    estadoFrom->chamadaSubMaquina = chamadaSubMaquina;

                    printf("\n Criou chamada submaquina from %d para o automato %s com retorno em %d",estadoFrom->estado,automatoAux->ID,estadoTo->estado);

                    //Cria uma chamada de submaquina

                }







                //printf("Tag name comparaao = '%s'\n", tagname );
            }

            xml_grab_attrib( tag, attrname, value, MaxStr );	/* Get any attributes within tag. */
            while (value[0] != '\0')
            {
                /* Add application code here to accept attribute attrname and value, such as: */
                //printf(" Attribute: %s = '%s'\n", attrname, value );

               if((lendoEstados==1) && (strcmp(attrname,"id")==0))
               {
                    estadoNum = atoi(value);
               }

                xml_grab_attrib( tag, attrname, value, MaxStr );	 /* Get next attribute, if any. */
            }

            /* Add application code here to accept contents between tags, such as: */
            //printf("\n Contents = '%s'\n", contents );

            if(from == 1)
            {
                fromNum = atoi(contents);
            }

            if(to == 1)
            {
                toNum = atoi(contents);
            }

            if(read==1)
            {
                strcpy(readTerminal,contents);

            }

            xml_parse( infile, tag, contents, MaxStr, &linum );


        }
        fclose(infile);

        Automato *automatoAux = buscarAutomatoPorID(*listaAutomatos,lAux->automato->ID);
        automatoAux->listaEstados = listaEstados;

        lAux = lAux->prox;
    }

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

    Automato *automatoT = buscarAutomatoPorID(*L,"T");

    Automato *automatoE = buscarAutomatoPorID(*L,"E");


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

Automato* buscarAutomatoPorID(ListaAutomatos *listaAutomatos,char ID[40])
{
    while(listaAutomatos!=NULL)
    {
        if(listaAutomatos->automato!=NULL)
        {
            if(strcmp(listaAutomatos->automato->ID,ID)==0)
            {
                return listaAutomatos->automato;
            }
        }

        listaAutomatos = listaAutomatos->prox;
    }

    return NULL;
}

void semantico_tbd()
{

}
