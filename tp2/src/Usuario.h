#ifndef _USUARIO_H_
#define _USUARIO_H_

#include "Ldenc.h"

typedef struct {
    int user_id;
    Ldenc *assistidos;
} Usuario;

/**
 * Aloca a memória e inicializa os elementos de um novo usuário. Inicializa a
 * lista de filmes assistidos (vazia).
 * @param  user_id    ID do usuário.
 * @return            Endereço do novo usuário.
 */
Usuario *Usuario_Inicializar(int user_id);

/**
 * Libera a memória do usuário e da lista de filmes.
 * @param usuario Usuário a ser destruído
 */
void Usuario_Destruir(Usuario *usuario);

/**
 * Retorna o ID do usuário.
 * @param  usuario Usuário a ser lido.
 * @return         ID do usuário.
 */
int Usuario_ObterID(Usuario *usuario);

/**
 * Retorna o endereço da lista de filmes assistidos.
 * @param  usuario Usuário a ser lido.
 * @return         Endereço da lista de filmes assistidos.
 */
Ldenc *Usuario_ObterAssistidos(Usuario *usuario);

#endif
