#include "Racional.h"
#include "Sort.h"

/**
 * Corrige a sub-árvore especificada, se necessário, para que ela seja um min-
 * -heap. Assume que as sub-árvores cujas raízes são os filhos dessa árvore já
 * são min-heaps.
 * @param v      Vetor de inteiros no qual o heap está.
 * @param inicio Posição da raiz dessa min-heap no vetor.
 * @param fim    Última posição válida do vetor.
 */
static void int_minheap(int *v, int inicio, int fim){
    int raiz = inicio;
    while ((raiz * 2 + 1) <= fim){
        int swap = raiz; // Variável que armazena posição a ser trocada
        int filho = raiz * 2 + 1; // Filho esquerdo
        if (v[filho] < v[swap])
            swap = filho;
        filho++; // Filho direito (pode não existir dentro dos limites)
        if (filho <= fim && v[filho] < v[swap])
            swap = filho;
        if (swap != raiz){
            int temp = v[swap];
            v[swap] = v[raiz];
            v[raiz] = temp;
            raiz = swap;
        }
        else
            return; // Raiz é maior que os filhos
    }
}

/**
 * Ordena o vetor em ordem decrescente com heapsort.
 * @param v     Vetor de inteiros.
 * @param v_tam Tamanho do vetor.
 */
void HeapsortIntD(int *v, int v_tam){
    int i;
    for (i = (v_tam - 2)/2; i >= 0; i--)
        int_minheap(v, i, v_tam - 1);
    i = v_tam - 1;
    while (i > 0){
        int temp = v[0]; v[0] = v[i]; v[i] = temp; //swap
        i--;
        int_minheap(v, 0, i);
    }
}

/**
 * Corrige a sub-árvore especificada, se necessário, para que ela seja um min-
 * -heap. Assume que as sub-árvores cujas raízes são os filhos dessa árvore já
 * são min-heaps.
 * @param v      Vetor de números racionais no qual o heap está.
 * @param inicio Posição da raiz dessa min-heap no vetor.
 * @param fim    Última posição válida do vetor.
 */
static void racional_minheap(Racional *v, int inicio, int fim){
    int raiz = inicio;
    while ((raiz * 2 + 1) <= fim){
        int swap = raiz; // Variável que armazena posição a ser trocada
        int filho = raiz * 2 + 1; // Filho esquerdo
        if (Racional_Comparar(v[filho],v[swap]) < 0)
            swap = filho;
        filho++; // Filho direito (pode não existir dentro dos limites)
        if (filho <= fim && Racional_Comparar(v[filho],v[swap]) < 0)
            swap = filho;
        if (swap != raiz){
            Racional temp = v[swap];
            v[swap] = v[raiz];
            v[raiz] = temp;
            raiz = swap;
        }
        else
            return; // Raiz é maior que os filhos
    }
}

/**
 * Ordena o vetor em ordem decrescente com heapsort.
 * @param v     Vetor de números racionais.
 * @param v_tam Tamanho do vetor.
 */
void HeapsortRacionalD(Racional *v, int v_tam){
    int i;
    for (i = (v_tam - 2)/2; i >= 0; i--)
        racional_minheap(v, i, v_tam - 1);
    i = v_tam - 1;
    while (i > 0){
        Racional temp = v[0]; v[0] = v[i]; v[i] = temp; //swap
        i--;
        racional_minheap(v, 0, i);
    }
}
