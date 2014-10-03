#include "valloc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

unsigned char memoria[MAX_MEM];
Ldenc *auxiliar;

memchunk *InicializarMemchunk(bool used, size_t size){
    memchunk *temp = (memchunk *)malloc(sizeof(memchunk));
    temp->used = used;
    temp->size = size;
    return temp;
}

memchunk *ObterMemchunk(Ndenc *nodo){
    return (memchunk *)ObterDados(nodo);
}

Ndenc *EncontrarLacuna(int tam){
    Ndenc *atual = ObterPrimeiro(auxiliar);
    // É seguro assumir que a lista auxiliar sempre tem pelo menos um elemento
    // Portanto, o do while abaixo não deve falhar em situação alguma
    while (atual != NULL && (ObterMemchunk(atual)->size < tam || ObterMemchunk(atual)->used == true))
        atual = ObterProx(atual);
    return atual;
}

Ndenc *EncontrarNodo(void *ptr){
    unsigned char *init = memoria;
    Ndenc *atual = ObterPrimeiro(auxiliar);
    while (atual != NULL && init != ptr){
        init += ObterMemchunk(atual)->size;
        atual = ObterProx(atual);
    }
    return atual;
}

unsigned char *EncontrarEndereco(Ndenc *nodo){
    unsigned char *init = memoria;
    Ndenc *atual = ObterPrimeiro(auxiliar);
     while (atual != NULL && atual != nodo){
        init += ObterMemchunk(atual)->size;
        atual = ObterProx(atual);
    }
    return init;
}

//valloc
void *valloc(size_t tam){
    /**
     * Encontra lacuna da qual possa ser alocado um bloco de memória de tamanho
     * tam. Adiciona novo nodo com memchunk de tamanho tam antes da lacuna e re-
     * duz o tamanho da lacuna por tam. Retorna endereço no vetor da memória 
     * alocada ou NULL, caso não seja possível alocar a memória.
     */
    Ndenc *lacuna = EncontrarLacuna(tam);
    if (lacuna != NULL){
        memchunk *temp = InicializarMemchunk(true, tam);
        Ndenc *novo = AdicionarElemento(auxiliar, ObterAnt(lacuna), (void *)temp);
        ObterMemchunk(lacuna)->size -= tam;
        return (void *)EncontrarEndereco(novo);
    }
    return NULL;
}

//vcalloc
void *vcalloc(size_t num, size_t tam){
    int size = num*tam;
    unsigned char *pos = (unsigned char *)valloc(size);
    if (pos != NULL){
        size--;
        while (size >= 0){
            pos[size] = 0;
            size--;
        }
        return (void *)pos;
    }
    return NULL;
}

//vrealloc
void *vrealloc(void *var, size_t tam){
    size_t tamanho_origem = ObterMemchunk(EncontrarNodo(var))->size;
    vfree(var);
    void *novo = valloc(tam);
    memmove(novo, var, tamanho_origem);
    return novo;
}

//vfree
void vfree(void *ptr){
    Ndenc *nodo = EncontrarNodo(ptr);
    memchunk *atual = ObterMemchunk(nodo);
    atual->used = false;
    Ndenc *ant = ObterAnt(nodo), *prox = ObterProx(nodo);
    // Se o anterior de ant é NULL, ele é o nodo cabeça (que não tem um memchunk)
    if (ant != NULL && ObterAnt(ant) != NULL && ObterMemchunk(ant)->used == false){
        atual->size += ObterMemchunk(ObterAnt(nodo))->size;
        RemoverElemento(auxiliar, ObterAnt(nodo), NULL);
    }
    if (prox != NULL && ObterMemchunk(prox)->used == false){
        atual->size += ObterMemchunk(ObterProx(nodo))->size;
        RemoverElemento(auxiliar, ObterProx(nodo), NULL);
    }
}

void inicializa_gerencia(){
    auxiliar = InicializarLdenc();
    AdicionarAoInicio(auxiliar, (void *)InicializarMemchunk(false, MAX_MEM));
}

void imprime_status_memoria(){
    Ndenc *atual = ObterPrimeiro(auxiliar);
    int pos = 0;
    memchunk *temp;
    printf("Status agora:\n");
    do {
        temp = ObterMemchunk(atual);
        printf("Pos: %d, Size: %zu, Status: %s\n",
            pos, temp->size, temp->used ? "USED" : "FREE");
        pos += temp->size;
    } while ((atual = ObterProx(atual)) != NULL);
}

void finaliza_gerencia(){
    DestruirLdenc(auxiliar, NULL);
}