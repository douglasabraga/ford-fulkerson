#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 
//#include <limits.h> 
#include <string.h> 

typedef struct tipoVertice{
	int vertice;
	struct tipoVertice *prox /**ante*/;
}TVertice;

typedef struct tipoFila{
	TVertice *inicio;
	TVertice *fim;
}TFila;

void inicializaFila(TFila *F);
int filaVazia(TFila *F);
void insere(TFila *F, int vertice);
void remover(TFila *F);
