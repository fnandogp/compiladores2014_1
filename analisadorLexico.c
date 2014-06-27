/*
 * analisadorLexico.c
 *
 *  Created on: 24/04/2014
 *      Author: thiago
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automato.h"
#include "hash.h"
#include "tadLista.h"


int consultaTabVar(char* caracter){

	char* pch;
	FILE* tabVar = fopen("tabvar","r");
	char buffer[100];
	while(fgets(buffer,100,tabVar)){
		pch = strtok(buffer, "\n");
		if(strcmp(pch,caracter)==0){
			fclose(tabVar);
			return 1;
		}
	}
	return 0;

}



void acoesSemanticas(int tipoAcao, char* buffer, int posicao, char* tipoSimbolo, char simbolo, Hash tab, Hash tabProc, FILE* arquivoEntrada, Lista* variaveis){	
	switch(tipoAcao){
	case 1:
		buffer[posicao] = simbolo;
		break;
	case 2:
		buffer[posicao] = simbolo;
		break;
	case 3:
		buffer[posicao] = '\0';
		//printf("Buffer = %s, Result = %d\n",buffer, consultaSR(tab,buffer));
		if(consultaSR(tab, buffer)){
			strcpy(tipoSimbolo,"PALAVRA RESERVADA");
		}
		else if(lista_consultar(variaveis, buffer)!=NULL){
			strcpy(tipoSimbolo,"VAIDEN");
		}
		else if(consultaSR(tabProc, buffer)){
			strcpy(tipoSimbolo, "PRIDEN");
		}
		else{
			strcpy(tipoSimbolo,"IDENTIFICADOR");
		}
		break;
	case 4:
		buffer[posicao] = simbolo;
		break;
	case 5:
		buffer[posicao] = simbolo;
		break;
	case 6:
		strcpy(tipoSimbolo,"NUMERO INTEIRO");
		buffer[posicao] = '\0';
		break;
	case 7:
		buffer[posicao] = simbolo;
		buffer[posicao+1] = '\0';
		if(consultaSR(tab, buffer)){
			strcpy(tipoSimbolo,"SIMBOLO RESERVADO");
		}else{
			buffer[posicao] = '\0';
			//fseek(arquivoEntrada,-1,SEEK_CUR);
			//printf("%s\n",buffer);
			if(consultaSR(tab,buffer)){
				strcpy(tipoSimbolo,"SIMBOLO RESERVADO");
			}else{
				strcpy(tipoSimbolo, "SIMBOLO ESPECIAL");
			}		
		}

		//Verifica se esta na tabela de simbolos reservados
		break;
	case 8:
		buffer[posicao] = '\0';
		//Verifica se esta na tabela de simbolos reservados
		if(consultaSR(tab, buffer)){
			strcpy(tipoSimbolo,"SIMBOLO RESERVADO");
		}else{
			strcpy(tipoSimbolo,"SIMBOLO ESPECIAL");
		}
		break;
	case 10:
		buffer[posicao] = '\0';
		strcpy(tipoSimbolo,"caracter");
		break;
	case 11:
		buffer[posicao] = '\0';
		strcpy(tipoSimbolo,"NUMERO REAL");
		break;
	default:
		break;
	}
}

int executaAnalisador(FILE* arquivoEntrada, int** automato, int linhas, int colunas, Hash tab, int* posicaoArquivo, char** vetor, Hash tabProc, Lista* variaveis, int* linha){

	fseek(arquivoEntrada,0,*posicaoArquivo);
	char simbolo;
	char buffer[50];
	char tipoSimbolo[50];
	int tipoLido;
	int estadoAtual = 0;
	int proximaTransicao;
	int transicaoAtual = 0;
	int posicao = 0;
	int verificaSimboloTamanho2 = 0;
	
	while((simbolo=fgetc(arquivoEntrada))!=EOF){

		
		tipoLido = verificaSimboloLido(simbolo); //Verifica o tipo do simbolo lido
		proximaTransicao = verificaProximaTransicao(automato, estadoAtual,tipoLido, linhas, colunas);//Busca a proxima transição
		transicaoAtual = verificaTransicaoAtual(automato, estadoAtual, tipoLido, linhas, colunas);//Verifica qual eh a transicao atual
		estadoAtual = verificaProximoEstado(automato, estadoAtual, tipoLido, linhas, colunas); //Atualiza o estado atual
		//printf("Estado = %d, Tipo Lido = %d, Prox Trans = %d, Trans Atual = %d\n",estadoAtual, tipoLido, proximaTransicao, transicaoAtual);
		if(estadoAtual==8){
			if(strlen(buffer)==1){
				estadoAtual=7;
				proximaTransicao=-1;
			}else if(strlen(buffer)==2){
				
				
			}
		printf("Simbolo = %c, buffer = %s\n",simbolo, buffer);
		}
		if(estadoAtual==7 && proximaTransicao==-1){
			acoesSemanticas(automato[transicaoAtual][5],buffer,posicao,tipoSimbolo,simbolo, tab, tabProc, arquivoEntrada, variaveis); //Aplica as acoes semanticas
			printf("Fim!\n");
			if(strcmp(tipoSimbolo, "PALAVRA RESERVADA")==0) {
				strcpy(vetor[0], "C2");
				strcpy(vetor[1], buffer);
				strcpy(vetor[2], buffer);
			}
			else if(strcmp(tipoSimbolo, "IDENTIFICADOR")==0) {
				strcpy(vetor[0], "C1");
				strcpy(vetor[1], "IDEN");
				strcpy(vetor[2], buffer);
			}
			else if(strcmp(tipoSimbolo, "VAIDEN")==0) {
				strcpy(vetor[0], "C1");
				strcpy(vetor[1], "VAIDEN");
				strcpy(vetor[2], buffer);
			}
			else if(strcmp(tipoSimbolo, "SIMBOLO RESERVADO")==0) {
				if(strlen(buffer)==2){
					verificaSimboloTamanho2 = 1;
				}
				strcpy(vetor[0], "C4");
				strcpy(vetor[1], buffer);
				strcpy(vetor[2], buffer);
			}
			else if(strcmp(tipoSimbolo, "NUMERO INTEIRO")==0) {
				strcpy(vetor[0], "C3");
				strcpy(vetor[1], "NUMB");
				strcpy(vetor[2], buffer);
			}
			else if(strcmp(tipoSimbolo, "caracter")==0){
				verificaSimboloTamanho2 = 1;
				strcpy(vetor[0], "C5");
				strcpy(vetor[1], "caracter");
				strcpy(vetor[2], buffer);
			}
			else if(strcmp(tipoSimbolo, "NUMERO REAL")==0) {
				strcpy(vetor[0], "C3");
				strcpy(vetor[1], "NUMB");
				strcpy(vetor[2], buffer);
			}
			else if(strcmp(tipoSimbolo, "PRIDEN")==0) {
				strcpy(vetor[0], "C1");
				strcpy(vetor[1], "PRIDEN");
				strcpy(vetor[2], buffer);
			}

			if(verificaSimboloTamanho2!=1){
			
				fseek(arquivoEntrada,-1,SEEK_CUR);
			}
			//printf("%s - ",buffer);
			//printf("%s\n",tipoSimbolo);
			
			estadoAtual = 0;
			posicao = 0;

			*posicaoArquivo = SEEK_CUR;

			return 1;


		}else{
			if(estadoAtual!=-1 && estadoAtual!=0){
				//printf("Pos = %c\n",simbolo);
				acoesSemanticas(automato[transicaoAtual][5],buffer,posicao,tipoSimbolo,simbolo, tab, tabProc, arquivoEntrada, variaveis); //Aplica as acoes semanticas
				posicao++;
				//printf("%c -> Estado Atual = %d\n", simbolo, estadoAtual);
			}

		}
	}
	return 0;


}
