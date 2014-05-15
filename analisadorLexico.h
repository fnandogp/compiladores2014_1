/*
 * analisadorLexico.h
 *
 *  Created on: 24/04/2014
 *      Author: thiago
 */
#ifndef ANALISADORLEXICO_H_
#define ANALISADORLEXICO_H_

#include "hash.h"


int executaAnalisador(FILE* arquivoEntrada, int** automato, int linhas, int colunas,  Hash tab, int* posicaoArquivo, char** vetor);
void acoesSemanticas(int tipoAcao, char* buffer, int posicao, char* tipoSimbolo, char simbolo, Hash tab);

#endif /* ANALISADORLEXICO_H_ */
