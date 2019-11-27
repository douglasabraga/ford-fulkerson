
#include "fila.h"
//#define V 6



int V;

bool bfs(int **grafo, int s, int t, int parent[], TFila *fila);
int fordFulkerson(int **grafo, int s, int t, TFila *fila);
int** alocarMatriz(int linhas, int colunas);
