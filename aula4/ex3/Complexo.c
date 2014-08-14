#include "Complexo.h"
#include <stdio.h>

void Atribui(Complexo *num, double real, double imag){
    num->real = real;
    num->imag = imag;
}

void Imprime(Complexo num){
    printf("%f + %fi\n", num.real, num.imag);
}

void Copia(Complexo *destino, Complexo *origem){
    destino->real = origem->real;
    destino->imag = origem->imag;
}

void Soma(Complexo a, Complexo b, Complexo *resultado){
    resultado->real = a.real + b.real;
    resultado->imag = a.imag + b.imag;
}

int EhReal(Complexo num){
    return num.imag == 0;
}