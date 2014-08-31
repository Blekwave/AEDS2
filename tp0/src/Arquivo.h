#ifndef _ARQUIVO_H_
#define _ARQUIVO_H_

/**
 * Obtém o número de filmes da base de dados
 * @param  endereco Endereço do arquivo de avaliações (*_ratings.txt)
 * @return          Número de filmes
 */
int ObterNumFilmes(char *endereco);

/**
 * Lê os dados dos filmes do arquivo de metadados
 * @param  endereco  Endereço do arquivo de metadados (*_metadata.txt)
 * @param  numfilmes Número de filmes da base de dados
 * @return           Ponteiro de Filme contendo um vetor de filmes de tamanho
 *                            numfilmes alocado dinamicamente.
 */
Filme *LerFilmes(char *endereco, int numfilmes);

/**
 * Lê os usuários e seus filmes assistidos do arquivo de avaliações
 * @param  endereco  Endereço do arquivo de avaliações (*_ratings.txt)
 * @param  numfilmes Número de filmes da base de dados
 * @return           Ponteiro de Lista contendo uma lista encadeada cujos nodos
 *                            contém os usuários lidos.
 */
Lista *LerUsuarios(char *endereco, int numfilmes);

/**
 * Libera a memória utilizada pela lista de filmes.
 * @param filmes    Vetor de Filme
 * @param numfilmes Número de filmes do vetor
 */
void DestruirListaDeFilmes(Filme *filmes, int numfilmes);

/**
 * Libera a memória utilizada pela lista encadeada de usuários e pelos usuários
 * armazenados na lista.
 * @param lista Lista encadeada contendo usuários
 */
void DestruirListaDeUsuarios(Lista *lista);

#endif