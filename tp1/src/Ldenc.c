#include "Ldenc.h"
#include <stdlib.h>

Lista *InicializarLista(){
    Lista *nova;
    if ((nova = (Lista *)malloc(sizeof(Lista))) != NULL){
        Nodo *cabeca = InicializarNodo(NULL, NULL, NULL);
        nova->cabeca = nova->ultimo = cabeca;
        nova->tamanho = 0;
    }
    return nova;
}

Nodo *AdicionarElemento(Lista *lista, Nodo *referencia, void *dados){
    Nodo *novo = NULL;
    if (referencia != NULL && (novo = InicializarNodo(dados, referencia->prox, referencia)) != NULL){
        if (referencia->prox != NULL)
            referencia->prox->ant = novo;
        referencia->prox = novo;
        if (lista->ultimo == referencia)
            lista->ultimo = novo;
        (lista->tamanho)++;
    }
    return novo;
}

Nodo *AdicionarAoInicio(Lista *lista, void *dados){
    Nodo *novo = NULL;
    if ((novo = InicializarNodo(dados, lista->cabeca->prox, lista->cabeca)) != NULL){
        if (lista->cabeca->prox != NULL)
            lista->cabeca->prox->ant = novo;
        lista->cabeca->prox = novo;
        if (lista->ultimo == lista->cabeca)
            lista->ultimo = novo;
        (lista->tamanho)++;
    }
    return novo;
}

Nodo *AdicionarAoFinal(Lista *lista, void *dados){
    Nodo *novo = NULL;
    if ((novo = InicializarNodo(dados, NULL, lista->ultimo)) != NULL){
        lista->ultimo->prox = novo;
        lista->ultimo = novo;
        (lista->tamanho)++;
    }
    return novo;
}

void RemoverElemento(Lista *lista, Nodo *nodo, void(*DestruirDados)(void *)){
    if (nodo != NULL && nodo != lista->cabeca){
        nodo->ant->prox = nodo->prox;
        if (lista->ultimo == nodo)
            lista->ultimo = nodo->ant;
        else
            nodo->prox->ant = nodo->ant; // Se o nodo é o último, nodo->prox == NULL
        DestruirNodo(nodo, DestruirDados);
        (lista->tamanho)--;
    }
};

void RemoverElementoApos(Lista *lista, Nodo *nodo, void(*DestruirDados)(void *)){
    RemoverElemento(lista, nodo->prox, DestruirDados); // TODO: Fazer macro
}

void RemoverPrimeiroElemento(Lista *lista, void(*DestruirDados)(void *)){
    if (lista->tamanho > 0){
        Nodo *temp = lista->cabeca->prox;
        lista->cabeca->prox = lista->cabeca->prox->prox;
        if (lista->cabeca->prox != NULL)
            lista->cabeca->prox->ant = lista->cabeca;
        if (temp == lista->ultimo)
            lista->ultimo = lista->cabeca;
        DestruirNodo(temp, DestruirDados);
        (lista->tamanho)--;
    }
}

void RemoverUltimoElemento(Lista *lista, void(*DestruirDados)(void *)){
    if (lista->tamanho > 0){
        Nodo *temp = lista->ultimo->ant;
        temp->prox = NULL;
        DestruirNodo(lista->ultimo, DestruirDados);
        lista->ultimo = temp;
        (lista->tamanho)--;
    }
}

void DeslocarElemento(Lista *lista, Nodo *origem, Nodo *destino){
    if (origem == destino || origem == lista->cabeca)
        return;

    if (lista->ultimo == origem)
        lista->ultimo = origem->ant;
    else if (lista->ultimo == destino)
        lista->ultimo = origem;

    origem->ant->prox = origem->prox;
    if (origem->prox != NULL)
        origem->prox->ant = origem->ant;

    origem->prox = destino->prox;
    origem->ant = destino;
    if (destino->prox != NULL)
        destino->prox->ant = origem;
    destino->prox = origem;
}

void TrocarElementos(Lista *lista, Nodo *a, Nodo *b){
    Nodo *temp;
    if (a == b || a == lista->cabeca || b == lista->cabeca)
        return;

    if (a == lista->ultimo)
        lista->ultimo = b;
    else if (b == lista->ultimo)
        lista->ultimo = a;

    a->ant->prox = b;
    if (a->prox != NULL)
        a->prox->ant = b;
    b->ant->prox = a;
    if (b->prox != NULL)
        b->prox->ant = a;

    temp = a->prox;
    a->prox = b->prox;
    b->prox = temp;

    temp = a->ant;
    a->ant = b->ant;
    b->ant = temp;
}

void TrocarDados(Nodo *a, Nodo *b){
    void *temp = a->dados;
    a->dados = b->dados;
    b->dados = temp;
}

Nodo *ObterPrimeiro(Lista *lista){
    return lista->cabeca->prox;
}

Nodo *ObterUltimo(Lista *lista){
    return lista->ultimo;
}

Nodo *ObterCabeca(Lista *lista){
    return lista->cabeca;
}

Nodo *ObterAnterior(Lista *lista, Nodo *nodo){ // Desnecessário
    return nodo->ant;
}

Nodo *ObterElementoPorIndice(Lista *lista, int indice){
    if (indice < 0 || indice >= lista->tamanho)
        return NULL;
    Nodo *atual = lista->cabeca->prox;
    while (indice > 0){
        atual = atual->prox;
        indice--;
    }
    return atual;
}

int ObterTamanho(Lista *lista){
    return lista->tamanho;
}

void AtravessarLista(Lista *lista, void(*Funcao)(void *)){
    if (lista->tamanho <= 0)
        return;
    Nodo *atual = lista->cabeca->prox;
    do {
        Funcao(atual->dados);
    } while ((atual = atual->prox) != NULL);
}

void InsertionSort(Lista *lista, int(*Comparacao)(void *, void *)){
    if (lista->tamanho <= 1)
        return;
    Nodo *atual = lista->cabeca->prox->prox, *i, *prox;
    while (atual != NULL){
        prox = atual->prox;
        i = lista->cabeca;
        while (i != atual && Comparacao(i->prox->dados, atual->dados))
            i = i->prox;
        DeslocarElemento(lista, atual, i);
        atual = prox;
    }
}

void DestruirLista(Lista *lista, void(*DestruirDados)(void *)){
    Nodo *atual = lista->cabeca->prox, *prox;
    DestruirNodo(lista->cabeca, NULL);
    while (atual != NULL){
        prox = atual->prox;
        DestruirNodo(atual, DestruirDados);
        atual = prox;
    }
    free(lista);
}