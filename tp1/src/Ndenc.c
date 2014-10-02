#include "Ndenc.h"
#include <stdlib.h>

Ndenc *InicializarNdenc(void *dados, void *prox, void *ant){
    Ndenc *novo = (Ndenc *)malloc(sizeof(Ndenc));
    if (novo != NULL){
        novo->dados = dados;
        novo->prox = prox;
        novo->ant = ant;
    }
    return novo;
}

Ndenc *ObterProx(Ndenc *nodo){
    return nodo->prox;
}

void DefinirProx(Ndenc *nodo, void *prox){
    nodo->prox = prox;
}

Ndenc *ObterAnt(Ndenc *nodo){
    return nodo->ant;
}

void DefinirAnt(Ndenc *nodo, void *ant){
    nodo->ant = ant;
}

void *ObterDados(Ndenc *nodo){
    return nodo->dados;
}

void DefinirDados(Ndenc *nodo, void *dados){
    nodo->dados = dados;
}

void DestruirNdenc(Ndenc *nodo, void (*DestruirDados)(void *)){
    if (DestruirDados != NULL)
        (*DestruirDados)(nodo->dados);
    if (nodo->dados != NULL)
        free(nodo->dados);
    free(nodo);
}