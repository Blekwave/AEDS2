#ifndef _USUARIOS_H_
#define _USUARIOS_H_
#include <stdbool.h>
#include "Lista.h"

/*
 O tipo Usuarios representa uma lista encadeada, cujos nodos são structs do 
 tipo Usuario.
 */

typedef struct usuario {
    int user_id;
    bool *assistidos;
} Usuario;

Usuario *InicializarUsuario(int user_id, bool *assistidos, Usuario *prox);
void DestruirUsuario(Usuario *usuario);
int ObterID(Usuario *usuario);
bool *ObterAssistidos(Usuario *usuario);

/*
 Similaridade de Jaccard: itens(A interseção B)/itens(A união B)
 */
double Jaccard(Usuario *a, Usuario *b, int numfilmes);

/*
 Adiciona um novo usuário ao final da lista de usuários. É preciso passar
 o endereço da lista de filmes assistidos, alocada externamente.
 */
Usuario *AdicionarUsuario(Lista *lista, int user_id, bool *assistidos);

/*
 Retorna o endereço do usuário de ID user_id, ou NULL, caso não haja tal
 usuário.
 */
Usuario *BuscarUsuarioPorID(Lista *lista, int user_id);

#endif