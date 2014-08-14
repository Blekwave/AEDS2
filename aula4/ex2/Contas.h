#ifndef _CONTAS_H_
#define _CONTAS_H_

#include "ContaBancaria.h"
#define CONTAS_MAX 50

typedef struct {
    ContaBancaria contas[CONTAS_MAX];
    int numcontas;
} Contas;

void InicializaContas (Contas *);
int CriarNovasContas (Contas *, int);
void ImprimirContas (Contas *);
int ZerarSaldoConta (Contas *, int);

#endif