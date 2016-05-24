/*
 ============================================================================
 Name        : Auto.c
 Author      : João Lucas Veloso Gouveia
 Version     :
 Copyright   : Academic work for FUMEC
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO_MAXIMO_NOME_SOLDADOS 20

typedef struct lista TLista;

struct lista{
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

int main(void){
	//testando a funcao insere e imprime e verificaCircVazio
	TLista* lista = inicializaListaSoldados();
	TLista* soldadoEspecifico = inicializaListaSoldados();

	setbuf(stdout, NULL);

	int a = verificaCircVazio(lista);
	int tamanhoLista;

	if(a == 1){
		printf("Lista vazia!\n");
	}else{
		printf("Lista nao vazia!\n");
	}

	lista = insereSoldadoNoCirc(lista, "Joao");
	lista = insereSoldadoNoCirc(lista, "Andressa");
	lista = insereSoldadoNoCirc(lista, "Xulambs");
	lista = insereSoldadoNoCirc(lista, "Xurango");

	imprimeSoldadosCirc(lista);

	a = verificaCircVazio(lista);

	if(a == 1){
		printf("\nLista vazia!\n");
	}else{
		printf("\nLista nao vazia!\n");
	}

	//teste do calculo do tamanho da lista
	tamanhoLista = verificaNumeroSoldados(lista);
	printf("\nTemos %i soldados!", tamanhoLista);

	soldadoEspecifico = buscaSoldado(lista, "Joao");
	printf("\nsoldado especifico = %s", soldadoEspecifico->nomeSoldado);
	return EXIT_SUCCESS;
}

TLista* inicializaListaSoldados(){
	return NULL;
}

TLista* insereSoldadoNoCirc(TLista* lista, char dado[TAMANHO_MAXIMO_NOME_SOLDADOS]){
	TLista* aux, *aux2;
	if(lista == NULL){
		lista = (TLista*) malloc(sizeof(TLista));
		strcpy(lista->nomeSoldado, dado);
		lista->prox = lista;
	}else{
		aux = lista;
		do{
			aux = aux->prox;
		}while(aux->prox != lista);
		aux2 = (TLista*) malloc(sizeof(TLista));
		strcpy(aux2->nomeSoldado, dado);
		aux2->prox = lista;
		aux->prox = aux2;
	}
	return lista;
}

void imprimeSoldadosCirc(TLista* lista){
	TLista* aux;
	if(lista == NULL){
		printf("\nLista vazia!\n");
	}else{
		aux = lista;
		do{
			if(aux->prox != lista){
				printf("%s - ",aux->nomeSoldado);
			}else{
				printf("%s",aux->nomeSoldado);
			}
			aux = aux->prox;
		}while(aux != lista);
	}
}

int verificaCircVazio(TLista* lista){
	if(lista == NULL){
		return 1;
	}
	return 0;
}

int verificaNumeroSoldados(TLista* lista){
	TLista* aux = lista;
	int contador = 0;
	if(lista != NULL){
		do{
			contador++;
			aux = aux->prox;
		}while(aux != lista);
	}
	return contador;
}

TLista* buscaSoldado(TLista* lista, char* busca){
	int ref = 0;
	TLista* aux = lista;
	if(lista != NULL){
		do{
			if(strcmp(aux->nomeSoldado, busca) == 0){
				return aux;
			}
			aux = aux->prox;
		}while(aux != lista);
		return NULL;
	}
	return lista;
}
