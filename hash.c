#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


//Gera a chave da tabela hash sendo o resto da divisão de um numero pelo tamanho da Hash
int geraChave(int num){
	return(num%TAM);
}

int iniciaTSR(Hash tab, FILE* arqSR){
	inicializaHash(tab); //Inicializa a tabela como null;
	char buffer[50]; //Define o tamanho do buffer (palavras de tamanho no maximo 6)
	char* pch;
	if(arqSR!=NULL){ 
		while(fgets(buffer, 1000, arqSR)){
			pch = strtok(buffer,"\n");
			//printf("%s\n",pch);
			insereS(tab, pch);
		}

		fclose(arqSR);
		return 1;
		
	}else{
		printf("Falha ao abrir o arquivo");
		return 0;
	}
}

void insereTipo(Celula* item, char* simbolo){
	if(simbolo[0]>64 && simbolo[0]<123){
		item->tipo = "Palavra reservada";
	}else{
		item->tipo = "Simbolo especial";
	}
}


int representacaoInteira(char* simbolo){

	int ascii = 0;
	int size = strlen(simbolo);
	int i;
	for(i=0;i<size;i++){
		if(simbolo[i]!='\n'){
			ascii = ascii + simbolo[i];
		}
	}
	return ascii;
}

void inicializaHash(Hash tab){
	int i;
	
	for(i=0;i<TAM;i++){
		tab[i] = NULL;
	}
}

void insereS(Hash tabS, char* item){
	int chave;
	int i;
	int codigo = representacaoInteira(item);
	chave = geraChave(codigo);
	Celula* aux = tabS[chave];
	while(aux!=NULL){
		if(strcmp(aux->simbolo,item)==0){
			break;
		}
		aux = aux->prox;
	}
	if(aux==NULL){
		Celula* celula = (Celula *)malloc(sizeof(Celula));
		strcpy(celula->simbolo,item);
		celula->prox = tabS[chave];
		insereTipo(celula, item);
		tabS[chave] = celula;
	}
}

void imprimeHash(Hash tab){
	
	printf("IMPRIMINDO TABELA DE SIMBOLOS\n");
	Celula* aux;
	int i;
	for(i=0;i<TAM;i++){
		
		if(tab[i]!=NULL){
			aux = tab[i];
			printf("Posicao: %d\n",i);
			printf("Simbolo(s):\n");
			while(aux!=NULL){
				printf("%s\n",aux->simbolo);
				printf("Tipo: %s\n",aux->tipo);
				aux = aux->prox;
							
			}		
		}
	}
}


int consultaSR(Hash tab, char* simbolo){
	int chave;
	int codigo = representacaoInteira(simbolo);
	chave = geraChave(codigo);
	Celula* aux = tab[chave];
	while(aux!=NULL){
		if(strcmp(aux->simbolo,simbolo)==0){
			return 1;
		}
		aux = aux->prox;
	}
	
	if(aux==NULL){
		return 0;
	}
}
