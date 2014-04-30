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


int main (int argc, char *argv[]){

	/*
	if(argc != 2) {
		printf("Insira o nome do arquivo a ser analisado.\nPor exemplo: ./trab2 codigo\nOnde código é o nome do arquivo.");
	}
	FILE* codigo = fopen(argv[1],"r");
	if(!codigo) {
		printf("\nArquivo não encontrado.\n\n");
		return 0;
	}

	FILE* fp = fopen("automato","r");
	FILE* tabSimbolos = fopen("simbolos","r");

	Hash tab;
	int result = iniciaTSR(tab,tabSimbolos);
	// imprimeHash(tab);

	int** matrix = inicializaMatrizAutomato(matrix,22,7);
	carregaAutomato(matrix,22,7,fp);
	executaAnalisador(codigo, matrix, 22, 7, tab);


	fclose(fp);
	fclose(codigo);
	//fclose(tabSimbolos);
	//liberaMatrizAutomato(matrix,22,7);
	 *
	 */

	char** TABGRAFO = inicializaTABGRAFO(TABGRAFO,10,6);
	char*** TABT = inicializaTABT(TABT, 7,2);
	char*** TABNT = inicializaTABNT(TABNT, 2, 3);
	char*** ANASIN = inicializaANASIN(ANASIN, 10, 6);

	FILE* tabelaGrafo = fopen("tabgrafo","r");
	FILE* tabelaTerminais = fopen("tabt","r");
	FILE* tabelaNaoTerminais = fopen("tabnt","r");

	carregaTABGRAFO(TABGRAFO,10,6,tabelaGrafo);

	carregaTABT(TABT,7,2,tabelaTerminais);
	carregaTABNT(TABNT,2,3,tabelaNaoTerminais);
	carregaAnaSin(ANASIN,TABGRAFO,10,6,TABT,7,2,TABNT,2,3);

	fclose(tabelaGrafo);
	fclose(tabelaNaoTerminais);
	fclose(tabelaTerminais);

	return 1;
}

