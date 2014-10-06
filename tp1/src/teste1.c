#include "valloc.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int *vetor;
    inicializa_gerencia();

    // for (int i = 0; i < MAX_MEM; i++)
    //     printf("%d ", memoria[i]);

    vetor = valloc(sizeof(int)*5);
    printf("Alocando 5 inteiros (sizeof int = %d)\n", sizeof(int));
    for(int i = 0; i < 5; i++)
        printf("vetor[%d] = %d\n", i, vetor[i]);
    imprime_status_memoria();
    printf("Inicializando os elementos\n");
    vetor[0] = 3;
    vetor[1] = 6;
    vetor[2] = 38;
    vetor[3] = 12;
    vetor[4] = 155;
    for(int i = 0; i < 5; i++)
        printf("vetor[%d] = %d\n", i, vetor[i]);

    int *vetor2 = vcalloc(20, sizeof(int));
    printf("Alocando 20 inteiros\n");

    imprime_status_memoria();

    for(int i = 0; i < 20; i++)
        printf("vetor2[%d] = %d\n", i, vetor2[i]);

    imprime_status_memoria();

    vetor = vrealloc(vetor, sizeof(int)*20);
    printf("Realocando o primeiro vetor para vinte elementos.\n");

    imprime_status_memoria();

    for(int i = 0; i < 20; i++)
        printf("vetor[%d] = %d\n", i, vetor[i]);

    vfree(vetor);
    vfree(vetor2);

    imprime_status_memoria();
    finaliza_gerencia();
    return 0;
}