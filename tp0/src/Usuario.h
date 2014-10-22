#ifndef _USUARIO_H_
#define _USUARIO_H_
#include <stdbool.h>
#include "Lista.h"

typedef struct usuario {
    int user_id;
    bool *assistidos;
} Usuario;

/**
 * Aloca a memória e inicializa os elementos de um novo usuário.
 * @param  user_id    ID do usuário
 * @param  assistidos Vetor de bool que representa os filmes assistidos pelo
 *                    usuário
 * @return            Endereço do novo usuário.
 */
Usuario *InicializarUsuario(int user_id, bool *assistidos);

/**
 * Libera a memória dos elementos do usuário (mas não do usuário em si)
 * @param usuario Usuário a ser destruído
 */
void DestruirUsuario(Usuario *usuario);

/**
 * Retorna o ID do usuário
 * @param  usuario Usuário a ser lido
 * @return         ID do usuário
 */
int ObterID(Usuario *usuario);

/**
 * Retorna o endereço do vetor de filmes assistidos
 * @param  usuario Usuário a ser lido
 * @return         Endereço do vetor de bool de filmes assistidos
 */
bool *ObterAssistidos(Usuario *usuario);

/**
 * Calcula a similaridade de Jaccard entre dois usuários:
 * itens(A interseção B)/itens(A união B)
 * @param  a         Primeiro usuário
 * @param  b         Segundo usuário
 * @param  numfilmes Número de filmes da base de dados
 * @return           Valor da similaridade de Jaccard entre a e b
 */
double Jaccard(Usuario *a, Usuario *b, int numfilmes);

/**
 * Adiciona um novo usuário ao final da lista de usuários. É preciso passar
 * o endereço da lista de filmes assistidos, alocada externamente.
 * @param  lista      Lista de usuários
 * @param  user_id    ID do novo usuário
 * @param  assistidos Endereço da lista de assistidos do novo u²suário
 * @return            Endereço do novo usuário
 */
Usuario *AdicionarUsuario(Lista *lista, int user_id, bool *assistidos);

/**
 * Retorna o endereço do usuário de ID user_id, ou NULL, caso não haja tal
 * usuário.
 * @param  lista   Lista de usuários
 * @param  user_id ID do usuário procurado
 * @return         Endereço do usuário (ou NULL, caso não seja encontrado)
 */
Usuario *BuscarUsuarioPorID(Lista *lista, int user_id);

#endif