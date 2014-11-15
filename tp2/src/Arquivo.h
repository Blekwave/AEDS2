#ifndef _ARQUIVO_H_
#define _ARQUIVO_H_

#include "Lista.h"

/**
 * Preenche uma lista encadeada com os usuários lidos de um arquivo.
 * @param  end        Endereço do arquivo a ser lido.
 * @param  num_filmes Número de elementos da base de dados de filmes.
 * @return            Endereço da lista encadeada inicializada. (ou NULL)
 */
Lista *Arquivo_LerListaDeUsuarios(char *end, int num_filmes);

/**
 * Preenche uma lista encadeada com os filmes lidos de um arquivo.
 * @param  end   Endereço do arquivo a ser lido.
 * @return       Endereço da lista encadeada inicializada. (ou NULL)
 */
Lista *Arquivo_LerListaDeFilmes(char *end);

#endif
