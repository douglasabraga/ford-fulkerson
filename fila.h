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

/************************* LISTA ***********************/
typedef struct tipoCaminhao{
	char placa[100];
	char nome[100];
	int capacidade;
	struct tipoCaminhao *prox, *ante;
}TCaminhao;

typedef struct tipoLista{
	TCliente *inicio;
	TCliente *fim;
}TLista;

void inicializaLista(TLista *L);

