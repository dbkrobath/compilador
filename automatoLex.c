#include "automatoLex.h"

//matrix de trainsicoes, linhas sao os estados e colunas os caracters em codigo ASC
int** tabelaTransicao;

//tabela contendo o codigo dos tipos de saidas dos estados quando voltam ao estado inicial
int* tabelaSaida;


/*
    Le a descricao do automato em transicoes.txt
*/

void inicializarAutomatoLex()
{


	int numeroDeLinhas = NUMERO_ESTADOS +2;
	int numeroDeColunas = 176;

 	tabelaTransicao = (int **) calloc (numeroDeLinhas, sizeof(int*));
	int indiceLinha;
	for ( indiceLinha = 0; indiceLinha < numeroDeLinhas; indiceLinha++ )
		tabelaTransicao[indiceLinha] = (int*) calloc (numeroDeColunas, sizeof(int));

    tabelaSaida = (int*) calloc (numeroDeLinhas, sizeof(int));

    FILE *fTransicoes;
    char c;

    fTransicoes = fopen("transicoes.txt","r");
    if(!fTransicoes)
    {
        printf( "Erro na abertura do arquivo de transicoes");
        exit(0);
    }

    int estadoAtual;
    int caracterLido;
    int estadoProximo;
    int tipoSaida;

    while (fscanf(fTransicoes, "%d %d %d %d", &estadoAtual, &caracterLido, &estadoProximo, &tipoSaida) >= 3)
    {
        tabelaTransicao[estadoAtual][caracterLido] = estadoProximo;

        if(estadoProximo==0)
            tabelaSaida[estadoAtual] = tipoSaida;
    }

    fclose(fTransicoes);

}

/*
    Obtem o proximo estado do automato e, se houver, o codigo associado ao output da transição
    Recebe estado atual e o caracter lido
*/

int obterProximoEstado(int estadoAtual, char caracterLido, int *tipoSaida)
{
    int caracterASC = caracterLido;

    int proximoEstado = tabelaTransicao[estadoAtual][caracterASC];

    if(proximoEstado==0)
        *tipoSaida = tabelaSaida[estadoAtual];
    else
        *tipoSaida = 0;

    return proximoEstado;

}


