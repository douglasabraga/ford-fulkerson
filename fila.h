#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 

/*********************  MATRIZ **************************/

typedef struct TipoGrafo{
	int fluxo;
	int distancia;
}TGrafo;



/******************* FILA *************************/
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
	int alocado;
	struct tipoCaminhao *prox, *ante;
}TCaminhao;

typedef struct tipoLista{
	TCaminhao *inicio;
	TCaminhao *fim;
}TLista;

void inicializaLista(TLista *L);
void insereCaminhao(TLista *L, char placa[], char nome[], int capacidade);

