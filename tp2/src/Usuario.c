#include "Usuario.h"

/**
 * Aloca a memória e inicializa os elementos de um novo usuário. Inicializa a
 * lista de filmes assistidos (vazia).
 * @param  user_id    ID do usuário
 * @return            Endereço do novo usuário.
 */
Usuario *Usuario_Inicializar(int user_id){
    Usuario *novo = (Usuario *)malloc(sizeof(Usuario));
    novo->user_id = user_id;
    novo->assistidos = Ldenc_Inicializar();
    return novo;
}

/**
 * Libera a memória do usuário e da lista de filmes.
 * @param usuario Usuário a ser destruído
 */
void Usuario_Destruir(Usuario *usuario){
    Ldenc_Destruir(usuario->assistidos, NULL);
    free(usuario);
}

/**
 * Retorna o ID do usuário
 * @param  usuario Usuário a ser lido
 * @return         ID do usuário
 */
int Usuario_ObterID(Usuario *usuario){
    return usuario->user_id;
}

/**
 * Retorna o endereço da lista de filmes assistidos.
 * @param  usuario Usuário a ser lido.
 * @return         Endereço da lista de filmes assistidos.
 */
Ldenc *Usuario_ObterAssistidos(Usuario *usuario){
    return usuario->assistidos;
}