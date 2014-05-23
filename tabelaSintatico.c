/*
 * tabelaSintatico.c
 *
 *  Created on: 30/04/2014
 *      Author: thiago
 */

#include "tabelaSintatico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* verificaTerminal(int valor){
	switch(valor){
	case 1:
		return "T";
		break;
	case 0:
		return "N";
		break;
	default:
		return NULL;
		break;
	}
}

char** inicializaTABGRAFO(char** matrix, int linhas, int colunas){
	int i,j;
	matrix = (char **)malloc(linhas*sizeof(char *));
	for(i=0;i<linhas;i++){
		matrix[i] = (char *)malloc(colunas*sizeof(char));
	}

	for(i=0;i<linhas;i++){
		for(j=0;j<colunas;j++){
			matrix[i][j] = 0;
		}
	}
	return matrix;
}

void carregaTABGRAFO(char **matrix, int linhas, int colunas, FILE* tabgrafo){
	char buffer[100];
	char* pch;
	int nLinha=0;
	int nColuna=0;
	while(fgets(buffer,100,tabgrafo)!=NULL){
		pch = strtok(buffer, "	\n");
		while(pch!=NULL && nColuna<6){
			matrix[nLinha][nColuna] = atoi(pch);
			nColuna++;
			pch = strtok(NULL,"	\n");

		}
		nColuna = 0;
		nLinha++;
	}
}

char*** inicializaTABT(char*** matrix, int linhas, int colunas){
	int i,j;
	matrix = (char ***)malloc(linhas*sizeof(char **));
	for(i=0;i<linhas;i++){
		matrix[i] = (char **)malloc(colunas*sizeof(char *));
		for(j=0;j<colunas;j++){
			matrix[i][j] = (char *)malloc(50*sizeof(char));
		}
	}

//	for(i=0;i<linhas;i++){
	//	for(j=0;j<colunas;j++){
		//	matrix[i][j] = '\0';
		//}
	//}
	return matrix;

}

void carregaTABT(char*** matrix, int linhas, int colunas, FILE* tabt){
	char buffer[50];
	char* pch;
	int nLinha=0;
	int nColuna=0;
	while(fgets(buffer,50,tabt)!=NULL){
		pch = strtok(buffer, "	\n");
		while(pch!=NULL){
		//	printf("%c\n",pch[0]);
			int t = strlen(pch);
			strcpy(matrix[nLinha][nColuna],pch);
			//printf("%s ",matrix[nLinha][nColuna]);
			nColuna++;
			pch = strtok(NULL,"	\n");

		}
		//printf("\n");
		nColuna = 0;
		nLinha++;
	}
}

char*** inicializaTABNT(char*** matrix, int linhas, int colunas){
	int i,j;
	matrix = (char ***)malloc(linhas*sizeof(char **));
	for(i=0;i<linhas;i++){
		matrix[i] = (char **)malloc(colunas*sizeof(char *));
		for(j=0;j<colunas;j++){
			matrix[i][j] = (char *)malloc(50*sizeof(char));
		}
	}

/*	for(i=0;i<linhas;i++){
		for(j=0;j<colunas;j++){
			matrix[i][j] = '\0';
		}
	}
	*/
	return matrix;

}

void carregaTABNT(char*** matrix, int linhas, int colunas, FILE* tabnt){
	char buffer[50];
	char* pch;
	int nLinha=0;
	int nColuna=0;
	while(fgets(buffer,50,tabnt)!=NULL){
		pch = strtok(buffer, "	\n");
		while(pch!=NULL){
		//	printf("%c\n",pch[0]);
			strcpy(matrix[nLinha][nColuna],pch);
			//matrix[nLinha][nColuna] = pch;
			//printf("%s ",matrix[nLinha][nColuna]);
			nColuna++;
			pch = strtok(NULL,"	\n");

		}
		//printf("\n");
		nColuna = 0;
		nLinha++;
	}
}

char*** inicializaANASIN(char*** matrix, int linhas, int colunas){
	int i,j;
	matrix = (char ***)malloc(linhas*sizeof(char **));
	for(i=0;i<linhas;i++){
		matrix[i] = (char **)malloc(colunas*sizeof(char *));
		for(j=0;j<colunas;j++){
			matrix[i][j] = (char *)malloc(20*sizeof(char));
		}
	}

//	for(i=0;i<linhas;i++){
//		for(j=0;j<colunas;j++){
//			matrix[i][j] = '\0';
//		}
//	}
	return matrix;

}


//Monta a tabela final do analisador sintatico para ser usada futuramente
void carregaAnaSin(char*** TabAnaSin, char** TABGRAFO, int linhasG, int colunasG, char*** TABT, int linhasT, int colunasT, char*** TABNT, int linhasNT, int colunasNT){
	int linha,coluna;
	int auxTabT;
	int auxTabNT;
	char buf[10];
	for(linha=0;linha<linhasG;linha++){
		for(coluna=0;coluna<colunasG;coluna++){

			if(coluna==0){

				strcpy(TabAnaSin[linha][coluna],verificaTerminal(TABGRAFO[linha][1]));
				printf("%s ", TabAnaSin[linha][coluna]);
			}
			if(coluna==1){
				if(strcmp(TabAnaSin[linha][0],"T")==0){
					strcpy(TabAnaSin[linha][coluna],TABT[TABGRAFO[linha][2]-1][1]);
					printf("%s ", TabAnaSin[linha][coluna]);
				}else{
					strcpy(TabAnaSin[linha][coluna],TABNT[TABGRAFO[linha][2]-1][1]);
					printf("%s ", TabAnaSin[linha][coluna]);

				}
			}
			if(coluna==2){

				sprintf(buf,"%i",TABGRAFO[linha][0]);
				strcpy(TabAnaSin[linha][coluna],buf);
				printf("%s ", TabAnaSin[linha][coluna]);
			}
			if(coluna==3){
				sprintf(buf,"%i",TABGRAFO[linha][3]);
				strcpy(TabAnaSin[linha][coluna],buf);
				printf("%s ", TabAnaSin[linha][coluna]);
			}

			if(coluna==4){
				sprintf(buf,"%i",TABGRAFO[linha][4]);
				strcpy(TabAnaSin[linha][coluna],buf);
				printf("%s ", TabAnaSin[linha][coluna]);
			}

			if(coluna==5){
				sprintf(buf,"%i",TABGRAFO[linha][5]);
				strcpy(TabAnaSin[linha][coluna],buf);
				printf("%s ", TabAnaSin[linha][coluna]);
			}
		}
		printf("\n");

	}

}


