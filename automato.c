/*
 * analisadorLexico.c
 *
 *  Created on: 24/04/2014
 *      Author: thiago
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int** inicializaMatrizAutomato(int **matrix, int linhas, int colunas){
	int i,j;
	matrix = (int **)malloc(linhas*sizeof(int *));
	for(i=0;i<linhas;i++){
		matrix[i] = (int *)malloc(colunas*sizeof(int));
	}

	for(i=0;i<linhas;i++){
		for(j=0;j<colunas;j++){
			matrix[i][j] = -1;
		}
	}
	return matrix;
}

void carregaAutomato(int **matrix, int linhas, int colunas, FILE* automato){

	char buffer[50];
	char* pch;
	int nLinha=0;
	int nColuna=0;
	while(fgets(buffer,1000,automato)!=NULL){
		pch = strtok(buffer, " \n");
		while(pch!=NULL){
			matrix[nLinha][nColuna] = atoi(pch);
			nColuna++;
			pch = strtok(NULL," \n");

		}
		nColuna = 0;
		nLinha++;
	}

}

int verificaEstadoFinal(int **matrix, int estadoAtual, int linhas, int colunas){
	int j;
	for(j=0;j<colunas;j++){
		if(matrix[0][j]!=-1){
			if(matrix[0][j]==estadoAtual){
				return 1;
			}
		}
	}
	return 0;
}

int verificaProximaTransicao(int **matrix, int estadoAtual, int tipoLido, int linhas, int colunas){

	int i,j;
	for(i=1;i<linhas;i++){
		if(matrix[i][1]==estadoAtual){
			if(matrix[i][2]==tipoLido){
				return matrix[i][4];
			}
		}
	}
	return -1;

}

int verificaTransicaoAtual(int **matrix, int estadoAtual, int tipoLido, int linhas, int colunas){
	int i, j;
	for(i=1;i<linhas;i++){
		if(matrix[i][1]==estadoAtual){
			if(matrix[i][2]==tipoLido){
				return matrix[i][0];
			}
		}
	}

	return -1;
}

int verificaProximoEstado(int **matrix, int estadoAtual, int tipoLido, int linhas, int colunas){
	int i,j;
	for(i=1;i<linhas;i++){
		if(matrix[i][1]==estadoAtual){
			if(matrix[i][2]==tipoLido){
				return matrix[i][3];
			}
		}
	}
	return -1;
}


int ehLetra(char c){
	if((c>=65 && c<=90) || (c>=97 && c<=122)){
		return 1;
	}
	return 0;
}

int ehNumero(char c){
	if(c>=48 && c<=57){
		return 1;
	}
	return 0;
}

int ehSimbolo(char c){
	if(!ehLetra(c) && !ehNumero(c) && c!=32 && c!='\n' && c!='/'){
		return 1;
	}
	return 0;
}


int verificaSimboloLido(char c){
	if(ehLetra(c)){ //Simbolo lido eh letra
		return 1;
	}
	if(ehNumero(c)){ //Simbolo lido eh numero
		return 2;
	}
	if(ehSimbolo(c)){ //Simbolo lido eh Caracter Especial
		return 3;
	}
	if(c=='/'){ //Simbolo lido eh '/'
		return 4;
	}

	return 0;
}
