#include "Usuarios.h"
#include <stdlib.h>

Usuario *InicializarUsuario(int user_id, bool *assistidos, Usuario *prox){
    Usuario *novo =(Usuario *) malloc(sizeof(Usuario));
    novo->user_id = user_id;
    novo->assistidos = assistidos;
    novo->prox = prox;
    return novo;
}

void DestruirUsuario(Usuario *usuario){
    free(usuario->assistidos);
    free(usuario);
}

int ObterID(Usuario usuario) {
    return usuario.user_id;
}

bool *ObterAssistidos(Usuario usuario){
    return usuario.assistidos;
}

Usuario *ObterProx(Usuario usuario){
    return usuario.prox;
}

void DefinirProx(Usuario *usuario, Usuario *prox){
    usuario->prox = prox;
}

double Jaccard(Usuario a, Usuario b, int numfilmes){
    int uniao = 0, intersecao = 0;
    for (int i = 0; i < numfilmes; i++)
        if (a.assistidos[i] || b.assistidos[i]){
            uniao++;
            if (a.assistidos[i] && b.assistidos[i])
                intersecao++;
        }
    return(double)intersecao/uniao;
}

void InicializarListaDeUsuarios(Usuarios *lista){
    lista->primeiro = NULL;
    lista->ultimo = NULL;
}

Usuario *AdicionarUsuario(Usuarios *lista, int user_id, bool *assistidos){
    Usuario *novo = InicializarUsuario(user_id, assistidos, NULL);
    if (lista->primeiro == NULL)
        lista->primeiro = novo;
    else
        lista->ultimo->prox = novo;
    lista->ultimo = novo;
    return novo;
}

void DestruirListaDeUsuarios(Usuarios *lista){
    Usuario *atual = lista->primeiro, *proximo;
    while (atual != NULL){
        free(atual->assistidos);
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

Usuario *BuscarUsuarioPorID(Usuarios lista, int user_id){
    Usuario *atual = lista.primeiro;
    while (atual != NULL && atual->user_id != user_id)
        atual = atual->prox;
    return atual;
}