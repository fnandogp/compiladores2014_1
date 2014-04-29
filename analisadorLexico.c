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

void acoesSemanticas(int tipoAcao, char* buffer, int posicao, char* tipoSimbolo, char simbolo, Hash tab){
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
		}else{
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
			strcpy(tipoSimbolo,"SIMBOLO ESPECIAL");
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
	default:
		break;
	}
}

void executaAnalisador(FILE* arquivoEntrada, int** automato, int linhas, int colunas, Hash tab){

	char simbolo;
	char buffer[50];
	char tipoSimbolo[50];
	int tipoLido;
	int estadoAtual = 0;
	int proximaTransicao;
	int transicaoAtual = 0;
	int posicao = 0;

	while((simbolo=fgetc(arquivoEntrada))!=EOF){
		tipoLido = verificaSimboloLido(simbolo); //Verifica o tipo do simbolo lido
		proximaTransicao = verificaProximaTransicao(automato, estadoAtual,tipoLido, linhas, colunas);//Busca a proxima transição
		transicaoAtual = verificaTransicaoAtual(automato, estadoAtual, tipoLido, linhas, colunas);//Verifica qual eh a transicao atual
		estadoAtual = verificaProximoEstado(automato, estadoAtual, tipoLido, linhas, colunas); //Atualiza o estado atual
		//printf("Estado = %d, Tipo Lido = %d, Prox Trans = %d, Trans Atual = %d\n",estadoAtual, tipoLido, proximaTransicao, transicaoAtual);
		if(estadoAtual==7 && proximaTransicao==-1){
			acoesSemanticas(automato[transicaoAtual][5],buffer,posicao,tipoSimbolo,simbolo, tab); //Aplica as acoes semanticas
			//printf("Fim!\n");
			printf("%s - ",buffer);
			printf("%s\n",tipoSimbolo);
			fseek(arquivoEntrada,-1,SEEK_CUR);
			estadoAtual = 0;
			posicao = 0;

		}else{
			if(estadoAtual!=-1 && estadoAtual!=0){
				//printf("Pos = %c\n",simbolo);
				acoesSemanticas(automato[transicaoAtual][5],buffer,posicao,tipoSimbolo,simbolo, tab); //Aplica as acoes semanticas
				posicao++;
				//printf("%c -> Estado Atual = %d\n", simbolo, estadoAtual);
			}

		}
	}


}
