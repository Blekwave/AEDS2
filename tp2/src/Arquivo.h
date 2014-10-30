#ifndef _ARQUIVO_H_
#define _ARQUIVO_H_

#include "Lista.h"

/**
 * Preenche uma lista encadeada com os usuários lidos de um arquivo.
 * @param  end   Endereço do arquivo a ser lido.
 * @return       Endereço da lista encadeada inicializada (ou NULL)
 */
Lista *Arquivo_LerListaDeUsuarios(char *end);

/**
 * Preenche uma lista encadeada com os filmes lidos de um arquivo.
 * @param  end   Endereço do arquivo a ser lido.
 * @return       Endereço da lista encadeada inicializada (ou NULL)
 */
Lista *Arquivo_LerListaDeFilmes(char *end);

/**
 * Libera a memória da lista de usuários e das estruturas auxiliares.
 * @param lista Lista a ser destruida.
 */
void Arquivo_DestruirListaDeUsuarios(Lista *lista);

/**
 * Libera a memória da lista de filmes e das estruturas auxiliares.
 * @param lista Lista a ser destruida.
 */
void Arquivo_DestruirListaDeFilmes(Lista *lista);

#endif
