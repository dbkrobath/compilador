#ifndef AUTOMATO_H_INCLUDED
#define AUTOMATO_H_INCLUDED
#include <stdio.h>
#include "automato.h"

int** tabelaTransicao;

void inicializarAutomato();

int obterProximoEstado(int estadoAtual, char caracterLido, int *tipoSaida);



#endif // AUTOMATO_H_INCLUDED
