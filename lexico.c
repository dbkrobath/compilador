#include "lexico.h"
#include <string.h>

/*
    ESTADO 0 : Estado inicial
    ESTADO 1 : Estado de erro
*/

noLista *NoPalavraReservada;
noLista *NoSimbolo;
noLista *NoString;
token *TokenLista;

void adicionarCharNaString(char caracter, char* stringOriginal) {
	int tamanho = strlen(stringOriginal);
	stringOriginal[tamanho] = caracter;
	stringOriginal[tamanho + 1] = '\0';
}

void inicializarLexico()
{
    inicializaLista(&NoPalavraReservada);
    inicializaLista(&NoSimbolo);
    inicializaLista(&NoString);
    inicializaToken(&TokenLista);
    populaTabelaPalavrasReservadas(&NoPalavraReservada);

    inicializarAutomato();

    //imprimeLista(NoPalavraReservada);

}

void imprimeLista(noLista *lista) {

    noLista *paux;

    paux = lista;

    while(paux!=NULL){
        printf("\nidentificador %d",paux->id);
        printf("\npalavra %s",paux->valor);
        printf("\n");
        paux = paux->prox;
    }
    printf("\n");

}

void imprimeTokens(token *Tlista) {

    token *taux;

    taux = Tlista;

    while(taux!=NULL){
        printf("\n tipo %d",taux->tipo);
        printf("\n valor %s",taux->valor);
        printf("\n");
        taux = taux->proxToken;
    }
    printf("\n");

}

int verificaEspacador(char caracter)
{
    int caracterASC = caracter;

    switch(caracterASC)
    {
        case 32:
            return 1;
        break;

        case 9:
            return 1;
        break;

        case 13:
            return 1;
        break;

        case 10:
            return 1;
        break;
    }


    return 0;
}


void extrairTokens(FILE *programaFonte)
{
    char proximoCaracter;
    int proximoEstado = 0;
    int estadoAtual = 0;
    int tipoSaida = 0;

    int lerProximoCaracter = 1;

    char tokenFormado[200];

    tokenFormado[0] = '\0';


    while (1){


        if(lerProximoCaracter==1)
        {


            if(fscanf(programaFonte, "%c", &proximoCaracter) == EOF)
            {
                proximoEstado = obterProximoEstado(estadoAtual, proximoCaracter, &tipoSaida);

                if(tipoSaida>0)
                {
                    registrarTokenEncontrado(tokenFormado,tipoSaida);
                }

                registrarTokenEncontrado("",NO_TOKENS);
                break;
            }


        }
        else
        {
            lerProximoCaracter = 1;
        }

        proximoEstado = obterProximoEstado(estadoAtual, proximoCaracter, &tipoSaida);

        if(proximoEstado == 1)
        {
            printf("Erro no lexico");
            return 0;
        }

        //if(lerProximoCaracter==0)


        //caso o automato tenha retornado algum tipo de saída, considera que um token foi identificado
        if(tipoSaida > 0)
        {

            if(verificaEspacador(proximoCaracter)==0)
            {
                lerProximoCaracter = 0;
            }


            registrarTokenEncontrado(tokenFormado,tipoSaida);

            tokenFormado[0] = '\0';
        }
        else
        {

            //concatena o caracter lido a
            if(proximoEstado>1)
                adicionarCharNaString(proximoCaracter, &tokenFormado);
        }


        estadoAtual= proximoEstado;
    }


    imprimeTokens(TokenLista);
}

void registrarTokenEncontrado(char* tokenEncontrado, int tipo)
{

    switch(tipo)
    {

        case INTEIRO:
            insereToken(INTEIRO,tokenEncontrado,&TokenLista);
            break;

        case FLOAT:
            insereToken(FLOAT,tokenEncontrado,&TokenLista);
            break;

        case NO_TOKENS:
            insereToken(NO_TOKENS,"",&TokenLista);
            break;

        case STRING:

            adicionaSimboloLista(tokenEncontrado, &NoString);
            insereToken(STRING,tokenEncontrado,&TokenLista);
            break;



        //deals with string
        default:

            //    Verifica se palavra esta na lista de palavras reservadas!
            //imprimeLista(NoPalavraReservada);

            if (buscaSimboloLista(tokenEncontrado, NoPalavraReservada) > 0) {
                insereToken(PALAVRARESERVADA,tokenEncontrado,&TokenLista);
            }
            else
                if (buscaSimboloLista(tokenEncontrado, NoSimbolo) > 0) {
                    insereToken(tipo,tokenEncontrado,&TokenLista);
                }
                else
                {
                    adicionaSimboloLista(tokenEncontrado, &NoSimbolo);
                    insereToken(tipo,tokenEncontrado,&TokenLista);
                }

            break;
    }


}
