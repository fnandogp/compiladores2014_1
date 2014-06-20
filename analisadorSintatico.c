/*
 * analisadorSintatico.c
 *
 *  Created on: 30/04/2014
 *      Author: thiago
 */

#include <stdio.h>
#include <stdlib.h>
#include "tadPilha.h"
#include "tadLista.h"
#include "hash.h"
#include <string.h>

Lista* variaveis = NULL;

void aplicaAcoesSemanticas(FILE* arquivo, int acao, char** info, char* nomeArquivo, int* flag){

	switch(acao){
		case 1: //Cria o arquivo intermediario
			strcpy(nomeArquivo, info[2]);
			arquivo = fopen(info[2], "w");
			fprintf(arquivo, "#include <stdio.h>\n");
			fprintf(arquivo, "#include <stdlib.h>\n");
			fprintf(arquivo, "#include <string.h>\n\n\n");
			fprintf(arquivo, "int main(void){\n\n");
			fclose(arquivo);
			break;
		
		case 2: //Se
			*flag = 1;
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo,"	if(");
			fclose(arquivo);
			break;
		case 3: //VAIDEN dentro do SE
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "%s ", info[2]);
			fclose(arquivo);
			break;
		case 4: //NUMB dentro do SE
			arquivo = fopen(nomeArquivo, "a");
			if(*flag == 1){
				fprintf(arquivo, "%s ", info[2]);
			}else{
				fprintf(arquivo, "%s;\n", info[2]);
			}
			fclose(arquivo);
			break;
		case 5: // ( dentro do SE
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "(");
			fclose(arquivo);
			break;
		case 6: // ) dentro do SE
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, ")", info[2]);
			fclose(arquivo);
			break;
		case 7: // not dentro do SE
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "!", info[2]);
			fclose(arquivo);
			break;
		case 8: // > dentro do SE
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, ">");
			fclose(arquivo);
			break;
		case 9: // = dentro do SE
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "=");
			fclose(arquivo);
			break;
		case 10: // < dentro do SE
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "<");
			fclose(arquivo);
			break;
		case 11: // <> dentro do SE
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "<>");
			fclose(arquivo);
			break;
		case 12: // >= dentro do SE
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, ">=");
			fclose(arquivo);
			break;
		case 13: // <= dentro do SE
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "<=");
			fclose(arquivo);
			break;
		case 14: // entao
			*flag = 0;
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "){\n");
			fclose(arquivo);
			break;
			
		case 15: //VAIDEN statm
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "	%s ", info[2]);
			fclose(arquivo);
			break;
		case 16: // := statm
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "=");
			fclose(arquivo);
			break;
		case 17: //senao
			*flag = 2;
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "	}else{\n");
			fclose(arquivo);
			break;
		case 18: //lambda statm
			if(*flag>0){
				arquivo = fopen(nomeArquivo, "a");
				fprintf(arquivo, "}\n");
				fclose(arquivo);			
			}
			break;	
		case 19: // Enquanto
			*flag = 1;
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "	while(");
			fclose(arquivo);
			break;
		case 20: //faca
			*flag = 0;
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "){\n");
			fclose(arquivo);
			break;
		case 21: //sinal de +
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "+");
			fclose(arquivo);
			break;
		case 22: //sinal de -
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "-");
			fclose(arquivo);
			break;	
		case 23: //sinal de *
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "*");
			fclose(arquivo);
			break;	
		case 24: //sinal de /
			arquivo = fopen(nomeArquivo, "a");
			fprintf(arquivo, "/");
			fclose(arquivo);
			break;		
		case 60: //Cria variavel
			printf("\n\n Veremos \n\n %s\n", info[2]);
			variaveis = lista_inserir(variaveis,info[2]);
			break;
		case 69: //Escreve as variaveis no arquivo
			arquivo = fopen(nomeArquivo,"a");	
			imprimeVariaveis(variaveis, "int", arquivo);
			fclose(arquivo);
			break;
			
	}

}



int verificaLinhaTerminal(char*** TABNT, int linhas, char* naoTerminal){

	int i;
	for(i=0;i<linhas;i++){
		if(strcmp(TABNT[i][1],naoTerminal)==0){
			return atoi(TABNT[i][2])-1;
		}
	}
	return -1;
}


