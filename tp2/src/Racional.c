#include "Racional.h"

/**
 * Obtém o MDC de dois inteiros.
 * @param  a Inteiro
 * @param  b Inteiro
 * @return   MDC de a e b
 */
static int MDC(int a, int b){
    int r;
    if (b > a){
        int temp = b;
        b = a;
        a = temp;
    }
    do {
        r = a % b;
        a = b;
        b = r;
    } while (r != 0);
    return a;
}

/**
 * Inicializa um número racional. Simplifica a fração automaticamente.
 * @param  num Numerador
 * @param  den Denominador
 * @return     Endereço do número racional.
 */
Racional *Racional_Inicializar(int num, int den){
    Racional *novo = malloc(sizeof(Racional));
    int mdc = MDC(num, den);
    novo->num = num/mdc;
    novo->den = den/mdc;
    return novo;
}

/**
 * Define o valor de um número racional. Simplifica a fração automaticamente.
 * @param racional Endereço de um número racional.
 * @param num      Numerador
 * @param den      Denominador
 */
void Racional_Definir(Racional *racional, int num, int den){
    int mdc = MDC(num, den);
    racional->num = num/mdc;
    racional->den = den/mdc;
}

/**
 * Compara dois números racionais. Se comporta de forma similar a strcmp no seu
 * valor de retorno.
 * @param  a Número racional a
 * @param  b Número racional b
 * @return   n | n == 0 se a == b, n < 0 se a < b, n > 0 se a > b.
 */
int Racional_Comparar(Racional a, Racional b){
    b.num *= a.den;
    a.num *= b.den;
    return a.num - b.num;
}
