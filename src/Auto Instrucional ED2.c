/*
 ============================================================================
 Name        : Auto.c
 Authors     : João Lucas Veloso Gouveia, Vitor Yomassa e Frederico Perpetuo
 Version     :
 Copyright   : Academic work for FUMEC
 Description : Academic work for FUMEC(Josephus problem) in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define TAMANHO_MAXIMO_NOME_SOLDADOS 20

typedef struct lista TLista;

struct lista {
	char nomeSoldado[TAMANHO_MAXIMO_NOME_SOLDADOS];
	TLista* prox;
};

//protótipos
TLista* inicializaListaSoldados(); // inicializa a lista para que a mesma nao seja um ponteiro apontando pro nada
TLista* insereSoldadoNoCirc(TLista*, char*); //insere um soldado em uma lista pre criada
void imprimeSoldadosCirc(TLista*); // imprime a lista de soldados no console
int verificaCircVazio(TLista*); // verifica se a lista de soldados esta vazia
int verificaNumeroSoldados(TLista*); // verifica a quantidade de soldados na lista
TLista* buscaSoldado(TLista*, char*); // busca um soldado especifico
TLista* sorteiaSoldado(TLista*); // sorteia um soldado aleatorio
TLista* lerNomeSoldados(TLista*, char*); // le nomes de soldados inseridos num arquivo de texto que fica na raiz do projeto
TLista* excluiSoldadoDoCirc(TLista*, char*); // exclui um soldado da lista
int sorteiaN(void); // sorteia um N, que por sua vez discrimina de quanto sera o numero de saltos do algoritimo
void executaJosephus(TLista*, TLista*, int);

int main(void) {
	//testando a funcao insere e imprime e verificaCircVazio
	TLista* listaSoldados = inicializaListaSoldados();
	TLista* soldadoSorteado = inicializaListaSoldados();
	int n = sorteiaN();

	setbuf(stdout, NULL);

	// pre execucao do algoritimo, pegando os dados
	listaSoldados = lerNomeSoldados(listaSoldados, "nomes.txt");

	soldadoSorteado = sorteiaSoldado(listaSoldados);
	//execucao do algoritimo
	executaJosephus(listaSoldados, soldadoSorteado, n);

	return EXIT_SUCCESS;
}

TLista* inicializaListaSoldados() {
	return NULL;
}

TLista* insereSoldadoNoCirc(TLista* lista,
		char dado[TAMANHO_MAXIMO_NOME_SOLDADOS]) {
	TLista* aux, *aux2;
	if (lista == NULL) {
		lista = (TLista*) malloc(sizeof(TLista));
		strcpy(lista->nomeSoldado, dado);
		lista->prox = lista;
	} else {
		aux = lista;
		do {
			aux = aux->prox;
		} while (aux->prox != lista);
		aux2 = (TLista*) malloc(sizeof(TLista));
		strcpy(aux2->nomeSoldado, dado);
		aux2->prox = lista;
		aux->prox = aux2;
	}
	return lista;
}

void imprimeSoldadosCirc(TLista* lista) {
	TLista* aux;
	if (lista == NULL) {
		printf("\nLista vazia!\n");
	} else {
		aux = lista;
		do {
			if (aux->prox != lista) {
				TLista* excluiSoldadoDoCirc(TLista*, char*);


				printf("%s - ", aux->nomeSoldado);
			} else {
				printf("%s", aux->nomeSoldado);
			}
			aux = aux->prox;
		} while (aux != lista);
	}
}

int verificaCircVazio(TLista* lista) {
	if (lista == NULL) {
		return 1;
	}
	return 0;
}

int verificaNumeroSoldados(TLista* lista) {
	TLista* aux = lista;
	int contador = 0;
	if (lista != NULL) {
		do {
			contador++;
			aux = aux->prox;
		} while (aux != lista);
	}
	return contador;
}

TLista* buscaSoldado(TLista* lista, char* busca){
	TLista* aux = lista;
	if(lista != NULL){
		do{
			if(strcmp(aux->nomeSoldado, busca) == 0){
				return aux;
			}
			aux = aux->prox;
		} while (aux != lista);
		return NULL;
	}
	return lista;
}

TLista* sorteiaSoldado(TLista* lista) {
	int tamanhoLista = verificaNumeroSoldados(lista);
	int indiceSoldadoSorteado;
	int aux = 0;
	TLista* soldadoSorteado = lista;

	srand((unsigned) time(NULL));

	if (lista != NULL) {
		do {
			indiceSoldadoSorteado = rand()
					% (int) pow(10, ((int) log10(tamanhoLista)) + 1);
		} while (indiceSoldadoSorteado >= tamanhoLista);

		do{
			soldadoSorteado = soldadoSorteado->prox;
			aux++;
		}while(aux != indiceSoldadoSorteado);
		return soldadoSorteado;
	}
	return NULL;
}

TLista* lerNomeSoldados(TLista* lista, char* path){
	char* nome;
	FILE *file;
	file = fopen(path, "rt");
	if (file) {
		while (fgets(nome,150, file)) {
			nome[strlen(nome)-1] = '\0';
			lista = insereSoldadoNoCirc(lista, nome);
		}
		fclose(file);
	}else{
		printf("\nAquivo nomes.txt nao encontrado\n");
	}

	return lista;
}

TLista* excluiSoldadoDoCirc(TLista* lista, char* nomeMorto){
	/* TLista* soldadoMorto = buscaSoldado(lista, nomeMorto);
	 *  Se eu usar a funcao buscaSoldado vou ter de fazer duas varreduras na
	 *  lista, sendo uma feita na funcao buscaSoldado e a outra nessa funcao
	 *  para buscar o soldado anterior ao buscado, entao resolvi fazer com uma
	 *  busca so para um menor esforco computacional, ja que dessa forma
	 *  consigo as duas informacoes
	 */
	TLista* aux = lista;
	TLista* soldadoExcluido = NULL;
	do{
		aux = aux->prox;
	}while(strcmp(aux->prox->nomeSoldado, nomeMorto) != 0);
	soldadoExcluido = aux->prox;
	aux->prox = aux->prox->prox;
	if(soldadoExcluido == lista){
		lista = aux;
	}
	free(soldadoExcluido);
	return lista;
}

