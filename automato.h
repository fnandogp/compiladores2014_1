/*
 * automato.h
 *
 *  Created on: 24/04/2014
 *      Author: thiago
 */

#ifndef AUTOMATO_H_
#define AUTOMATO_H_


int** inicializaMatrizAutomato(int **matrix, int linhas, int colunas);
void carregaAutomato(int **matrix, int linhas, int colunas, FILE* automato);
int verificaSimboloLido(char c);
int verificaProximaTransicao(int **matrix, int estadoAtual, int tipoLido, int linhas, int colunas);
int verificaTransicaoAtual(int **matrix, int estadoAtual, int tipoLido, int linhas, int colunas);


#endif /* AUTOMATO_H_ */
