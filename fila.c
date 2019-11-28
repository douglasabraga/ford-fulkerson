
#include "fila.h"

void inicializaFila(TFila *F){
	F->inicio = NULL;
	F->fim = NULL;
}

int filaVazia(TFila *F){
	if(F->inicio == NULL) return 1;
	return 0;
}

void insere(TFila *F, int vertice){
	TVertice *novo = (TVertice *) malloc (sizeof(TVertice));
	    
    novo->prox = NULL;
    //novo->ante = NULL;
    
    novo->vertice = vertice;
    
    if (F->inicio == NULL){
    	F->inicio = novo;
    	F->fim = novo;
    } else {
    	F->fim->prox= novo;
    	//novo->ante = F->fim;
    	F->fim = novo;
	}
}

void remover(TFila *F){
	if(F->inicio == NULL) return;
	
	if(F->inicio == F->fim){
		free(F->inicio);
		F->inicio = NULL;
		F->fim = NULL;
		
	}else{
		TVertice *aux = F->inicio;
		F->inicio = F->inicio->prox;
		//F->inicio->ante = NULL;
		free(aux);
	}
}

/********************** LISTA *******************************/
void inicializaLista(TLista *L){
	L->inicio = NULL;
	L->fim = NULL;
}


void insereCaminhao(TLista *L, char placa[], char nome[], int capacidade){
	TCaminhao *novo = (TCaminhao *) malloc (sizeof(TCaminhao));
	    
    novo->prox = NULL;
    novo->ante = NULL;
    
    strcpy(novo->placa,placa);
    strcpy(novo->nome,nome);
    novo->capacidade = capacidade;
    
    if (L->inicio == NULL){
    	L->inicio = novo;
    	L->fim = novo;
    } else {
    	L->fim->prox= novo;
    	novo->ante = L->fim;
    	L->fim = novo;
	}
}
