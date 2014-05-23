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
	int reconhecidoAte[20];
	int no[20];
	char elementos[20][10]; //Pilha de tamanho 20 de strings de ate 10 caracteres
};


int vazia(Pilha* p){
	if(p->topo==0)return 1;
	return 0;
}

int vaziaNTerminais(Pilha* p){
	if(p->topo-1==0)return 1;
	return 0;
}

void imprimePilhaPosicaoAteTopo(Pilha* p, int pos){
	int i;
	for(i=pos;i<p->topo;i++){
		printf("%s, ",p->elementos[i]);
	}
	printf("\n");
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


void push(Pilha* p, char* elemento, int no, int topo){

	if(!cheia(p)){
		strcpy(p->elementos[p->topo],elemento);
		p->no[p->topo] = no;
		p->reconhecidoAte[p->topo] = topo;
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

void desempilhaDaPosicaoAteTopo(Pilha* p, int pos){
	p->topo = pos;
}

int buscaNoTopo(Pilha* p){
	if(!vazia(p)){
		return p->no[p->topo-1];
	}
	return -1;
}

int buscaPosicaoReconhecida(Pilha* p){
	if(!vazia(p)){
		return p->reconhecidoAte[p->topo-1];
	}
	return -1;
}

void imprimirPilha(Pilha *p){
	printf("Imprimindo Pilha\n");
	int i;
	if(!vazia(p)){
		for(i=p->topo-1;i>=0;i--){
			printf("%s - %d - %d\n",p->elementos[i], p->no[i], p->reconhecidoAte[i]+1);
		}
	}
}

int topo(Pilha* p){
	return p->topo;
}

