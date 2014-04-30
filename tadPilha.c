/*
 * tadPilha.c
 *
 *  Created on: 30/04/2014
 *      Author: thiago
 */

#include "tadPilha.h"
#include <string.h>

struct pilha{
	int topo;
	char elementos[20][10]; //Pilha de tamanho 20 de strings de ate 10 caracteres
};


int vazia(Pilha* p){
	if(p->topo==0)return 1;
	return 0;
}

int cheia(Pilha* p){
	if(p->topo==20)return 1;
	return 0;
}

Pilha* inicializarPilha(Pilha* p){

	p = (Pilha*)malloc(sizeof(Pilha));
	p->topo=0;
	return p;
}


void push(Pilha* p, char* elemento){

	if(!cheia(p)){
		strcpy(p->elementos[p->topo],elemento);
		p->topo++;
	}else{
		printf("Pilha cheia\n");
	}

}

char* pop(Pilha* p){

	if(!vazia(p)){
		p->topo--;
		return p->elementos[p->topo];
	}

	return NULL;


}

