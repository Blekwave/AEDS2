#ifndef _SORT_H_
#define _SORT_H_

#include "Racional.h"

/**
 * Ordena o vetor em ordem decrescente com heapsort.
 * @param v     Vetor de inteiros.
 * @param v_tam Tamanho do vetor.
 */
void HeapsortIntD(int *v, int v_tam);

/**
 * Ordena o vetor em ordem decrescente com heapsort.
 * @param v     Vetor de números racionais.
 * @param v_tam Tamanho do vetor.
 */
void HeapsortRacionalD(Racional *v, int v_tam);

#endif
