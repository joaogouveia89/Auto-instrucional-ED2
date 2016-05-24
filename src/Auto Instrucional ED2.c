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
TLista* inicializaListaSoldados();
TLista* insereSoldadoNoCirc(TLista*, char*);
void imprimeSoldadosCirc(TLista*);
int verificaCircVazio(TLista*);
int verificaNumeroSoldados(TLista*);
TLista* buscaSoldado(TLista*, char*);
TLista* sorteiaSoldado(TLista*);
TLista* lerNomeSoldados(TLista*, char*);
TLista* excluiSoldadoDoCirc(TLista*, char*);
int sorteiaN(void);

int main(void) {
	//testando a funcao insere e imprime e verificaCircVazio
	TLista* lista = inicializaListaSoldados();

	setbuf(stdout, NULL);

	lista = lerNomeSoldados(lista, "nomes.txt");

	imprimeSoldadosCirc(lista);

	lista = excluiSoldadoDoCirc(lista, "Andressa");

	printf("\n\n");

	imprimeSoldadosCirc(lista);

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

	srand((unsigned) time(NULL));

	if (lista != NULL) {
		do {
			indiceSoldadoSorteado = rand()
					% (int) pow(10, ((int) log10(tamanhoLista)) + 1);
		} while (indiceSoldadoSorteado >= tamanhoLista);

		return buscaSoldado(lista, indiceSoldadoSorteado);
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
	free(soldadoExcluido);
	return lista;
}

int sorteiaN(void){ // sendo n um numero entre 1 e 10
	srand((unsigned) time(NULL));
	return rand()%10;
}
