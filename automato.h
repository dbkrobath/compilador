#ifndef AUTOMAO_H_INCLUDED
#define AUTOMAO_H_INCLUDED

//Submaquinas



typedef struct {} Estado;
typedef struct {} ListaEstados;

typedef struct _automato{
    char* ID;
    Estado* estadoAtual;
    ListaEstados* listaEstados;
} Automato;

void inicializarAutomato(Automato **A);

void printAutomato(Automato* A);


typedef struct _chamadaSubMaquina{
    Automato* proxAutomato;
    Estado* estadoRetorno;
}ChamadaSubMaquina;


typedef struct _listaChamadasSubMaquina{

    ChamadaSubMaquina* chamadaSubMaquina;
    struct _listaChamadasSubMaquina *prox;

}ListaChamadasSubMaquina;

typedef struct _transicao{
    Estado* proximoEstado;
    char* terminal;
}Transicao;

typedef struct _listaTransicao{
    Transicao* transicao;
    struct _listaTransicao *prox;
}ListaTransicao;

void inicializarListaTransicao(ListaTransicao **L);
void adicionarListaTransicao(Transicao* T,ListaTransicao **L);

struct Estado{
    int estado;
    int estadoFinal;
    int estadoInicial;
    ListaTransicao* listaTransicao;
    ChamadaSubMaquina* chamadaSubMaquina;
};

struct ListaEstados{
    Estado* estado;
    ListaEstados *prox;
};

void inicializarListaEstados(ListaEstados **L);
void adicionarListaEstados(Estado* E,ListaEstados **L);






#endif // AUTOMAO_H_INCLUDED
