/**
 * Lista duplamente encadeada - Ldenc.h
 * Biblioteca de lista duplamente encadeada genérica com cabeça
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

#ifndef _LDENC_H_
#define _LDENC_H_

#include "Ndenc.h"

typedef struct ldenc {
    Ndenc *cabeca;
    Ndenc *ultimo;
    int tamanho;
} Ldenc;

/////////////////////////////////
// INICIALIZAÇÃO E FINALIZAÇÃO //
/////////////////////////////////

/**
 * Aloca a memória da nova lista, adiciona o nodo cabeça e atribui seu endereço
 * como primeira e última posições da lista.
 * @return endereço da nova lista.
 */
Ldenc *Ldenc_Inicializar();

/**
 * Libera memória dos nodos da lista e da lista em si. Realiza o procedimento
 * DestruirDados nos dados dos nodos da lista antes da liberação.
 * @param lista Ldenc a ser liberada.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Ldenc_Destruir(Ldenc *lista, void(*DestruirDados)(void *));

//////////////
// INSERÇÃO //
//////////////

/**
 * Adiciona um novo nodo após um nodo especificado.
 * @param  lista Ldenc ao qual será adicionado o novo elemento.
 * @param  referencia Ndenc após o qual será adicionado o novo elemento
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Ndenc *Ldenc_AdicionarElemento(Ldenc *lista, Ndenc *referencia, void *dados);

/**
 * Adiciona um novo nodo no início da lista.
 * @param  lista Ldenc ao qual será adicionado o novo elemento.
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Ndenc *Ldenc_AdicionarAoInicio(Ldenc *lista, void *dados);

/**
 * Adiciona um novo nodo ao fim da lista.
 * @param  lista Ldenc ao qual será adicionado o novo elemento.
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Ndenc *Ldenc_AdicionarAoFinal(Ldenc *lista, void *dados);

/////////////
// REMOÇÃO //
/////////////

/**
 * Remove um elemento da lista. Pode realizar um procedimento especificado para
 * destruir os dados armazenados.
 * @param lista         Ldenc da qual o elemento será removido.
 * @param nodo          Ndenc a ser removido
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Ldenc_RemoverElemento(Ldenc *lista, Ndenc *nodo, void(*DestruirDados)(void *));

/**
 * Remove elemento após o nodo. Pode realizar um procedimento especificado para
 * destruir os dados armazenados.
 * @param lista         Ldenc da qual o elemento será removido.
 * @param nodo          Ndenc a ser removido
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Ldenc_RemoverElementoApos(Ldenc *lista, Ndenc *nodo, void(*DestruirDados)(void *));

/**
 * Remove o primeiro elemento da lista. Pode realizar um procedimento especi-
 * ficado para destruir os dados armazenados.
 * @param lista         Ldenc da qual o elemento será removido.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Ldenc_RemoverPrimeiroElemento(Ldenc *lista, void(*DestruirDados)(void *));

/**
 * Remove o ultimo elemento da lista. Pode realizar um procedimento especifica
 * do para destruir os dados armazenados.
 * @param lista         Ldenc da qual o elemento será removido.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Ldenc_RemoverUltimoElemento(Ldenc *lista, void(*DestruirDados)(void *));

/////////////////////////////////////
// DESLOCAMENTO, TROCA E ORDENAÇÃO //
/////////////////////////////////////

/**
 * Desloca um nodo para a posição após o destino especificado.
 * @param lista   Ldenc na qual as operações são realizadas.
 * @param origem  Ndenc a ser deslocado
 * @param destino Ndenc após o qual origem deve ser posicionado
 */
void Ldenc_DeslocarElemento(Ldenc *lista, Ndenc *origem, Ndenc *destino);

/**
 * Troca dois nodos de posição em uma lista.
 * @param lista Ldenc que contém os nodos
 * @param a     Ndenc A
 * @param b     Ndenc B
 */
void Ldenc_TrocarElementos(Ldenc *lista, Ndenc *a, Ndenc *b);

/**
 * Troca o endereço armazenado no ponteiro de dados de dois nodos de uma lista.
 * @param a Ndenc A
 * @param b Ndenc B
 */
void Ldenc_TrocarDados(Ndenc *a, Ndenc *b);

/**
 * Ordena a lista na ordem estipulada pela função de comparação passada.
 * @param  lista      Ldenc a ser ordenada
 * @param  Comparacao Função a ser usada para determinar a ordem na qual a lista
 *                    deve ser ordenada. Os parâmetros recebidos são ponteiros
 *                    void contendo o endereço dos dados de dois elementos a e b
 *                    sendo que a vem antes de b. Assim, se a função lida com 
 *                    inteiros, por exemplo, retornar a > b significa que a lista
 *                    será ordenada em ordem decrescente.
 */
void Ldenc_InsertionSort(Ldenc *lista, int(*Comparacao)(void *, void *));

///////////////
// TRAVESSIA //
///////////////

/**
 * Aplica uma função aos dados de todos os nodos válidos da lista.
 * @param  lista  Ldenc
 * @param  Funcao função a ser aplicada aos dados dos nodos. A função deve 
 *                retornar void e ter um único argumento do tipo void *.
 */
void Ldenc_Atravessar(Ldenc *lista, void(*Funcao)(void *));

///////////////
// INTERFACE //
///////////////

/**
 * Retorna endereço do primeiro nodo válido.
 * @param  lista Ldenc da qual se quer o elemento.
 * @return       Endereço do primeiro nodo válido.
 */
Ndenc *Ldenc_ObterPrimeiro(Ldenc *lista);

/**
 * Retorna endereço do último nodo (podendo este ser o cabeça)
 * @param  lista Ldenc da qual se quer o elemento.
 * @return       Endereço do último nodo.
 */
Ndenc *Ldenc_ObterUltimo(Ldenc *lista);

/**
 * Retorna endereço do nodo cabeça.
 * @param  lista Ldenc da qual se quer o elemento.
 * @return       Endereço do nodo cabeça.
 */
Ndenc *Ldenc_ObterCabeca(Ldenc *lista);

/**
 * Retorna endereço do nodo anterior. Função redundante: funcionalidade efetuada
 * por ObterAnt, de "Ndenc.h". Existe para manter compatibilidade com a implemen-
 * tação de lista encadeada simples, na qual essa operação depende da lista e é
 * O(n).
 * @param  lista Ldenc na qual está o nodo.
 * @param  nodo  Ndenc do qual se quer o endereço do anterior.
 * @return       Endereço do nodo anterior.
 */
Ndenc *Ldenc_ObterAnterior(Ldenc *lista, Ndenc *nodo);

/**
 * Retorna endereço do nodo de índice indice na lista.
 * @param  lista  Ldenc na qual está o nodo.
 * @param  indice Índice natural menor que o tamanho da lista.
 * @return        Endereço do nodo.
 */
Ndenc *Ldenc_ObterElementoPorIndice(Ldenc *lista, int indice);

/**
 * Retorna o tamanho da lista, sem contar com a cabeça.
 * @param  lista Ldenc 
 * @return       Número de elementos da lista.
 */
int Ldenc_ObterTamanho(Ldenc *lista);

#endif
