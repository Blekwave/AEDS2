#include "Ldenc.h"
#include <stdlib.h>

Ldenc *InicializarLdenc(){
    Ldenc *nova;
    if ((nova = (Ldenc *)malloc(sizeof(Ldenc))) != NULL){
        // Inicializa o nodo cabeça e o atribui à primeira e à última posições
        Ndenc *cabeca = InicializarNdenc(NULL, NULL, NULL);
        nova->cabeca = nova->ultimo = cabeca;
        nova->tamanho = 0;
    }
    return nova;
}

Ndenc *AdicionarElemento(Ldenc *lista, Ndenc *referencia, void *dados){
    Ndenc *novo = NULL;
    if (referencia != NULL && (novo = InicializarNdenc(dados, referencia->prox, referencia)) != NULL){
        if (referencia->prox != NULL)
            referencia->prox->ant = novo;
        referencia->prox = novo;
        if (lista->ultimo == referencia)
            lista->ultimo = novo;
        (lista->tamanho)++;
    }
    return novo;
}

Ndenc *AdicionarAoInicio(Ldenc *lista, void *dados){
    Ndenc *novo = NULL;
    if ((novo = InicializarNdenc(dados, lista->cabeca->prox, lista->cabeca)) != NULL){
        if (lista->cabeca->prox != NULL)
            lista->cabeca->prox->ant = novo;
        lista->cabeca->prox = novo;
        if (lista->ultimo == lista->cabeca)
            lista->ultimo = novo;
        (lista->tamanho)++;
    }
    return novo;
}

Ndenc *AdicionarAoFinal(Ldenc *lista, void *dados){
    Ndenc *novo = NULL;
    if ((novo = InicializarNdenc(dados, NULL, lista->ultimo)) != NULL){
        lista->ultimo->prox = novo;
        lista->ultimo = novo;
        (lista->tamanho)++;
    }
    return novo;
}

void RemoverElemento(Ldenc *lista, Ndenc *nodo, void(*DestruirDados)(void *)){
    if (nodo != NULL && nodo != lista->cabeca){
        nodo->ant->prox = nodo->prox;
        if (lista->ultimo == nodo)
            lista->ultimo = nodo->ant;
        else
            nodo->prox->ant = nodo->ant; // Se o nodo é o último, nodo->prox == NULL
        DestruirNdenc(nodo, DestruirDados);
        (lista->tamanho)--;
    }
};

void RemoverElementoApos(Ldenc *lista, Ndenc *nodo, void(*DestruirDados)(void *)){
    RemoverElemento(lista, nodo->prox, DestruirDados);
}

void RemoverPrimeiroElemento(Ldenc *lista, void(*DestruirDados)(void *)){
    if (lista->tamanho > 0){
        Ndenc *temp = lista->cabeca->prox;
        lista->cabeca->prox = lista->cabeca->prox->prox;
        if (lista->cabeca->prox != NULL)
            lista->cabeca->prox->ant = lista->cabeca;
        if (temp == lista->ultimo)
            lista->ultimo = lista->cabeca;
        DestruirNdenc(temp, DestruirDados);
        (lista->tamanho)--;
    }
}

void RemoverUltimoElemento(Ldenc *lista, void(*DestruirDados)(void *)){
    if (lista->tamanho > 0){
        Ndenc *temp = lista->ultimo->ant;
        temp->prox = NULL;
        DestruirNdenc(lista->ultimo, DestruirDados);
        lista->ultimo = temp;
        (lista->tamanho)--;
    }
}

void DeslocarElemento(Ldenc *lista, Ndenc *origem, Ndenc *destino){
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

void TrocarElementos(Ldenc *lista, Ndenc *a, Ndenc *b){
    Ndenc *temp;
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

void TrocarDados(Ndenc *a, Ndenc *b){
    void *temp = a->dados;
    a->dados = b->dados;
    b->dados = temp;
}

Ndenc *ObterPrimeiro(Ldenc *lista){
    return lista->cabeca->prox;
}

Ndenc *ObterUltimo(Ldenc *lista){
    return lista->ultimo;
}

Ndenc *ObterCabeca(Ldenc *lista){
    return lista->cabeca;
}

Ndenc *ObterAnterior(Ldenc *lista, Ndenc *nodo){ // Redundante: ObterAnt
    return nodo->ant;
}

Ndenc *ObterElementoPorIndice(Ldenc *lista, int indice){
    if (indice < 0 || indice >= lista->tamanho)
        return NULL;
    Ndenc *atual = lista->cabeca->prox;
    while (indice > 0 && atual != NULL){
        atual = atual->prox;
        indice--;
    }
    return atual;
}

int ObterTamanho(Ldenc *lista){
    return lista->tamanho;
}

void AtravessarLdenc(Ldenc *lista, void(*Funcao)(void *)){
    if (lista->tamanho <= 0)
        return;
    Ndenc *atual = lista->cabeca->prox;
    do {
        Funcao(atual->dados);
    } while ((atual = atual->prox) != NULL);
}

void InsertionSort(Ldenc *lista, int(*Comparacao)(void *, void *)){
    if (lista->tamanho <= 1)
        return;
    Ndenc *atual = lista->cabeca->prox->prox, *i, *prox;
    while (atual != NULL){
        prox = atual->prox;
        i = lista->cabeca;
        while (i != atual && Comparacao(i->prox->dados, atual->dados))
            i = i->prox;
        DeslocarElemento(lista, atual, i);
        atual = prox;
    }
}

void DestruirLdenc(Ldenc *lista, void(*DestruirDados)(void *)){
    Ndenc *atual = lista->cabeca->prox, *prox;
    DestruirNdenc(lista->cabeca, NULL);
    while (atual != NULL){
        prox = atual->prox;
        DestruirNdenc(atual, DestruirDados);
        atual = prox;
    }
    free(lista);
}