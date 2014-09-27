#ifndef _LISTA_H_
#define _LISTA_H_

#include "Ndenc.h"

typedef struct {
    Nodo *cabeca;
    Nodo *ultimo;
    int tamanho;
} Lista;

/**
 * Aloca a memória da nova lista, adiciona o nodo cabeça e atribui seu endereço
 * como primeira e última posições da lista.
 * @return endereço da nova lista.
 */
Lista *InicializarLista();

/**
 * Adiciona um novo nodo após um nodo especificado.
 * @param  lista Lista ao qual será adicionado o novo elemento.
 * @param  referencia Nodo após o qual será adicionado o novo elemento
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Nodo *AdicionarElemento(Lista *lista, Nodo *referencia, void *dados);

/**
 * Adiciona um novo nodo no início da lista.
 * @param  lista Lista ao qual será adicionado o novo elemento.
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Nodo *AdicionarAoInicio(Lista *lista, void *dados);

/**
 * Adiciona um novo nodo ao fim da lista.
 * @param  lista Lista ao qual será adicionado o novo elemento.
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Nodo *AdicionarAoFinal(Lista *lista, void *dados);

/**
 * Remove um elemento da lista. Pode realizar um procedimento especificado para
 * destruir os dados armazenados.
 * @param lista         Lista da qual o elemento será removido.
 * @param nodo          Nodo a ser removido
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void RemoverElemento(Lista *lista, Nodo *nodo, void(*DestruirDados)(void *));

/**
 * Remove elemento após o nodo. Pode realizar um procedimento especificado para
 * destruir os dados armazenados.
 * @param lista         Lista da qual o elemento será removido.
 * @param nodo          Nodo a ser removido
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void RemoverElementoApos(Lista *lista, Nodo *nodo, void(*DestruirDados)(void *));

/**
 * Remove o primeiro elemento da lista. Pode realizar um procedimento especi-
 * ficado para destruir os dados armazenados.
 * @param lista         Lista da qual o elemento será removido.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void RemoverPrimeiroElemento(Lista *lista, void(*DestruirDados)(void *));

/**
 * Remove o ultimo elemento da lista. Pode realizar um procedimento especifica
 * do para destruir os dados armazenados.
 * @param lista         Lista da qual o elemento será removido.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void RemoverUltimoElemento(Lista *lista, void(*DestruirDados)(void *));

/**
 * Desloca um nodo para a posição após o destino especificado.
 * @param lista   Lista na qual as operações são realizadas.
 * @param origem  Nodo a ser deslocado
 * @param destino Nodo após o qual origem deve ser posicionado
 */
void DeslocarElemento(Lista *lista, Nodo *origem, Nodo *destino);

/**
 * Troca dois nodos de posição em uma lista.
 * @param lista Lista que contém os nodos
 * @param a     Nodo A
 * @param b     Nodo B
 */
void TrocarElementos(Lista *lista, Nodo *a, Nodo *b);

/**
 * Troca o endereço armazenado no ponteiro de dados de dois nodos de uma lista.
 * @param a Nodo A
 * @param b Nodo B
 */
void TrocarDados(Nodo *a, Nodo *b);

/**
 * Retorna endereço do primeiro nodo válido.
 * @param  lista Lista da qual se quer o elemento.
 * @return       Endereço do primeiro nodo válido.
 */
Nodo *ObterPrimeiro(Lista *lista);

/**
 * Retorna endereço do último nodo (podendo este ser o cabeça)
 * @param  lista Lista da qual se quer o elemento.
 * @return       Endereço do último nodo.
 */
Nodo *ObterUltimo(Lista *lista);

/**
 * Retorna endereço do nodo cabeça.
 * @param  lista Lista da qual se quer o elemento.
 * @return       Endereço do nodo cabeça.
 */
Nodo *ObterCabeca(Lista *lista);

/**
 * Retorna endereço do nodo anterior. O(n)
 * @param  lista Lista na qual está o nodo.
 * @param  nodo  Nodo do qual se quer o endereço do anterior.
 * @return       Endereço do nodo anterior.
 */
Nodo *ObterAnterior(Lista *lista, Nodo *nodo);

/**
 * Retorna endereço do nodo de índice indice na lista.
 * @param  lista  Lista na qual está o nodo.
 * @param  indice Índice natural menor que o tamanho da lista.
 * @return        Endereço do nodo.
 */
Nodo *ObterElementoPorIndice(Lista *lista, int indice);

/**
 * Retorna o tamanho da lista, sem contar com a cabeça.
 * @param  lista Lista 
 * @return       Número de elementos da lista.
 */
int ObterTamanho(Lista *lista);

/**
 * Aplica uma função aos dados de todos os nodos válidos da lista.
 * @param  lista  Lista
 * @param  Funcao função a ser aplicada aos dados dos nodos. A função deve 
 *                retornar void e ter um único argumento do tipo void *.
 */
void AtravessarLista(Lista *lista, void(*Funcao)(void *));

/**
 * Ordena a lista na ordem estipulada pela função de comparação passada.
 * @param  lista      Lista a ser ordenada
 * @param  Comparacao Função a ser usada para determinar a ordem na qual a lista
 *                    deve ser ordenada. Os parâmetros recebidos são ponteiros
 *                    void contendo o endereço dos dados de dois elementos a e b
 *                    sendo que a vem antes de b. Assim, se a função lida com 
 *                    inteiros, por exemplo, retornar a > b significa que a lista
 *                    será ordenada em ordem decrescente.
 */
void InsertionSort(Lista *lista, int(*Comparacao)(void *, void *));

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
