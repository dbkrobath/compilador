#include "automato.h"


int** tabelaTransicao;

void inicializarAutomato()
{

    //entre outras coisas... inicia a tabela de transicao

	int numeroDeLinhas = 20;
	int numeroDeColunas = 176;

 	tabelaTransicao = (int **) calloc (numeroDeLinhas, sizeof(int*));
	int indiceLinha;
	for ( indiceLinha = 0; indiceLinha < numeroDeLinhas; indiceLinha++ )
		tabelaTransicao[indiceLinha] = (int*) calloc (numeroDeColunas, sizeof(int));

}

int obterProximoEstado(int estadoAtual, char caracterLido, int *tipoSaida)
{

    //consulta a tabela de transicoes com o estado atual e o caracter lido

    //retorna a saida do automato e o proximo estado


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
    char tokenType[30];


    while (fscanf(fTransicoes, "%d %d %d %s", &estadoAtual, &caracterLido, &estadoProximo, tokenType) >= 3)
    {
        tabelaTransicao[estadoAtual][caracterLido] = estadoProximo;
        printf("%d %d %d %s \n", estadoAtual, caracterLido, estadoProximo, tokenType);
    }

    fclose(fTransicoes);



    return 1;
}
