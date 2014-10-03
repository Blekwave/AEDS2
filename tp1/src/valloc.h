#ifndef _VALLOC_H_
#define _VALLOC_H_

#include <stdlib.h>
#include <stdbool.h>
#include "Ldenc.h"

typedef struct {
    bool used;
    size_t size;
} memchunk;

#define MAX_MEM 1024576
extern unsigned char memoria[MAX_MEM];
extern Ldenc *auxiliar;

//valloc
void *valloc(size_t tam);

//vcalloc
void *vcalloc(size_t num, size_t tam);

//vrealloc
void *vrealloc(void *var, size_t tam);

//vfree
void vfree(void *mem);


void inicializa_gerencia();
void imprime_status_memoria();
void finaliza_gerencia();

#endif