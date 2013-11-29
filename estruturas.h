#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

/*
    LISTA
*/

typedef struct _noLista{
    int id;
    char valor[100];
    int bloco;
    struct _noLista *prox; //Apronta para o próximo da lista
}noLista;

void inicializaLista(noLista **L);
void insereNo(int value, char *palavra, noLista **L, int bloco);
noLista* procuraLista(char *palavra, noLista *L);
int ultimoIdentificador(noLista *L);
int adicionaSimboloLista(char *palavra, noLista **lista) ;
int buscaSimboloLista(char *palavra, noLista *lista);

/*
    TOKEN
*/

typedef struct _token{
    int tipo;   //tipo do token
    char *valor; //valor do token
    struct _token *proxToken; //aponta para o proximo token
}token;

void inicializaToken(token **T);
token* insereToken(int tipo, char *valor, token **T);
void populaTabelaPalavrasReservadas(noLista **palavraReservada);
token* geraToken(int tipo, char *valor);




#endif // ESTRUTURAS_H_INCLUDED
