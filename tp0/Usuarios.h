#ifndef _USUARIOS_H_
#define _USUARIOS_H_
#include <stdbool.h>

/*
 O tipo Usuarios representa uma lista encadeada, cujos nodos são structs do 
 tipo Usuario.
 */

typedef struct usuario {
    int user_id;
    bool *assistidos;
    struct usuario *prox;
} Usuario;

Usuario *InicializarUsuario(int user_id, bool *assistidos, Usuario *prox);

void DestruirUsuario(Usuario *usuario);

int ObterID(Usuario usuario);

bool *ObterAssistidos(Usuario usuario);

Usuario *ObterProx(Usuario usuario);

void DefinirProx(Usuario *usuario, Usuario *prox);


/*
 Similaridade de Jaccard: itens(A interseção B)/itens(A união B)
 */
double Jaccard(Usuario a, Usuario b, int numfilmes);



typedef struct {
    Usuario *primeiro;
    Usuario *ultimo;
} Usuarios;

/*
 Inicializa a lista de usuários vazia.
 */
void InicializarListaDeUsuarios(Usuarios *lista);

/*
 Adiciona um novo usuário ao final da lista de usuários. É preciso passar
 o endereço da lista de filmes assistidos, alocada externamente.
 */
Usuario *AdicionarUsuario(Usuarios *lista, int user_id, bool *assistidos);

/*
 Libera a memória alocada para os usuários da lista.
 */
void DestruirListaDeUsuarios(Usuarios *lista);

/*
 Retorna o endereço do usuário de ID user_id, ou NULL, caso não haja tal
 usuário.
 */
Usuario *BuscarUsuarioPorID(Usuarios lista, int user_id);

#endif