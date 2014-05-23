/*
 * main.c
 *
 *  Created on: 24/04/2014
 *      Author: thiago
 */

#include <stdio.h>
#include <stdlib.h>
#include "automato.h"
#include "analisadorLexico.h"
#include "tabelaSintatico.h"
#include "tadPilha.h"
#include "analisadorSintatico.h"


int main (int argc, char *argv[]){

	if(argc != 2) {
		printf("Insira o nome do arquivo a ser analisado.\n");
		printf("Por exemplo: ./trab3 <codigo>\n");
		printf("Onde código é o nome do arquivo.\n");
	}
	FILE* codigo = fopen(argv[1],"r");
	if(!codigo) {
		printf("\nArquivo não encontrado.\n\n");
		return 0;
	}
	
	

	char** TABGRAFO = inicializaTABGRAFO(TABGRAFO,78,6);
	char*** TABT = inicializaTABT(TABT, 50,2);
	char*** TABNT = inicializaTABNT(TABNT, 8, 3);
	char*** ANASIN = inicializaANASIN(ANASIN, 78, 6);

	FILE* tabelaGrafo = fopen("tabgrafo","r");
	FILE* tabelaTerminais = fopen("tabt","r");
	FILE* tabelaNaoTerminais = fopen("tabnt","r");
	FILE* fp = fopen("automato","r");
	FILE* tabSimbolos = fopen("simbolos","r");
	FILE* tabVar = fopen("tabvar","r");

	Hash tab;
	int result = iniciaTSR(tab,tabSimbolos);
	// imprimeHash(tab);

	int** matrix = inicializaMatrizAutomato(matrix,22,7);
	carregaAutomato(matrix,22,7,fp);


	carregaTABGRAFO(TABGRAFO,78,6,tabelaGrafo);
	carregaTABT(TABT,50,2,tabelaTerminais);
	carregaTABNT(TABNT,8,3,tabelaNaoTerminais);
	carregaAnaSin(ANASIN,TABGRAFO,78,6,TABT,50,2,TABNT,8,3);

	printf("\n");

	analisadorSintatico(codigo,TABGRAFO,TABT,TABNT,ANASIN,8, matrix, tab, tabVar);

	fclose(tabelaGrafo);
	fclose(tabelaNaoTerminais);
	fclose(tabelaTerminais);

	return 1;
}

