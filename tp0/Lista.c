#include "Lista.h"
#include <stdlib.h>

Lista *InicializarLista(){
    Lista *nova = (Lista *)malloc(sizeof(Lista));
    nova->primeiro = nova->ultimo = NULL;
    nova->tamanho = 0;
    return nova;
}

Nodo *AdicionarElemento(Lista *lista, void *dados){
    Nodo *novo = InicializarNodo(dados, NULL);
    if (novo != NULL){
        if (lista->primeiro == NULL)
            lista->primeiro = novo;
        else
            DefinirProx(lista->ultimo, novo);
        lista->ultimo = novo;
        lista->tamanho += 1;
    }
    return novo;
}

Nodo *ObterPrimeiro(Lista *lista){
    return lista->primeiro;
}

Nodo *ObterUltimo(Lista *lista){
    return lista->ultimo;
}

void DestruirLista(Lista *lista){
    Nodo *atual = lista->primeiro, *prox;
    while (atual != NULL){
        prox = ObterProx(atual);
        DestruirNodo(atual);
        atual = prox;
    }
    free(lista);
}

void DestruirListaAlt(Lista *lista, void(*DestruirDados)(void *)){
    Nodo *atual = lista->primeiro, *prox;
    while (atual != NULL){
        prox = ObterProx(atual);
        DestruirNodoAlt(atual, DestruirDados);
        atual = prox;
    }
}