#ifndef AUTOMATO_H_INCLUDED
#define AUTOMATO_H_INCLUDED
#include <stdio.h>
#include "constantes.h"



void inicializarAutomato();

int obterProximoEstado(int estadoAtual, char caracterLido, int *tipoSaida);



#endif // AUTOMATO_H_INCLUDED
