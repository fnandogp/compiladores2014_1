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
	Pilha* terminais = inicializarPilha(terminais);

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
			while(aux==-2 && !vazia(terminais)){
				imprimirPilha(terminais);
				aux = atoi(ANASIN[buscaNoTopo(terminais)][4])-1;
				if(aux==-1) aux = -2;
				if(aux!=-2 && strcmp(ANASIN[aux][1],caracter)!=0) aux = -2;
				printf("Linha = %d\n",aux);
				strcpy(p, pop(terminais));
				printf("Desempilha o terminal %s\n",p);
			}
			if(vazia(terminais) && aux==-2){
				printf("Cadeia nao aceita\n");
				return 0;
			}
			if(strcmp(ANASIN[aux][1],caracter)==0){ //Encontra na tabela ANASIN o caracter lido
				printf("Caracter %c aceito! Proxima linha = %d\n",c,atoi(ANASIN[aux][4])-1);
				strcpy(cadCaracteres,ANASIN[aux][1]);
				push(cadeia,cadCaracteres,0); //Insere na pilha o caracter reconhecido
				aux = atoi(ANASIN[aux][4])-1; //Aux recebe a linha correspondente ao sucessor do no encontrado
				if(aux==-1)aux=-2;
				break;
			}else{
				if(strcmp(ANASIN[aux][0],"N")==0){ //Encontra um Nao Terminal
					strcpy(cadTerminais,ANASIN[aux][1]);
					push(terminais,cadTerminais,atoi(ANASIN[aux][2])-1); //Empilha o nao terminal na pilha de nao terminais
					printf("No que devemos voltar = %d\n",atoi(ANASIN[aux][2])-1);
					printf("Nao terminal encontrado: %s! Devemos empilha-lo\n",cadTerminais);
					aux = verificaLinhaTerminal(TABNT,linhasTabNT,cadTerminais); //Aux vai para a linha correspondente ao grafo do nao terminal
					printf("Linha = %d\n",aux);
				}else{
					aux = atoi(ANASIN[aux][3])-1; //Aux recebe a posicao do no alternativo
					if(aux==-1){ //Caso nao haja mais nenhum no alternativo
						//if(vazia(terminais)){ //Verifica se a pilha de terminais esta vazia
							printf("Cadeia nao aceita\n");
							return 0;
						//}//else{ //Caso a pilha nao esteja
						//	imprimirPilha(terminais);
						//	aux = atoi(ANASIN[buscaNoTopo(terminais)][4])-1; //Aux recebe o sucessor do no que sera desempilhado
						//	printf("Linha = %d\n",aux);
						//	strcpy(p,pop(terminais)); //Desempilha o terminal
					//		printf("Desempilha o terminal %s\n",p);
						//}
					}
				}

			}
		}
		numeroLinha = aux;




	}while(1);

	return 1;


}
