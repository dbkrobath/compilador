#include "automato.h"


int** tabelaTransicao;
int* tabelaSaida;

void inicializarAutomato()
{
    //entre outras coisas... inicia a tabela de transicao

	int numeroDeLinhas = 25;
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
        printf( "Erro na abertura do arquivo");
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

int obterProximoEstado(int estadoAtual, char caracterLido, int *tipoSaida)
{
    int caracterASC = caracterLido;

    int proximoEstado = tabelaTransicao[estadoAtual][caracterASC];

    if(proximoEstado==0)
        *tipoSaida = tabelaSaida[estadoAtual];
    else
        *tipoSaida = 0;

    printf("\n tipo saida antes do retorno %d e estado atual %d",*tipoSaida,estadoAtual);

    return proximoEstado;

}


