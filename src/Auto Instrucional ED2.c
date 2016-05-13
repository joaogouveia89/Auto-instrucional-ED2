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

int main(void) {
	puts("Hello world"); /* prints Hello world */
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
