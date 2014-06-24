#include <stdio.h>
#include <stdlib.h>
#define TAM 31

struct celula{
	char simbolo[50];
	char* tipo;
	struct celula* prox;
};

typedef struct celula Celula;
typedef Celula* Hash[TAM];


int iniciaTSR(Hash tab, FILE* arqSR);
int geraChave(int num);
int representacaoInteira(char* simbolo);
void inicializaHash(Hash tab);
void insereS(Hash tabS, char* item);
int consultaSR(Hash tab, char* info);
void imprimeHash(Hash tab);
void insereTipo(Celula* item, char* simbolo);
