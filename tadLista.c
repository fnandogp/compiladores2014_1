#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadLista.h"


struct lista{
	char *info;
	struct lista *prox;
};

Lista* lista_construir (void) {
	return NULL;
}

void lista_alterarInfo(Lista* l, char* novaInfo){
	char info[30];
	strcpy(info, l->info);
	strcat(info, novaInfo);
	l->info = (char *)realloc(l->info, sizeof(info));
	strcpy(l->info, info);
}

void lista_imprimir (Lista* l) {
	if(!l) {
		printf("|");
		return;
	}
	lista_imprimir(l->prox);
	printf(" %s |", l->info);
}

int lista_vazia (Lista* l) {
	return !l;
}

Lista* lista_inserir (Lista* l, char palavra[]) {
	Lista *novo;
	novo = (Lista *)malloc(sizeof(Lista));

	novo->info = (char*) malloc ((strlen(palavra) + 1) * sizeof(char));
	strcpy(novo->info, palavra);
	
	novo->prox = l;

	return novo;
}

Lista* lista_consultar (Lista* l, char palavra[]) {
	Lista *aux;
	aux = l;

	while(aux) {
		if (strcmp(aux->info, palavra) == 0) {
			return aux;
		}
		aux = aux->prox;
	}
	return NULL;
}

void imprimeVariaveis(Lista* l, char* tipo, FILE* arquivo){
	
	Lista* aux = l;
	while(aux!=NULL){
		fprintf(arquivo, "	%s %s;\n", tipo, aux->info);
		aux = aux->prox;
	}
}

