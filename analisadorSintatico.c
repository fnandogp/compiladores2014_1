/*
 * analisadorSintatico.c
 *
 *  Created on: 30/04/2014
 *      Author: thiago
 */

#include <stdio.h>
#include <stdlib.h>
#include "tadPilha.h"
#include <string.h>


int verificaLinhaTerminal(char*** TABNT, int linhas, char* naoTerminal){

	int i;
	for(i=0;i<linhas;i++){
		if(strcmp(TABNT[i][1],naoTerminal)==0){
			return atoi(TABNT[i][2])-1;
		}
	}
	return -1;
}


int analisadorSintatico(FILE* codigo, char** TABGRAFO, char*** TABT, char*** TABNT, char*** ANASIN, int linhasTabNT){


	//Inicializa as Pilhas
	Pilha* cadeia = inicializarPilha(cadeia);
	Pilha* naoTerminais = inicializarPilha(naoTerminais);
	push(naoTerminais,"S",10,0);

	char* cadCaracteres = (char *)malloc(20*sizeof(char));
	char* cadTerminais = (char *)malloc(20*sizeof(char));
	char* p = (char *)malloc(20*sizeof(char));

	//Isso sera alterado quando comecarmos a ler strings ao inves de caracteres
	char c;
	char caracter[2];
	int numeroLinha = 0;
	int aux=0;
	int flag = 0;
	do{
		c = fgetc(codigo);
		if(feof(codigo)){
			break;
		}
		caracter[0] = c;
		caracter[1] = '\0';

		//Lixo no fim do arquivo
		if(c=='\n'){
			break;
		}
		//Fim do lixo no fim do arquivo

		if(aux==-1){
			printf("Cadeia nao aceita\n");
			return 0;
		}

		while(1){
			// para aux == -2 
			while(aux==-2 && !vaziaNTerminais(naoTerminais)){
				imprimirPilha(naoTerminais);
				aux = atoi(ANASIN[buscaNoTopo(naoTerminais)][4])-1;
				if(aux==-1) aux = -2;
				if(aux!=-2 && strcmp(ANASIN[aux][1],caracter)!=0) aux = -2;
				//printf("Linha = %d\n",aux);
				printf("O Nao Terminal abaixo eh pai de: ");
				imprimePilhaPosicaoAteTopo(cadeia, buscaPosicaoReconhecida(naoTerminais));
				desempilhaDaPosicaoAteTopo(cadeia,buscaPosicaoReconhecida(naoTerminais)); //Adicionar uma especie de fila aqui
				strcpy(p, pop(naoTerminais));
				push(cadeia,p,0,0);
				printf("Desempilha o terminal %s\n",p);
			}
			if(vaziaNTerminais(naoTerminais) && aux==-2){
				printf("Cadeia nao aceita\n");
				return 0;
			}

			// Para um Terminal encontrado
			if(strcmp(ANASIN[aux][0],"T")==0){

				// para caracter lido reconhecido
				if(strcmp(ANASIN[aux][1],caracter)==0){
					printf("Caracter %c aceito! Proxima linha = %d\n",c,atoi(ANASIN[aux][4])-1);
					strcpy(cadCaracteres,ANASIN[aux][1]);
					push(cadeia,cadCaracteres,0,0); //Insere na pilha o caracter reconhecido
					imprimirPilha(cadeia);
					aux = atoi(ANASIN[aux][4])-1; //Aux recebe a linha correspondente ao sucessor do no encontrado
					if(aux==-1)aux=-2;
					break;
				}
				// para caracter não reconhecido
				else {
					aux = atoi(ANASIN[aux][3])-1; //Aux recebe a posicao do no alternativo
					
					//Caso nao haja mais nenhum no alternativo
					if(aux==-1){
						printf("Cadeia nao aceita\n");
						return 0;
					}
				}
			}
			// para um não terminal encontrado
			else if(strcmp(ANASIN[aux][0],"N")==0){ //Encontra um Nao Terminal
				strcpy(cadTerminais,ANASIN[aux][1]);
				push(naoTerminais,cadTerminais,atoi(ANASIN[aux][2])-1,topo(cadeia)); //Empilha o nao terminal na pilha de nao naoTerminais
				//	printf("No que devemos voltar = %d\n",atoi(ANASIN[aux][2])-1);
				printf("Nao terminal encontrado: %s! Devemos empilha-lo\n",cadTerminais);
				imprimirPilha(naoTerminais);
				aux = verificaLinhaTerminal(TABNT,linhasTabNT,cadTerminais); //Aux vai para a linha correspondente ao grafo do nao terminal
			//	printf("Linha = %d\n",aux);
			}
		}
		numeroLinha = aux;




	}while(1);

	while(!vazia(naoTerminais)){
		printf("O Nao Terminal Abaixo eh pai de: ");
		imprimePilhaPosicaoAteTopo(cadeia, buscaPosicaoReconhecida(naoTerminais));

		desempilhaDaPosicaoAteTopo(cadeia,buscaPosicaoReconhecida(naoTerminais));
		strcpy(p,pop(naoTerminais));
		printf("Desempilhando o %s\n",p);
		push(cadeia,p,0,0);
	}

	printf("Cadeia reconhecida!\n");



	return 1;


}
