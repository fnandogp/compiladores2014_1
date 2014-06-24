/*
 * analisadorSintatico.h
 *
 *  Created on: 30/04/2014
 *      Author: thiago
 */

#ifndef ANALISADORSINTATICO_H_
#define ANALISADORSINTATICO_H_

void analisadorSintatico(FILE* codigo, char** TABGRAFO, char*** TABT, char*** TABNT, char*** ANASIN, int linhasTabNT, int** automato, Hash tab, FILE* tabVar, Hash tabProc);

#endif /* ANALISADORSINTATICO_H_ */
