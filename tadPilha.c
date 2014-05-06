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
	int no[20];
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


void push(Pilha* p, char* elemento, int no){

	if(!cheia(p)){
		strcpy(p->elementos[p->topo],elemento);
		p->no[p->topo] = no;
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

int buscaNoTopo(Pilha* p){
	if(!vazia(p)){
		return p->no[p->topo-1];
	}
	return -1;
}

void imprimirPilha(Pilha *p){
	printf("Imprimindo Pilha\n");
	int i;
	if(!vazia(p)){
		for(i=0;i<p->topo;i++){
			printf("%s - %d\n",p->elementos[i], p->no[i]);
		}
	}
}

