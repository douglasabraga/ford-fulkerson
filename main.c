
#include "fordFulkerson.h"
//#include <string.h>

// Number of vertices in given graph 
//#define V 6 

TFila fila;
int **grafo;
char **vetorNomes;
int qntdNodo = 0;

void lerArquivo(int op);
void separarDadosDaLinha(char linha[10000], int contLinhas);
int contaNodos(char linha[10000]);
int pegarIndice(char palavra[100]);


int main() {

	//Verificar a quantidade de nodos
	lerArquivo(2);
	printf("qntd: %d\n", qntdNodo);
	V = qntdNodo;
	
	grafo = alocarMatriz(qntdNodo, qntdNodo);
	
	//Preencher a Matriz
	lerArquivo(1);
	
    // Let us create a graph shown in the above example 
    /*int graph[V][V] = { {0, 16, 13, 0, 0, 0}, 
                        {0, 0, 10, 12, 0, 0}, 
                        {0, 4, 0, 0, 14, 0}, 
                        {0, 0, 9, 0, 0, 20}, 
                        {0, 0, 0, 7, 0, 4}, 
                        {0, 0, 0, 0, 0, 0} 
                      }; */
  	int i = fordFulkerson(grafo, 0, 5, &fila);
    printf("O caminho maximo possivel eh %d ", i ); 
  
    return 0; 
}


void lerArquivo(int op){
	
	char linha[10000]; // string armazenara a linha
    FILE *arq;
	int contLinhas = 0;
    arq = fopen("fluxo.csv","r"); // Abre o arquivo
    
    if (arq == NULL){  // Se houve erro na abertura
   
		printf("Problemas na abertura do arquivo\n");
	}else{
		
		if(op < 2){
			
			fgets(linha, sizeof(linha)-1, arq);
			while(fgets(linha, sizeof(linha)-1, arq) != NULL) { // Loop para ler cada linha do arquivo enquanto houver linhas
				separarDadosDaLinha(linha, contLinhas);
				contLinhas++;
			}
			
		}else{
			//fgets(linha, sizeof(linha)-1, arq); // Loop para ler cada linha do arquivo enquanto houver linhas
			
			fgets(linha, sizeof(linha)-1, arq); // Loop para ler cada linha do arquivo enquanto houver linhas
			
			contaNodos(linha);
		}
	}
    fclose(arq);
}


void separarDadosDaLinha(char linha[10000], int contLinhas){
	char delimitador[] = ";"; // Caracter delimitador
	
    char *info; // Ponteiro para armazenar as informacoes
	//printf("-> %s", linha);
	int peso;

	int contColunas = 0;
	
	info = strtok(linha, delimitador); // info recebe a primeira string antes do primeiro delimitador da primeira linha
	while(contColunas < qntdNodo) { // Enquanto houver linhas no arquivo
	//Ignorar primeira coluna

		if(contColunas != 0){
			info = strtok(NULL, delimitador);
			peso = atoi(info); // Copia info para peso
			grafo[contLinhas][contColunas-1] = peso;
			
		}
		contColunas++;
	}
}


int contaNodos(char linha[10000]){
	char delimitador[] = ";"; // Caracter delimitador
    char *info; // Ponteiro para armazenar as informacoes
    int c = 0, aux;
    char nome[10000];
    strcpy(nome, linha);
	
	info = strtok(linha, delimitador); // info recebe a primeira string antes do primeiro delimitador da primeira linha
	
	while(info != NULL) { // Enquanto houver linhas no arquivo
		//printf("%d\n", atoi(info));
		info = strtok(NULL, delimitador); // Separa o nome da linha
		qntdNodo++;
	}

	vetorNomes = (char **) malloc( qntdNodo * sizeof( char * ) );
	info = strtok(nome, delimitador);
	
	for(c = 0; c < qntdNodo; c++){ //Loop para percorrer todos os índices do seu "vetor"
		//Tratando o \n
		aux = strstr(info, "\n") - info;
		if(aux > 0) info[aux] = '\0';
		
    	vetorNomes[c] = strdup(info);
    	info = strtok(NULL, delimitador);
	}
}

int pegarIndice(char palavra[100]){
	int count = 0;
	while(count < qntdNodo){
		
		if(!strcmp(vetorNomes[count], palavra)){
			return count;
		}
		
		count++;
	}
}

