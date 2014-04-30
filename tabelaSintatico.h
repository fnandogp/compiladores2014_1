/*
 * tabelaSintatico.h
 *
 *  Created on: 30/04/2014
 *      Author: thiago
 */

#ifndef TABELASINTATICO_H_
#define TABELASINTATICO_H_

#include <stdio.h>
#include <stdlib.h>

char** inicializaTABGRAFO(char **matrix, int linhas, int colunas);
void carregaTABGRAFO(char **matrix, int linhas, int colunas, FILE* tabgrafo);
char*** inicializaTABT(char*** matrix, int linhas, int colunas);
void carregaTABT(char*** matrix, int linhas, int colunas, FILE* tabt);
char*** inicializaTABNT(char*** matrix, int linhas, int colunas);
void carregaTABNT(char*** matrix, int linhas, int colunas, FILE* tabnt);
char*** inicializaANASIN(char*** matrix, int linhas, int colunas);
void carregaAnaSin(char*** TabAnaSin, char** TABGRAFO, int linhasG, int colunasG, char*** TABT, int linhasT, int colunasT, char*** TABNT, int linhasNT, int colunasNT);


#endif /* TABELASINTATICO_H_ */
