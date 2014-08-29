#ifndef _LISTA_H_
#define _LISTA_H_

#include "Nodo.h"

typedef struct {
    Nodo *primeiro;
    Nodo *ultimo;
    int tamanho;
} Lista;

Lista *InicializarLista();

Nodo *AdicionarElemento(Lista *lista, void *dados);

Nodo *ObterPrimeiro(Lista *lista);
Nodo *ObterUltimo(Lista *lista);

void DestruirLista(Lista *lista);
void DestruirListaAlt(Lista *lista, void(*DestruirDados)(void *));

#endif
