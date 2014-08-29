#include "Nodo.h"
#include <stdlib.h>

Nodo *InicializarNodo(void *dados, void *prox){
    Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
    if (novo != NULL){
        novo->dados = dados;
        novo->prox = prox;
    }
    return novo;
}

Nodo *ObterProx(Nodo *nodo){
    return nodo->prox;
}

void DefinirProx(Nodo *nodo, void *prox){
    nodo->prox = prox;
}

void *ObterDados(Nodo *nodo){
    return nodo->dados;
}

void DefinirDados(Nodo *nodo, void *dados){
    nodo->dados = dados;
}

void DestruirNodo(Nodo *nodo){
    free(nodo);
}
void DestruirNodoAlt(Nodo *nodo, void (*DestruirDados)(void *)){
    (*DestruirDados)(nodo->dados);
    free(nodo);
}