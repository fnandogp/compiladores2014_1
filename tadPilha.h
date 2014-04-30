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
void push(Pilha* p, char* elemento);
char* pop(Pilha* p);
int vazia(Pilha* p);






#endif /* TADPILHA_H_ */
