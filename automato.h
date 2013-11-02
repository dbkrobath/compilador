#ifndef AUTOMAO_H_INCLUDED
#define AUTOMAO_H_INCLUDED

//Submaquinas



typedef struct _automato{
    char* ID;
    struct Estado* estadoAtual;
    struct ListaEstados* listaEstados;
} Automato;

void inicializarAutomato(Automato **A);

void printAutomato(Automato* A);


typedef struct _chamadaSubMaquina{
    struct Automato* proxAutomato;
    struct Estado* estadoRetorno;
}ChamadaSubMaquina;


typedef struct _listaChamadasSubMaquina{

    struct ChamadaSubMaquina* chamadaSubMaquina;
    struct _listaChamadasSubMaquina *prox;

}ListaChamadasSubMaquina;

typedef struct _transicao{
    struct Estado* proximoEstado;
    char* terminal;
}Transicao;

typedef struct _listaTransicao{
    Transicao* transicao;
    struct _listaTransicao *prox;
}ListaTransicao;

void inicializarListaTransicao(ListaTransicao **L);
void adicionarListaTransicao(Transicao* T,ListaTransicao **L);

typedef struct _estado{
    int estado;
    int estadoFinal;
    int estadoInicial;
    ListaTransicao* listaTransicao;
    ChamadaSubMaquina* chamadaSubMaquina;
}Estado;

typedef struct _listaEstados{
    Estado* estado;
    struct _listaEstados *prox;
}ListaEstados;

void inicializarListaEstados(ListaEstados **L);
void adicionarListaEstados(Estado* E,ListaEstados **L);






#endif // AUTOMAO_H_INCLUDED
