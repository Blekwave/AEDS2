#include "Ndenc.h"
#include <stdlib.h>

Nodo *InicializarNodo(void *dados, void *prox, void *ant){
    Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
    if (novo != NULL){
        novo->dados = dados;
        novo->prox = prox;
        novo->ant = ant;
    }
    return novo;
}

Nodo *ObterProx(Nodo *nodo){
    return nodo->prox;
}

void DefinirProx(Nodo *nodo, void *prox){
    nodo->prox = prox;
}

Nodo *ObterAnt(Nodo *nodo){
    return nodo->ant;
}

void DefinirAnt(Nodo *nodo, void *ant){
    nodo->ant = ant;
}

void *ObterDados(Nodo *nodo){
    return nodo->dados;
}

void DefinirDados(Nodo *nodo, void *dados){
    nodo->dados = dados;
}

void DestruirNodo(Nodo *nodo, void (*DestruirDados)(void *)){
    if (DestruirDados != NULL)
        (*DestruirDados)(nodo->dados);
    if (nodo->dados != NULL)
        free(nodo->dados);
    free(nodo);
}