#ifndef AUTOMATO_H_INCLUDED
#define AUTOMATO_H_INCLUDED


typedef struct _automato {
    int estadoAtual;
    int estadoAnterior;
	int** funcaoDeTransicao;
} automato ;

typedef struct _definicaoDeTransicao {
	int estadoAtual;
	int proximoEstado;
	char caractereLido;
} definicaoDeTransicao;


#endif // AUTOMATO_H_INCLUDED
