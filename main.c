
#include "fordFulkerson.h"

// Fila para o Ford-Fulkerson
TFila fila;
//Vetor para guardar o nome das arestas
char **vetorNomes;
//Grafo de vertices preenchida após a leitura dos arqs *fluxo* e *distancia*
TGrafo **grafo;
// Lista de caminhões preenchida após a leitura do arq
TLista listaCaminhao;
// Varável global responsável por armazenar a quantidade de arestas para alocação da matriz
int qntdNodo = 0;

//int cont = 0;

void lerArquivoCsv(char *nomeArq, TGrafo **matriz, int op);
void separarDadosDaLinha(TGrafo **matriz, char linha[10000], int contLinhas, int op);
int contaNodos(char linha[10000]);
int pegarIndice(char palavra[100]);
void imprimir(TGrafo **matriz, int op);

void lerArquivoTxt(TLista *L);
void separarDadosDaLinhaTxt(TLista *L, char linha[50]);


void imprimeLista(TLista *L);


int main() {
	
	//Verificar a quantidade de nodos
	lerArquivoCsv("fluxo.csv", grafo, 2);
	printf("qntd: %d\n", qntdNodo);
	V = qntdNodo;
	
	grafo = alocarMatriz(qntdNodo, qntdNodo);
	
	//Preenchendo o grafo com os dados do fluxo
	lerArquivoCsv("fluxo.csv", grafo, 0);
	//Preenchendo o grafo com os dados da distancia
	lerArquivoCsv("distancia.csv", grafo, 1);
	
	lerArquivoTxt(&listaCaminhao);
//	printf("\n\n");
//	imprimir(grafo, 0);
//	
//	printf("\n\n");
	imprimir(grafo, 1);

	//imprimeLista(&listaCaminhao);
	printf("\n\n");

  	int i = fordFulkerson(grafo, 0, 8, &fila, &listaCaminhao, vetorNomes);
    printf("O caminho maximo possivel eh %d ", i );
    
    printf("\n\nCAMINHOES NAO ALOCADOS");
    imprimirVeiculosNaoAlocados(&listaCaminhao);
  
    return 0; 
}


void lerArquivoTxt(TLista *L){
	char linha[50]; // string armazenara a linha
    
    FILE *arq;
    arq = fopen("caminhao.txt","r"); // Abre o arquivo
    if (arq == NULL){  // Se houve erro na abertura
		printf("Problemas na abertura do arquivo\n");
	}else{
		while(fgets(linha,sizeof(linha)-1,arq) != NULL) { // Loop para ler cada linha do arquivo enquanto houver linhas
			separarDadosDaLinhaTxt(L, linha);
		}
	}
    fclose(arq);     
}

void separarDadosDaLinhaTxt(TLista *L, char linha[50]){
	char delimitador[] = ";"; // Caracter delimitador
    char *info; // Ponteiro para armazenar as informaÃ§Ãµes

	char placa[50];
	char nome[50];
	int capacidade;

	info = strtok(linha,delimitador); // info recebe a primeira string antes do primeiro delimitador da primeira linha

	while(info != NULL) { // Enquanto houver linhas no arquivo

		strcpy(placa,info); // Copia info para codigo

		info = strtok(NULL,delimitador); // Separa o nome da linha
		strcpy(nome,info); // Copia info para nome

		info = strtok(NULL,delimitador); // Separa o saldo da linha
		capacidade=atoi(info); // Copia info para saldo

		info = strtok(NULL,delimitador); // Separa o codigo da linha

		insereCaminhao(L, placa, nome, capacidade);
	}
}


void lerArquivoCsv(char *nomeArq, TGrafo **matriz, int op){
	
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


void separarDadosDaLinha(TGrafo **matriz, char linha[10000], int contLinhas, int op){
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
			if(op == 0) grafo[contLinhas][contColunas-1].fluxo = peso;
			else grafo[contLinhas][contColunas-1].distancia = peso;
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

void imprimir(TGrafo **matriz, int op){
	int i,j;
	for(i = 0; i < qntdNodo; i++){
		for(j = 0; j < qntdNodo; j++){
			if(op == 0) printf("|%2d", matriz[i][j].fluxo);
			else printf("|%2d", matriz[i][j].distancia);
		}
		printf("\n");
	}
}

void imprimeLista(TLista *L){
	TCaminhao *atual = L->inicio;

	while(atual != NULL){
		printf("\nPlaca: %s", atual->placa);
		printf("\nNome: %s",atual->nome);
		printf("\nCapacidade: %d\n", atual->capacidade);
		atual = atual->prox;
	}
}

