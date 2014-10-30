/**
 * Lista encadeada - Lista.h
 * Biblioteca de lista encadeada genérica com cabeça
 * Victor Pires Diniz - victorpiresdiniz@dcc.ufmg.br
 *
 * Características:
 *   Opera de forma completamente genérica, com armazenamento de dados por meio
 *   de ponteiros void. Permite a ordenação, travessia e remoção com funções ge-
 *   néricas passadas por parâmetro, para comportar qualquer tipo de dados sem
 *   necessidade de alteração no código fonte da biblioteca.
 * 
 *   Contém sempre pelo menos um elemento cabeça, de forma a facilitar a imple-
 *   mentação de vários procedimentos.
 */

#ifndef _LISTA_H_
#define _LISTA_H_

#include "Nodo.h"

typedef struct {
    Nodo *cabeca;
    Nodo *ultimo;
    int tamanho;
} Lista;

/////////////////////////////////
// INICIALIZAÇÃO E FINALIZAÇÃO //
/////////////////////////////////

/**
 * Aloca a memória da nova lista, adiciona o nodo cabeça e atribui seu endereço
 * como primeira e última posições da lista.
 * @return endereço da nova lista.
 */
Lista *Lista_Inicializar();

/**
 * Libera memória dos nodos da lista e da lista em si. Realiza o procedimento
 * DestruirDados nos dados dos nodos da lista antes da liberação.
 * @param lista Lista a ser liberada.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Lista_Destruir(Lista *lista, void(*DestruirDados)(void *));

//////////////
// INSERÇÃO //
//////////////

/**
 * Adiciona um novo nodo após um nodo especificado.
 * @param  lista Lista ao qual será adicionado o novo elemento.
 * @param  referencia Nodo após o qual será adicionado o novo elemento
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Nodo *Lista_AdicionarElemento(Lista *lista, Nodo *referencia, void *dados);

/**
 * Adiciona um novo nodo no início da lista.
 * @param  lista Lista ao qual será adicionado o novo elemento.
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Nodo *Lista_AdicionarAoInicio(Lista *lista, void *dados);

/**
 * Adiciona um novo nodo ao fim da lista.
 * @param  lista Lista ao qual será adicionado o novo elemento.
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Nodo *Lista_AdicionarAoFinal(Lista *lista, void *dados);

/////////////
// REMOÇÃO //
/////////////

/**
 * Remove um elemento da lista. Pode realizar um procedimento especificado para
 * destruir os dados armazenados.
 * @param lista         Lista da qual o elemento será removido.
 * @param nodo          Nodo a ser removido
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Lista_RemoverElemento(Lista *lista, Nodo *nodo, void(*DestruirDados)(void *));

/**
 * Remove elemento após o nodo. Pode realizar um procedimento especificado para
 * destruir os dados armazenados.
 * @param lista         Lista da qual o elemento será removido.
 * @param nodo          Nodo a ser removido
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Lista_RemoverElementoApos(Lista *lista, Nodo *nodo, void(*DestruirDados)(void *));

/**
 * Remove o primeiro elemento da lista. Pode realizar um procedimento especi-
 * ficado para destruir os dados armazenados.
 * @param lista         Lista da qual o elemento será removido.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Lista_RemoverPrimeiroElemento(Lista *lista, void(*DestruirDados)(void *));

/**
 * Remove o ultimo elemento da lista. Pode realizar um procedimento especifica
 * do para destruir os dados armazenados.
 * @param lista         Lista da qual o elemento será removido.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Lista_RemoverUltimoElemento(Lista *lista, void(*DestruirDados)(void *));

/////////////////////////////////////
// DESLOCAMENTO, TROCA E ORDENAÇÃO //
/////////////////////////////////////

/**
 * Desloca um nodo para a posição após o destino especificado.
 * @param lista   Lista na qual as operações são realizadas.
 * @param origem  Nodo a ser deslocado
 * @param destino Nodo após o qual origem deve ser posicionado
 */
void Lista_DeslocarElemento(Lista *lista, Nodo *origem, Nodo *destino);

/**
 * Troca dois nodos de posição em uma lista.
 * @param lista Lista que contém os nodos
 * @param a     Nodo A
 * @param b     Nodo B
 */
void Lista_TrocarElementos(Lista *lista, Nodo *a, Nodo *b);

/**
 * Troca o endereço armazenado no ponteiro de dados de dois nodos de uma lista.
 * @param a Nodo A
 * @param b Nodo B
 */
void Lista_TrocarDados(Nodo *a, Nodo *b);

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
void Lista_InsertionSort(Lista *lista, int(*Comparacao)(void *, void *));

///////////////
// TRAVESSIA //
///////////////

/**
 * Aplica uma função aos dados de todos os nodos válidos da lista.
 * @param  lista  Lista
 * @param  Funcao função a ser aplicada aos dados dos nodos. A função deve 
 *                retornar void e ter um único argumento do tipo void *.
 */
void Lista_Atravessar(Lista *lista, void(*Funcao)(void *));

///////////////
// INTERFACE //
///////////////

/**
 * Retorna endereço do primeiro nodo válido.
 * @param  lista Lista da qual se quer o elemento.
 * @return       Endereço do primeiro nodo válido.
 */
Nodo *Lista_ObterPrimeiro(Lista *lista);

/**
 * Retorna endereço do último nodo (podendo este ser o cabeça)
 * @param  lista Lista da qual se quer o elemento.
 * @return       Endereço do último nodo.
 */
Nodo *Lista_ObterUltimo(Lista *lista);

/**
 * Retorna endereço do nodo cabeça.
 * @param  lista Lista da qual se quer o elemento.
 * @return       Endereço do nodo cabeça.
 */
Nodo *Lista_ObterCabeca(Lista *lista);

/**
 * Retorna endereço do nodo anterior. O(n)
 * @param  lista Lista na qual está o nodo.
 * @param  nodo  Nodo do qual se quer o endereço do anterior.
 * @return       Endereço do nodo anterior.
 */
Nodo *Lista_ObterAnterior(Lista *lista, Nodo *nodo);

/**
 * Retorna endereço do nodo de índice indice na lista.
 * @param  lista  Lista na qual está o nodo.
 * @param  indice Índice natural menor que o tamanho da lista.
 * @return        Endereço do nodo.
 */
Nodo *Lista_ObterElementoPorIndice(Lista *lista, int indice);

/**
 * Retorna o tamanho da lista, sem contar com a cabeça.
 * @param  lista Lista 
 * @return       Número de elementos da lista.
 */
int Lista_ObterTamanho(Lista *lista);

#endif
