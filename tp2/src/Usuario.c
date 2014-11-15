#include "Usuario.h"
#include <stdlib.h>

/**
 * Aloca a memória e inicializa os elementos de um novo usuário.
 * @param  user_id    ID do usuário.
 * @param  assistidos Endereço da lista de filmes assistidos.
 * @return            Endereço do novo usuário.
 */
Usuario *Usuario_Inicializar(int user_id, BitString *assistidos){
    Usuario *novo = (Usuario *)malloc(sizeof(Usuario));
    novo->user_id = user_id;
    novo->assistidos = assistidos;
    return novo;
}

/**
 * Libera a memória do usuário e da lista de filmes.
 * @param usuario Usuário a ser destruído
 */
void Usuario_Destruir(Usuario *usuario){
    BitString_Destruir(usuario->assistidos);
    free(usuario);
}

/**
 * Função auxiliar para destruir usuário. Construída para ser usada em conjunto
 * com as funções de destruir lista. Libera apenas a memória da lista de filmes.
 * @param dados Endereço do usuário.
 */
void Usuario_DestruirAux(void *dados){
    BitString_Destruir(((Usuario *)dados)->assistidos);
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
BitString *Usuario_ObterAssistidos(Usuario *usuario){
    return usuario->assistidos;
}