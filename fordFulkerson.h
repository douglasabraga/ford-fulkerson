
#include "fila.h"

int V;

bool bfs(int **grafo, int s, int t, int parent[], TFila *fila);
int fordFulkerson(TGrafo **grafo, int s, int t, TFila *fila, TLista *listaCaminhao, char **vetorNomes);
TGrafo** alocarMatriz(int linhas, int colunas);
int **alocarMatrizInt(int linhas, int colunas);
void alocarCaminhaoFluxo(TLista *listaCaminhao, int path_flow);
void imprimirCaminho(char **vetorNomes, int parent[], int j, int s, TGrafo **grafo);
void imprimirVeiculosNaoAlocados(TLista *listaCaminhoes);
