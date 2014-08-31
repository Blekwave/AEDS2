#ifndef _LISTA_H_
#define _LISTA_H_

#include "Nodo.h"

typedef struct {
    Nodo *primeiro;
    Nodo *ultimo;
    int tamanho;
} Lista;

/**
 * Aloca a memória da nova lista e inicializa primeiro e último elemento como
 * NULL.
 * @return endereço da nova lista.
 */
Lista *InicializarLista();

/**
 * Adiciona ao final da lista um novo nodo.
 * @param  lista Lista ao qual será adicionado o novo elemento.
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Nodo *AdicionarElemento(Lista *lista, void *dados);

/**
 * Retorna endereço do primeiro nodo.
 * @param  lista Lista da qual se quer o elemento.
 * @return       Endereço do primeiro nodo.
 */
Nodo *ObterPrimeiro(Lista *lista);

/**
 * Retorna endereço do último nodo.
 * @param  lista Lista da qual se quer o elemento.
 * @return       Endereço do último nodo.
 */
Nodo *ObterUltimo(Lista *lista);

/**
 * Libera memória dos nodos da lista e da lista em si. Realiza o procedimento
 * DestruirDados nos dados dos nodos da lista antes da liberação.
 * @param lista Lista a ser liberada.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void DestruirLista(Lista *lista, void(*DestruirDados)(void *));

#endif