int sorteiaN(void){ // sendo n um numero entre 2 e 10
	srand((unsigned) time(NULL));
	int n;
	do{
		n = rand()%10;
	}while(n < 2);
	return n;
}

void executaJosephus(TLista* listaSoldados, TLista* soldadoSorteado, int n){
	int iteracao = 0;
	int aux = 1;
	TLista* aux2 = NULL;
	TLista* soldadoAtual = soldadoSorteado;
	TLista* sobrevivente = inicializaListaSoldados();

	printf("Execucao do Algoritimo");
	printf("\n=================================\n");
	printf("\nDados recebidos:\n");
	printf("Lista de soldados: ");
	imprimeSoldadosCirc(listaSoldados);
	printf("\nSoldado Sorteado = %s", soldadoSorteado->nomeSoldado);
	printf("\nN: %i", n);
	printf("\n=================================\n");
	while(verificaNumeroSoldados(listaSoldados) != 1){
		iteracao++;
		printf("iteracao %i: \n", iteracao);
		while(aux < n){
			soldadoAtual = soldadoAtual->prox;
			aux++;
		}
		aux = 1;
		aux2 = soldadoAtual->prox;
		printf("\nSoldado excluido: %s\n", soldadoAtual->nomeSoldado);
		if(listaSoldados == soldadoAtual){
			listaSoldados = listaSoldados->prox;
		}
		soldadoAtual = excluiSoldadoDoCirc(listaSoldados, soldadoAtual->nomeSoldado);
		soldadoAtual = aux2;
		printf("\nnum soldados = %i\n", verificaNumeroSoldados(listaSoldados));
	}
	printf("\nsoldado sobrevivente: %s", listaSoldados->nomeSoldado);
}
