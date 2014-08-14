#include <stdio.h>
#include "Complexo.h"

int main(int argc, char const *argv[])
{
    Complexo a, b, c;
    Atribui(&a, 13, 2);
    Atribui(&b, 10, -2);
    Soma(a,b,&c);
    Imprime(a);
    printf("A = %s\n", EhReal(a) ? "Real" : "Imaginario");
    Imprime(b);
    printf("B = %s\n", EhReal(b) ? "Real" : "Imaginario");
    Imprime(c);
    printf("C = %s\n", EhReal(c) ? "Real" : "Imaginario");
    Soma(c, b, &c);
    Imprime(c);
    printf("C = %s\n", EhReal(c) ? "Real" : "Imaginario");
    return 0;
}