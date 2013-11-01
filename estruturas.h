#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

/*
    LISTA
*/

typedef struct _noLista{
    int id;
    char *valor;
    struct _noLista *prox; //Apronta para o próximo da lista
}noLista;

void inicializaLista(noLista **L);
void insereNo(int value, char *palavra, noLista **L);
noLista* procuraLista(char *palavra, noLista *L);
int ultimoIdentificador(noLista **L);
int adicionaSimboloLista(char *palavra, noLista **lista) ;
int buscaSimboloLista(char *palavra, noLista *lista);

/*
    TOKEN
*/

typedef struct _token{
    int tipo;   //tipo do token
    char *valor; //valor do token
    struct _token *proxToken //aponta para o proximo token
}token;

void inicializaToken(token **T);
token* insereToken(int tipo, char *valor, token **T);

/*
    PILHA
*/

typedef struct _pilhaEstados{
    int estado;
    struct _pilhaEstados *estadoAnterior;
}pilhaEstados;

void inicializaPilha(pilhaEstados **);
void empilhaEstado(int estado, pilhaEstados **P);
int desempilhaEstado(pilhaEstados **P);


#endif // ESTRUTURAS_H_INCLUDED
