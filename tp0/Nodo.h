#ifndef _NODO_H_
#define _NODO_H_

typedef struct nodo {
    void *dados;
    struct nodo *prox;
} Nodo;

Nodo *InicializarNodo(void *dados, void *prox);

Nodo *ObterProx(Nodo *nodo);
void DefinirProx(Nodo *nodo, void *prox);

void *ObterDados(Nodo *nodo);
void DefinirDados(Nodo *nodo, void *dados);

void DestruirNodo(Nodo *nodo);
void DestruirNodoAlt(Nodo *nodo, void (*DestruirDados)(void *));

#endif