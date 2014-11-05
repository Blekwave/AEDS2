#ifndef _SUGESTOES_H_
#define _SUGESTOES_H_

#include "Lista.h"
#include "Usuario.h"
#include "HashTable_ABB.h"
#include <stdbool.h>

//////////////////////////////////////
// Funções auxiliares da hash table //
//////////////////////////////////////

////////////
// Filmes //
////////////

/**
 * Compara dois filmes a e b, retorna verdadeiro se a é maior que b, de acordo
 * com os critérios definidos no trabalho:
 * Nº de visualizações > Data de lançamento > Movie ID
 * @param  a Filme a ser comparado.
 * @param  b Filme a ser comparado.
 * @return   a > b
 */
bool Sugestoes_FilmeComparacao(void *a, void *b);

/**
 * Compara dois filmes a e b, retorna verdadeiro se a é igual a b. Isso é feito
 * comparando seus movie_ids, já que eles são chaves únicas.
 * @param  a Filme a ser comparado.
 * @param  b Filme a ser comparado.
 * @return   a == b
 */
bool Sugestoes_FilmeIgualdade(void *a, void *b);

/**
 * Retorna a posição na tabela hash em que um filme deve ser colocado.
 * @param  dados Endereço do filme.
 * @param  tam   Tamanho da tabela hash.
 * @return       Posição i, 0 <= i < tam, na qual o filme deve se localizar na
 *               tabela hash.
 */
int Sugestoes_FilmeHash(void *dados, int tam);

//////////////
// Usuarios //
//////////////

/**
 * Compara dois usuários a e b, retorna verdadeiro se a é maior que b, de acordo
 * com os critérios definidos no trabalho:
 * Coeficiente de Jaccard (chave) > User ID
 * @param  a Usuario a ser comparado.
 * @param  b Usuario a ser comparado.
 * @return   a > b
 */
bool Sugestoes_UsuarioComparacao(void *a, void *b);

/**
 * Compara dois usuarios a e b, retorna verdadeiro se a é igual a b. Isso é feito
 * comparando seus user_ids, já que eles são chaves únicas.
 * @param  a Usuario a ser comparado.
 * @param  b Usuario a ser comparado.
 * @return   a == b
 */
bool Sugestoes_UsuarioIgualdade(void *a, void *b);

/**
 * Retorna a posição na tabela hash em que um usuario deve ser colocado.
 * @param  dados Endereço do usuario.
 * @param  tam   Tamanho da tabela hash.
 * @return       Posição i, 0 <= i < tam, na qual o usuario deve se localizar na
 *               tabela hash.
 */
int Sugestoes_UsuarioHash(void *dados, int tam);

///////////////////////////////
// SUGESTÃO POR POPULARIDADE //
///////////////////////////////

/**
 * Gera um vetor de inteiros contendo as visualizações de cada filme, a partir
 * dos dados das listas de filmes visualizados por cada usuário.
 * @param  usuarios   Lista de usuários.
 * @param  num_filmes Número total de filmes.
 * @return            Endereço para o vetor de número de visualizações.
 */
int *Sugestoes_GerarVetorDeVisualizacoes(Lista *usuarios, int num_filmes);

/**
 * Inicializa, preenche e retorna uma hash table contendo as sugestões por po-
 * popularidade de filmes para um conjunto de usuários. Gera, também, um vetor
 * de chaves únicas ordenadas (através de passagem do endereço do ponteiro)
 * @param  usuarios      Lista de usuários
 * @param  filmes        Lista de filmes
 * @param  tamanho_hash  Tamanho da hash table a ser gerada.
 * @param  chaves        Endereço do ponteiro no qual o vetor de chaves deverá
 *                       ser criado.
 * @return               Endereço da hash table.
 */
HashTable_ABB *Sugestoes_Popularidade(Lista *usuarios, Lista *filmes, int tamanho_hash, int **chaves);

///////////////////////////////
// SUGESTÃO POR SIMILARIDADE //
///////////////////////////////

/**
 * Calcula o coeficiente de Jaccard entre dois usuários.
 * @param  usuario_a Endereço de um usuário.
 * @param  usuario_b Endereço de outro usuário.
 * @return   Coeficiente de Jaccard entre dois usuários.
 */
double Sugestoes_Jaccard(Usuario *usuario_a, Usuario *usuario_b);

/**
 * Inicializa, preenche e retorna uma hash table contendo as sugestões por simi-
 * laridade entre uma base de usuários e um usuário alvo. Gera, também, um vetor
 * de chaves únicas ordenadas (através de passagem do endereço do ponteiro)
 * @param  usuarios     Lista de usuários
 * @param  alvo         Usuário alvo
 * @param  tamanho_hash Tamanho da hash table
 * @return              Endereço da hash table
 */
HashTable_ABB *Sugestoes_Similaridade(Lista *usuarios, Usuario *alvo, int tamanho_hash);

#endif
