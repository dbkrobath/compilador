#ifndef AUTOMATO_H_INCLUDED
#define AUTOMATO_H_INCLUDED

int** tabelaTransicao;

void inicializarAutomato();

int obterProximoEstado(int estadoAtual, char caracterLido, int *tipoSaida);


#endif // AUTOMATO_H_INCLUDED
