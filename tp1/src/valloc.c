#include "valloc.h"
#include <stdlib.h>

memchunk *InicializarMemchunk(bool used, size_t size){
    memchunk *temp = (memchunk *)malloc(sizeof(memchunk));
    temp->used = used;
    temp->size = size;
}

memchunk *ObterMemchunk(Ndenc *nodo){
    return (memchunk *)ObterDados(nodo);
}

Ndenc *EncontrarLacuna(int tam){
    Ndenc *atual = ObterPrimeiro(auxiliar);
    // É seguro assumir que a lista auxiliar sempre tem pelo menos um elemento
    // Portanto, o do while abaixo não deve falhar em situação alguma
    while (atual != NULL && (ObterDados(atual)->size < tam || ObterDados(atual)->used == 1))
        atual = ObterProx(atual);
    return atual;
}

Ndenc *EncontrarNodo(void *ptr){
    unsigned char *init = MEM;
    Ndenc *atual = ObterPrimeiro(auxiliar);
    while (atual != NULL && init != ptr){
        init += ObterMemchunk(atual)->size;
        atual = ObterProx(atual);
    }
    return atual;
}

unsigned char *EncontrarEndereco(Ndenc *nodo){
    unsigned char *init = MEM;
    Ndenc *atual = ObterPrimeiro(auxiliar);
     while (atual != NULL && atual != nodo){
        init += ObterMemchunk(atual)->size;
        atual = ObterProx(atual);
    }
    return init;
}

void valloc_initialize(){
    auxiliar = InicializarLista();
    unsigned char MEM[MAX_MEM];
    AdicionarAoInicio(auxiliar, (void *)InicializarMemchunk(false, MAX_MEM));
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
    size_t size = num*tam;
    unsigned char *pos = (unsigned char *)valloc(size);
    while ((--size) >= 0){
        pos[size] = 0;
    }
    return (void *)pos;
}

//vrealloc
void *vrealloc(void *var, size_t tam);

//vfree
void vfree(void *ptr){
    Ndenc *nodo = EncontrarNodo(ptr);
    memchunk *atual = ObterMemchunk(nodo);
    atual->used = false;
    if (ObterMemchunk(ObterAnt(nodo))->used == false){
        atual->size += ObterMemchunk(ObterAnt(nodo))->size;
        RemoverElemento(auxiliar, ObterAnt(nodo), NULL);
    }
    if (ObterMemchunk(ObterProx(nodo))->used == false){
        atual->size += ObterMemchunk(ObterProx(nodo))->size;
        RemoverElemento(auxiliar, ObterProx(nodo), NULL);
    }
}

//print_valloc
void print_valloc();