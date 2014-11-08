#ifndef _RACIONAL_H_
#define _RACIONAL_H_

#include <stdlib.h>

typedef struct {
    int num;
    int den;
} Racional;

/**
 * Inicializa um número racional. Simplifica a fração automaticamente.
 * @param  num Numerador
 * @param  den Denominador
 * @return     Endereço do número racional.
 */
Racional *Racional_Inicializar(int num, int den);

/**
 * Define o valor de um número racional. Simplifica a fração automaticamente.
 * @param racional Endereço de um número racional.
 * @param num      Numerador
 * @param den      Denominador
 */
void Racional_Definir(Racional *racional, int num, int den);

/**
 * Compara dois números racionais. Se comporta de forma similar a strcmp no seu
 * valor de retorno.
 * @param  a Número racional a
 * @param  b Número racional b
 * @return   n | n == 0 se a == b, n < 0 se a < b, n > 0 se a > b.
 */
int Racional_Comparar(Racional a, Racional b);

#endif
