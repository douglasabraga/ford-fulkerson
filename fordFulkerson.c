#include "fordFulkerson.h"

bool bfs(int **grafo, int s, int t, int parent[], TFila *fila) 
{ 
    // Create a visited array and mark all vertices as not visited 
    bool visited[V]; 
    int v;
    memset(visited, 0, sizeof(visited)); 

    // Create a queue, enqueue source vertex and mark source vertex 
    // as visited 
    //queue <int> q;
    inicializaFila(fila);
    //q.push(s);
    insere(fila, s);
    visited[s] = true; 
    parent[s] = -1; 
  
    // Standard BFS Loop 
    while (!filaVazia(fila)) 
    { 
        int u = fila->inicio->vertice; 
        //q.pop(); 
        remover(fila);
  		//printf("GARAIIIII");
        for ( v=0; v<V; v++) 
        { //printf("GARAIIIII");
            if (visited[v] == false && grafo[u][v] > 0) 
            {
                //q.push(v); 
                insere(fila, v);
                parent[v] = u; 
                visited[v] = true; 
            } 
        } 
    } 
  
    // If we reached sink in BFS starting from source, then return 
    // true, else false 
    return (visited[t] == true); 
} 
  
// Returns the maximum flow from s to t in the given graph 
int fordFulkerson(int **grafo, int s, int t, TFila *fila) 
{ 
    int u, v; 
  
    // Create a residual graph and fill the residual graph with 
    // given capacities in the original graph as residual capacities 
    // in residual graph 
    int **rGraph = alocarMatriz(V,V); // Residual graph where rGraph[i][j] indicates  
                     // residual capacity of edge from i to j (if there 
                     // is an edge. If rGraph[i][j] is 0, then there is not)   
    for (u = 0; u < V; u++) 
        for (v = 0; v < V; v++) 
             rGraph[u][v] = grafo[u][v]; 
  
    int parent[V];  // This array is filled by BFS and to store path 
  
    int max_flow = 0;  // There is no flow initially 
  
    // Augment the flow while tere is path from source to sink 
    while (bfs(rGraph, s, t, parent, fila)) 
    { 
        // Find minimum residual capacity of the edges along the 
        // path filled by BFS. Or we can say find the maximum flow 
        // through the path found. 
        int path_flow = INT_MAX; 
        for (v=t; v!=s; v=parent[v]) 
        { 
            u = parent[v]; 
            path_flow = __min(path_flow, rGraph[u][v]); 
        } 
  
        // update residual capacities of the edges and reverse edges 
        // along the path 
        for (v=t; v != s; v=parent[v]) 
        { 
            u = parent[v]; 
            rGraph[u][v] -= path_flow; 
            rGraph[v][u] += path_flow; 
        } 
  
        // Add path flow to overall flow 
        max_flow += path_flow; 
    } 
  
    // Return the overall flow 
    return max_flow; 
}

int** alocarMatriz(int linhas, int colunas){ //Recebe a quantidade de linhas e colunas como Parâmetro
	
	int i,j; //Variáveis Auxiliares
	
	int **m = (int**)malloc(linhas * sizeof(int*)); //Aloca um Vetor de Ponteiros
	
	for (i = 0; i < linhas; i++){ //Percorre as linhas do Vetor de Ponteiros
	   m[i] = (int*) malloc(colunas * sizeof(int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
	   for (j = 0; j < colunas; j++){ //Percorre o Vetor de Inteiros atual.
	        m[i][j] = 0; //Inicializa com 0.
	   }
	}
	
	return m; //Retorna o Ponteiro para a Matriz Alocada
}
