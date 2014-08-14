#ifndef _COMPLEXO_H_
#define _COMPLEXO_H_

typedef struct {
    double real;
    double imag;
} Complexo;

void Atribui(Complexo *, double, double);
void Imprime(Complexo);
void Copia(Complexo *, Complexo *);
void Soma(Complexo, Complexo, Complexo *);
int EhReal(Complexo);

#endif