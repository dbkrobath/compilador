#include <stdio.h>
#include <stdlib.h>

void printArray(int ** tabelaTransicao)
{
    //FILE *fTabela;
    //Transicoes = fopen("transicoes.txt","w");
    int i, j;

    printf("\n");

    for(j=20;j<29;j++)
        printf("\t%d ",j);

    for(i = 0;i<4;i++)
    {
        printf("\n%d\t",i);

        for(j=20;j<29;j++)
        {
            printf("%d\t",tabelaTransicao[i][j]);
        }

    }

    //fclose(fTabela);
}

int main()
{
    FILE *fTransicoes;
    char c;

	int** tabelaTransicao;
	int numeroDeLinhas = 20;
	int numeroDeColunas = 176;

 	tabelaTransicao = (int **) calloc (numeroDeLinhas, sizeof(int*));
	int indiceLinha;
	for ( indiceLinha = 0; indiceLinha < numeroDeLinhas; indiceLinha++ )
		tabelaTransicao[indiceLinha] = (int*) calloc (numeroDeColunas, sizeof(int));


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

    printArray(tabelaTransicao);

    return 0;
}
