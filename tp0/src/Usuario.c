#include "Usuario.h"
#include <stdlib.h>

Usuario *InicializarUsuario(int user_id, bool *assistidos){
    Usuario *novo = (Usuario *)malloc(sizeof(Usuario));
    novo->user_id = user_id;
    novo->assistidos = assistidos;
    return novo;
}

void DestruirUsuario(Usuario *usuario){
    free(usuario->assistidos);
}

int ObterID(Usuario *usuario) {
    return usuario->user_id;
}

bool *ObterAssistidos(Usuario *usuario){
    return usuario->assistidos;
}

double Jaccard(Usuario *a, Usuario *b, int numfilmes){
    int uniao = 0, intersecao = 0;
    for (int i = 0; i < numfilmes; i++)
        if (a->assistidos[i] || b->assistidos[i]){
            uniao++;
            if (a->assistidos[i] && b->assistidos[i])
                intersecao++;
        }
    return (double)intersecao/uniao;
}

Usuario *AdicionarUsuario(Lista *lista, int user_id, bool *assistidos){
    Usuario *novo = InicializarUsuario(user_id, assistidos);
    AdicionarElemento(lista, (void *)novo);
    return novo;
}

Usuario *BuscarUsuarioPorID(Lista *lista, int user_id){
    Nodo *atual = lista->primeiro;
    // O cast para Usuario * é necessário, já que ObterDados retorna void *
    while (atual != NULL && ObterID((Usuario *)ObterDados(atual)) != user_id)
        atual = ObterProx(atual);
    return atual == NULL ? NULL : (Usuario *)ObterDados(atual);
}