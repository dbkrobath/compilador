#include "lexico.h"
#include <string.h>

/*
    ESTADO 0 : Estado inicial
    ESTADO 1 : Estado de erro
*/


void adicionarCharNaString(char caracter, char* stringOriginal) {
	int tamanho = strlen(stringOriginal);
	stringOriginal[tamanho] = caracter;
	stringOriginal[tamanho + 1] = '\0';
}


void extrairTokens(FILE *programaFonte)
{
    char caracterLido;
    int proximoEstado = 0;
    int estadoAtual = 0;
    int tipoSaida = 0;
    char tokenFormado[200];

    tokenFormado[0] = '\0';

    while (fscanf(programaFonte, "%c", &caracterLido) != EOF){

        estadoAtual = proximoEstado;

        //obtem o proximo estado a partir do caracter atual
        proximoEstado = MOCKUPobterProximoEstado(estadoAtual, caracterLido, &tipoSaida);


        //estado de erro
        if(proximoEstado == 1)
        {
            printf("Erro no lexico");
        }
        else
        {
            //caso o automato tenha retornado algum tipo de saída, considera que um token foi identificado
            if(tipoSaida > 0)
            {
                printf("%s",tokenFormado);

                //reinicia o token
                tokenFormado[0] = '\0';
            }
            else
            {
                adicionarCharNaString(caracterLido, tokenFormado);
            }
        }


    }
}
