#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista Lista;

Lista* lista_contruir(void);
void lista_imprimir(Lista* l);
int lista_vazia(Lista* l);
Lista* lista_inserir(Lista* l, char palavra[]);
Lista* lista_consultar(Lista* l, char palavra[]);
