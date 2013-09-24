#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

typedef struct _noLista{
    int id;
    char *valor;
    struct _noLista *prox; //Apronta para o próximo da lista
}noLista;

void inicializaLista(noLista **L);
void insereNo(int value, char *palavra, noLista **L);
noLista* procuraLista(char *palavra, noLista **L);
int ultimoIdentificador(noLista **L);

typedef struct _token{
    int tipo;
    char *valor; //valor
    char *segundoValor;
}token;

token* criaToken(int tipo, char *valor);
token* procuraToken(int tipo, token *L);


#endif // ESTRUTURAS_H_INCLUDED
