
#include "fordFulkerson.h"
//#include <string.h>

// Number of vertices in given graph 
//#define V 6 

TFila fila;
int **grafoFluxo;
int **grafoDistancia;
//char **vetorNomes;
int vetorCaminhao;
//TLista L;
int qntdNodo = 0;

void lerArquivoCsv(char *nomeArq, int **matriz, int op);
void separarDadosDaLinha(int **matriz, char linha[10000], int contLinhas, int op);
int contaNodos(char linha[10000]);
int pegarIndice(char palavra[100]);
void imprimir(int **matriz);

void lerArquivoTxt(int *vetorCaminhao);
void separarDadosDaLinhaTxt(int *vetorCaminhao, char linha[50]);
void insereCaminhao(int *vetorCaminhao, char id[], char nome[], int saldo);



int main() {

	//Verificar a quantidade de nodos
	lerArquivoCsv("fluxo.csv", grafoFluxo, 2);
	printf("qntd: %d\n", qntdNodo);
	V = qntdNodo;
	
	grafoFluxo = alocarMatriz(qntdNodo, qntdNodo);
	grafoDistancia = alocarMatriz(qntdNodo, qntdNodo);
	
	//Preenchendo o grafo de fluxos
	lerArquivoCsv("fluxo.csv", grafoFluxo, 0);
	//Preenchendo o grafo de distancias
	lerArquivoCsv("distancia.csv", grafoDistancia, 0);
	
	/*printf("\nGrafo de fluxo\n");
	imprimir(grafoFluxo);
	printf("\n\nGrafo de distancia\n");
	imprimir(grafoDistancia);
	printf("\n\n");*/

	
  	int i = fordFulkerson(grafoFluxo, 0, 5, &fila);
    printf("O caminho maximo possivel eh %d ", i ); 
  
    return 0; 
}





void lerArquivoTxt(int *vetorCaminhao){
	char linha[50]; // string armazenara a linha
    
    FILE *arq;
    arq = fopen("caminhao.txt","r"); // Abre o arquivo
    if (arq == NULL){  // Se houve erro na abertura
		printf("Problemas na abertura do arquivo\n");
	}else{
		while(fgets(linha,sizeof(linha)-1,arq) != NULL) { // Loop para ler cada linha do arquivo enquanto houver linhas
			separarDadosDaLinhaTxt(vetorCaminhao, linha);
		}
	}
    fclose(arq);     
}

void separarDadosDaLinhaTxt(int *vetorCaminhao, char linha[50]){
	char delimitador[] = ";"; // Caracter delimitador
    char *info; // Ponteiro para armazenar as informações

	char placa[50];
	char nome[50];
	int capacidade;

	info = strtok(linha,delimitador); // info recebe a primeira string antes do primeiro delimitador da primeira linha

	while(info != NULL) { // Enquanto houver linhas no arquivo

		strcpy(codigo,info); // Copia info para codigo

		info = strtok(NULL,delimitador); // Separa o nome da linha
		strcpy(nome,info); // Copia info para nome

		info = strtok(NULL,delimitador); // Separa o saldo da linha
		saldo=atoi(info); // Copia info para saldo

		info = strtok(NULL,delimitador); // Separa o codigo da linha

		insereCaminhao(vetorCaminhao, codigo, nome, saldo);
	}
}

void insereCaminhao(int *vetorCaminhao, char id[], char nome[], int saldo){
	TCliente *novo = (TCliente *) malloc (sizeof(TCliente));
	    
    novo->prox = NULL;
    novo->ante = NULL;
    
    strcpy(novo->id,id);
    strcpy(novo->nome,nome);
    novo->saldo = saldo;
    
    if (L->inicio == NULL){
    	L->inicio = novo;
    	L->fim = novo;
    } else {
    	L->fim->prox= novo;
    	novo->ante = L->fim;
    	L->fim = novo;
	}
}






void lerArquivoCsv(char *nomeArq, int **matriz, int op){
	
	char linha[10000]; // string armazenara a linha
    FILE *arq;
	int contLinhas = 0;
    arq = fopen(nomeArq,"r"); // Abre o arquivo
    
    if (arq == NULL){  // Se houve erro na abertura
   
		printf("Problemas na abertura do arquivo\n");
	}else{
		
		if(op < 2){
			
			fgets(linha, sizeof(linha)-1, arq);
			while(fgets(linha, sizeof(linha)-1, arq) != NULL) { // Loop para ler cada linha do arquivo enquanto houver linhas
				separarDadosDaLinha(matriz, linha, contLinhas, op);
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


void separarDadosDaLinha(int **matriz, char linha[10000], int contLinhas, int op){
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
			matriz[contLinhas][contColunas-1] = peso;
			
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
	
	for(c = 0; c < qntdNodo; c++){ //Loop para percorrer todos os �ndices do seu "vetor"
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

void imprimir(int **matriz){
	int i,j;
	for(i = 0; i < qntdNodo; i++){
		for(j = 0; j < qntdNodo; j++){
			printf("|%2d", matriz[i][j]);
		}
		printf("\n");
	}
}