int analisadorSintatico(FILE* codigo, char** TABGRAFO, char*** TABT, char*** TABNT, char*** ANASIN, int linhasTabNT, int** automato, Hash tab, FILE* tabVar, Hash tabProc){

	char nomeArquivo[20];

	int* flag1 = (int *)malloc(sizeof(int));;
	*flag1 = 0;
	FILE* codigoIntermediario;
	//Inicializa as Pilhas
	Pilha* cadeia = inicializarPilha(cadeia);
	Pilha* naoTerminais = inicializarPilha(naoTerminais);
	push(naoTerminais,"progrm",10,0);

	char* cadCaracteres = (char *)malloc(50*sizeof(char));
	char* cadTerminais = (char *)malloc(50*sizeof(char));
	char* p = (char *)malloc(50*sizeof(char));

	//Isso sera alterado quando comecarmos a ler strings ao inves de caracteres
	char* caracter = (char *)malloc(50*sizeof(char));
	int numeroLinha = 0;
	int aux=0;
	int aux2=0;
	int flag = 0;
	char** vetor = (char **)malloc(4*sizeof(char *));
	int i;
	for(i=0;i<4;i++){
		vetor[i] = (char *)malloc(20*sizeof(char));
	}
	
	int* posicaoArquivo = (int *)malloc(sizeof(int));
	*posicaoArquivo = 0;
	while(executaAnalisador(codigo, automato, 34, 7, tab, posicaoArquivo, vetor, tabProc, variaveis)) {
		
		strcpy(caracter, vetor[1]);
		printf("\n\nLinha %d | Lexema: \"%s\"\n", aux+1, caracter);

		if(aux==-1){
			printf("\n\n!! Cadeia nao aceita !!\n\n\n");
			return 0;
		}
		while(1){
			// para aux == -2 
			while(aux==-2 && !vaziaNTerminais(naoTerminais)){
				//imprimirPilha(naoTerminais);
				aux = atoi(ANASIN[buscaNoTopo(naoTerminais)][4])-1;
				printf("Voltando para linha %d.\n", aux+1);

				if(aux==-1) aux = -2;
				if(aux!=-2){
					while(aux!=-1 && strcmp(ANASIN[aux][1],caracter)!=0){ //Verifica os nos alternativos para procurar o caracter
						aux = atoi(ANASIN[aux][3])-1;
						printf("Voltando novamente, para linha %d.\n", aux+1);

						// trick para tratar alternativo igual a -1
						if(aux==-2) aux = -1;
					}
					if(aux==-1) aux = -2;
				}
				
				// printf("%s\n",caracter);
				// printf("O Nao Terminal abaixo eh pai de: ");
				// imprimePilhaPosicaoAteTopo(cadeia, buscaPosicaoReconhecida(naoTerminais));
				desempilhaDaPosicaoAteTopo(cadeia,buscaPosicaoReconhecida(naoTerminais)); //Adicionar uma especie de fila aqui
				strcpy(p, pop(naoTerminais));
				push(cadeia,p,0,0);
				// printf("Desempilha o nao terminal %s\n",p);
			}
			if(vaziaNTerminais(naoTerminais) && aux==-2){
				printf("\n\n!! Cadeia nao aceita !!\n\n\n");
				// printf("Linha %d - Lexema \"%s\" encontrado.\n", numeroLinha, caracter);
				return 0;
			}
			// Para um Terminal encontrado
			if(strcmp(ANASIN[aux][0],"T")==0){
				// para caracter lido reconhecido
				if(strcmp(ANASIN[aux][1],caracter)==0){
					strcpy(cadCaracteres,ANASIN[aux][1]);
					push(cadeia,cadCaracteres,0,0); //Insere na pilha o caracter reconhecido
					aplicaAcoesSemanticas(codigoIntermediario, atoi(ANASIN[aux][5]),vetor, nomeArquivo, flag1);
					printf("TO AQUI %s\n",ANASIN[aux][5]);
					//imprimirPilha(cadeia);
					aux = atoi(ANASIN[aux][4])-1; //Aux recebe a linha correspondente ao sucessor do no encontrado
					printf("Lexema aceito. O sucessor é a linha: %d\n", aux+1);
					//printf("%s - %d\n", cadCaracteres, atoi(ANASIN[aux][5]));
					
					if(aux==-1) {
						aux=-2;
						printf("Linha sucessora é 0, ou seja, Chegamos ao fim dessa cadeia não terminal.\n");
					}
					break;
				}
				// para caracter não reconhecido
				else {
					aux = atoi(ANASIN[aux][3])-1; //Aux recebe a posicao do no alternativo
					
					//Caso nao haja mais nenhum no alternativo
					if(aux==-2){
						printf("\n\n!! Cadeia nao aceita !!\n\n\n");
						return 0;
					}
					printf("Não reconhecido. Alternativo na linha: %d\n", aux+1);
				}
			}
			// para um não terminal encontrado
			else if(strcmp(ANASIN[aux][0],"N")==0){ //Encontra um Nao Terminal
				strcpy(cadTerminais,ANASIN[aux][1]);
				aplicaAcoesSemanticas(codigoIntermediario, atoi(ANASIN[aux][5]),vetor, nomeArquivo, flag1);
				push(naoTerminais,cadTerminais,atoi(ANASIN[aux][2])-1,topo(cadeia)); //Empilha o nao terminal na pilha de nao naoTerminais
				
				printf("Não terminal encontrado: \"%s\". Devemos empilha-lo.\n",cadTerminais);
				printf("Ao finalizar esse não terminal devemos voltar na linha: %d. ", atoi(ANASIN[aux][4]));

				aux = verificaLinhaTerminal(TABNT,linhasTabNT,cadTerminais); //Aux vai para a linha correspondente ao grafo do nao terminal
				printf("Vai para a linha: %d\n", aux+1);
				// imprimirPilha(naoTerminais);
			}
		}
		numeroLinha = aux;
		strcpy(vetor[0], "");
		strcpy(vetor[1], "");
		strcpy(vetor[2], "");



	}

	while(!vazia(naoTerminais)){
		// printf("O Nao Terminal Abaixo é pai de: ");
		// imprimePilhaPosicaoAteTopo(cadeia, buscaPosicaoReconhecida(naoTerminais));
		desempilhaDaPosicaoAteTopo(cadeia,buscaPosicaoReconhecida(naoTerminais));
		strcpy(p,pop(naoTerminais));
		// printf("Desempilhando o %s\n",p);
		push(cadeia,p,0,0);
	}

	printf("\n\n!! Cadeia reconhecida !!\n\n\n");

	return 1;


}
