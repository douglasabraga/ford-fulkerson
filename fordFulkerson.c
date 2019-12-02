#include "fordFulkerson.h"
int cont = 0;
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
int fordFulkerson(TGrafo **grafo, int s, int t, TFila *fila, TLista *listaCaminhao, char **vetorNomes) 
{ 
    int u, v; 
  
    // Create a residual graph and fill the residual graph with 
    // given capacities in the original graph as residual capacities 
    // in residual graph 
    int **rGraph = alocarMatrizInt(V,V); // Residual graph where rGraph[i][j] indicates  
                     // residual capacity of edge from i to j (if there 
                     // is an edge. If rGraph[i][j] is 0, then there is not)   
    for (u = 0; u < V; u++) 
        for (v = 0; v < V; v++) 
             rGraph[u][v] = grafo[u][v].fluxo; 
  
    int parent[V];  // This array is filled by BFS and to store path 
  
    int max_flow = 0;  // There is no flow initially 

    // Augment the flow while tere is path from source to sink 
    printf("\n====================== ALOCACAO DE VEICULOS ====================== \n");
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

       	imprimirCaminho(vetorNomes, parent, t, s, grafo);
       	//printf("Distancia  %d", cont);
       	
       	printf(" Distancia: %d\n", cont);
        alocarCaminhaoFluxo(listaCaminhao, path_flow);
        
    }
    
    verificarCentroComCargaPendente(rGraph, vetorNomes);
  
    // Return the overall flow 
    return max_flow; 
}




void alocarCaminhaoFluxo(TLista *listaCaminhao, int path_flow){
	
	TCaminhao *atual = listaCaminhao->inicio;
	
	int capacidadeIdeal = INT_MAX;
	char placa[50];
	int aux = 0;
	while(atual != NULL){
		if(atual->capacidade >=path_flow && !atual->alocado){
			if(atual->capacidade <= capacidadeIdeal){
				capacidadeIdeal = atual->capacidade;
				strcpy(placa, atual->placa);
			}
		}
		atual = atual->prox;
	}
	
	atual = listaCaminhao->inicio;
	while(atual != NULL){
		if(strcmp(atual->placa, placa) == 0){
			aux = 1;
			atual->alocado = 1;
			printf("\nplaca: %s", atual->placa);
			printf("\nNome: %s", atual->nome);
			printf("\ncapacidade: %d\n", atual->capacidade);
			//atual = NULL;
		}
		atual = atual->prox;
	}
	
	if(!aux) printf("Não existe veículos disponiveis suficientes");
	
	
}


void imprimirCaminho(char **vetorNomes, int parent[], int j, int s, TGrafo **grafo) { 
	// Caso base: se j é fonte
	
	if(s >= 0){
		printf("\n===\n");
		printf("Caminho %s, ", vetorNomes[s]);
		cont = 0;
	}

    if (parent[j] == - 1) 
        return; 
  
    imprimirCaminho(vetorNomes, parent, parent[j], -1, grafo);
  	//printf("%d", grafo[parent[j]][j].distancia);
    printf("%s, ", vetorNomes[j]);
    cont+= grafo[parent[j]][j].distancia;
    
}


void imprimirVeiculosNaoAlocados(TLista *listaCaminhoes){
	TCaminhao *atual = listaCaminhoes->inicio;
	int aux = 0;
	while(atual != NULL){
		if(!atual->alocado){
			if(!aux) 	printf("\n\n========================== VEICULOS NAO ALOCADOS =======================\n");
			//printf("\n===================");
			printf("\n%d)", aux+1);
			printf("\nPlaca: %s", atual->placa);
			printf("\nNome: %s", atual->nome);
			printf("\nCapacidade: %d", atual->capacidade);
			aux++;
		}
		
		atual = atual->prox;
	}
}


void verificarCentroComCargaPendente(int **grafo, char **vetorNomes){
	int j, i;
	printf("\n\n========================== CARGAS PENDENTES =======================\n");
	for(i = 0; i < V; i++){
		for(j = 0; j < V; j++){
			if(grafo[i][j] > 0) printf("%s -> %s: %d\n", vetorNomes[i], vetorNomes[j], grafo[i][j]);
		}
		
	}
		//printf("\n\n=============================================================\n");

}


TGrafo** alocarMatriz(int linhas, int colunas){ //Recebe a quantidade de linhas e colunas como Parâmetro
	
	int i,j; //Variáveis Auxiliares
	
	TGrafo **m = (TGrafo**)malloc(linhas * sizeof(TGrafo*)); //Aloca um Vetor de Ponteiros
	
	for (i = 0; i < linhas; i++){ //Percorre as linhas do Vetor de Ponteiros
	   m[i] = (TGrafo*) malloc(colunas * sizeof(TGrafo)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
	   for (j = 0; j < colunas; j++){ //Percorre o Vetor de Inteiros atual.
	        m[i][j].distancia = 0; //Inicializa com 0.
	        m[i][j].fluxo = 0;
	   }
	}
	
	return m; //Retorna o Ponteiro para a Matriz Alocada
}

int** alocarMatrizInt(int linhas, int colunas){ //Recebe a quantidade de linhas e colunas como Parâmetro
	
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

