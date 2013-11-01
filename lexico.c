#include "lexico.h"
#include <string.h>


noLista *NoPalavraReservada;
noLista *NoSimbolo;
noLista *NoString;
token *TokenLista;


/*
 variaveis utilizadas em extraiProximoToken para auxiliar na extraçao de tokens
*/
char proximoCaracter;
int proximoEstado = 0;
int estadoAtual = 0;
int tipoSaida = 0;
int fim_arquivo = 0;
int lerProximoCaracter = 1;

char tokenFormado[200];


/*
 Inicializacao do analisador Lexico
*/

void inicializarLexico()
{
    inicializaLista(&NoPalavraReservada);
    inicializaLista(&NoSimbolo);
    inicializaLista(&NoString);
    inicializaToken(&TokenLista);
    populaTabelaPalavrasReservadas(&NoPalavraReservada);
    inicializarAutomatoLex();

}


/*
    Extrai o proximo token do arquivo fonte sendo lido
    Quando acbarem os token retorna o tipo NO_TOKENS
*/


token * extraiProximoToken(FILE *programaFonte)
{
    tokenFormado[0] = '\0';

    while (fim_arquivo == 0){

        //Verifica se deve ler o proximo caracter do arquivo

        if(lerProximoCaracter==1)
        {

            //Le o proximo caracter do arquivo e, se for fim de arquivo, retorna o token atual e marca numa flag o fim do arquivo

            if(fscanf(programaFonte, "%c", &proximoCaracter) == EOF)
            {
                fim_arquivo = 1;

                proximoEstado = obterProximoEstado(estadoAtual, proximoCaracter, &tipoSaida);

                //caso tenha alguma saida a ser retornada antes de fechar o arquivo, retorna o token associado
                if(tipoSaida>0)
                {
                    return retornarTokenEncontrado(tokenFormado,tipoSaida);
                }

                break;
            }
        }
        else
        {
            lerProximoCaracter = 1;
        }


        //obtem a informacao do proximo estado e se tem algum retorno tipoSaida na transicao para o proximo estado
        proximoEstado = obterProximoEstado(estadoAtual, proximoCaracter, &tipoSaida);


        //estado 1 é o estadopadrão de erros (o tratamento de erros sera implemenrado depois)
        if(proximoEstado == 1)
        {
            printf("Erro no lexico");
            return 0;
        }


        //caso o automato tenha retornado algum tipo de saída, considera que um token foi identificado
        if(tipoSaida > 0)
        {

            if(verificaEspacador(proximoCaracter)==0)
            {
                lerProximoCaracter = 0;
            }

            estadoAtual = 0;

            return retornarTokenEncontrado(tokenFormado,tipoSaida);

            tokenFormado[0] = '\0';
        }
        else
        {

            //caso nenhum token tenha sido encontrado e o proximo estado nao é o inicial, adiciona
            if(proximoEstado>1)
                adicionarCharNaString(proximoCaracter, &tokenFormado);

            estadoAtual= proximoEstado;
        }



    }

    //retorna o tipo NO_TOKENS
    return retornarTokenEncontrado("",NO_TOKENS);

}


/*
    Retorna o struc token para a palavra de entrada
    Este método também insere na lista de simbolos e strings conforme o caso
*/

token* retornarTokenEncontrado(char* tokenEncontrado, int tipo)
{

    switch(tipo)
    {

        case INTEIRO:
            return insereToken(INTEIRO,tokenEncontrado,&TokenLista);
            break;

        case FLOAT:
            return insereToken(FLOAT,tokenEncontrado,&TokenLista);
            break;

        case NO_TOKENS:
            return geraToken(NO_TOKENS,"");
            break;

        case COMENTARIO:
            return geraToken(COMENTARIO,tokenEncontrado);
            break;

        case STRING:

            //adiciona na lista de strings
            adicionaSimboloLista(tokenEncontrado, &NoString);
            return insereToken(STRING,tokenEncontrado,&TokenLista);
            break;


        default:

            //Verifica se é uma palavra reservada

            if (buscaSimboloLista(tokenEncontrado, NoPalavraReservada) > 0) {
                return insereToken(PALAVRARESERVADA,tokenEncontrado,&TokenLista);
            }
            else //Verifica se ja existe na lista de simbolos
                if (buscaSimboloLista(tokenEncontrado, NoSimbolo) > 0) {
                    return insereToken(tipo,tokenEncontrado,&TokenLista);
                }
                else
                {
                    //adiciona na lista de simbolos
                    adicionaSimboloLista(tokenEncontrado, &NoSimbolo);
                    return insereToken(tipo,tokenEncontrado,&TokenLista);
                }

            break;
    }

}

/*
    Funcoes diversas
*/

void adicionarCharNaString(char caracter, char* stringOriginal) {
	int tamanho = strlen(stringOriginal);
	stringOriginal[tamanho] = caracter;
	stringOriginal[tamanho + 1] = '\0';
}

int verificaEspacador(char caracter)
{
    int caracterASC = caracter;

    switch(caracterASC)
    {
        case 32:
            return 1;
        break;

        case 9:
            return 1;
        break;

        case 13:
            return 1;
        break;

        case 10:
            return 1;
        break;
    }


    return 0;
}
