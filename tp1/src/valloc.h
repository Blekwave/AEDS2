#ifndef _VALLOC_H_
#define _VALLOC_H_

#include <stdbool.h>
#include "Ldenc.h"

typedef struct {
    bool used;
    size_t size;
} memchunk;

#define MAX_MEM 1024576
extern unsigned char MEM[MAX_MEM];
extern Ldenc *auxiliar;

//valloc_initialize
void valloc_initialize();

//valloc
void *valloc(size_t tam);

//vcalloc
void *vcalloc(size_t num, size_t tam);

//vrealloc
void *vrealloc(void *var, size_t tam);

//vfree
void vfree(void *mem);

//print_valloc
void print_valloc();

#endif