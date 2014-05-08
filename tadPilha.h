/*
 * tadPilha.h
 *
 *  Created on: 30/04/2014
 *      Author: thiago
 */

#ifndef TADPILHA_H_
#define TADPILHA_H_

#include <stdio.h>
#include <stdlib.h>


typedef struct pilha Pilha;



Pilha* inicializarPilha(Pilha* p);
void push(Pilha* p, char* elemento, int no, int topo);
char* pop(Pilha* p);
int vazia(Pilha* p);
int buscaPosicaoReconhecida(Pilha* p);
int buscaNoTopo(Pilha* p);
int topo(Pilha* p);
int vaziaNTerminais(Pilha* p);
void imprimePilhaPosicaoAteTopo(Pilha* p, int pos);
void desempilhaDaPosicaoAteTopo(Pilha* p, int pos);






#endif /* TADPILHA_H_ */
