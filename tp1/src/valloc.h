/**
 * TP1: Alocação de Memória - Valloc.h
 * Sistema de alocação dinâmica de memória através de vetor estático e lista
 * Victor Pires Diniz - victorpiresdiniz@dcc.ufmg.br
 */

#ifndef _VALLOC_H_
#define _VALLOC_H_

#include <stdlib.h>
#include <stdbool.h>
#include "Ldenc.h"

/**
 * struct memchunk
 * Struct que define o tamanho e o estado de cada fragmento da memória
 * gerenciada pelo programa. É armazenado em cada nodo da lista auxiliar.
 */
typedef struct {
    bool used;
    size_t size;
} memchunk;


/**
 * unsigned char memoria[MAX_MEM]
 * Vetor de unsigned char utilizado como memória a ser alocada pelas funções
 * da biblioteca. É utilizado através da keyword "extern" em "valloc.c".
 */
#define MAX_MEM 1024576
unsigned char memoria[MAX_MEM];

/**
 * extern Ldenc *auxiliar
 * Ponteiro de lista duplamente encadeada que armazena a lista auxiliar. Essa
 * lista auxiliar é responsável por gerenciar o estado de alocação de cada parte
 * da memória fornecida pela biblioteca.
 */
extern Ldenc *auxiliar;

/**
 * Aloca memória, se possível, ocupando a primeira lacuna possível em MEM.
 * @param  tam Tamanho, em bytes, da memória alocada.
 * @return     Ponteiro para o início do bloco de memória alocado ou NULL, caso
 *             não tenha sido possível alocar o espaço requisitado.
 */
void *valloc(size_t tam);

/**
 * Aloca memória com valloc e inicializa a memória alocada com zeros.
 * @param  num Número de blocos a serem alocados.
 * @param  tam Tamanho de cada bloco de memória.
 * @return     Ponteiro para o início do primeiro bloco de memória alocado ou
 *             NULL, caso não tenha sido possível alocar o espaço requerido.
 */
void *vcalloc(size_t num, size_t tam);

/**
 * Aloca novo espaço na memória para a variável var, movendo seu conteúdo para
 * o novo bloco. Caso o tamanho alocado seja menor do que o disponível anterior-
 * mente, o conteúdo será truncado. A função tenta realocar a memória contiguamente
 * dentro do possível.
 * Se o endereço especificado para a realocação é nulo, a função se comporta co-
 * mo malloc. Se o tamanho da realocação é nulo, a função se comporta como free.
 * @param  var Variável a ser realocada.
 * @param  tam Tamanho novo, em bytes, disponível para a variável.
 * @return     Ponteiro para o início do bloco de memória alocado ou NULL, caso
 *             não tenha sido possível alocar o espaço requisitado.
 */
void *vrealloc(void *var, size_t tam);

/**
 * Libera o espaço alocado previamente na memória. Não faz nada se mem é nulo.
 * @param mem Endereço do início do bloco alocado.
 */
void vfree(void *mem);

/**
 * Inicializa a lista auxiliar. Permite o início das operações na memória vir-
 * tual da biblioteca.
 */
void inicializa_gerencia();

/**
 * Imprime cada bloco livre ou ocupado na memória, com o seu tamanho e posição.
 */
void imprime_status_memoria();

/**
 * Deleta a lista auxiliar, libera o espaço alocado na memória virtual e fina-
 * liza a possibilidade de operação da biblioteca.
 */
void finaliza_gerencia();

#endif