#ifndef _SUGESTOES_H_
#define _SUGESTOES_H_

/**
 * Obtém sugestões de filme com base no número de visualizações de cada filme.
 * @param  usuarios     Lista encadeada com nodos cujos dados são usuários
 * @param  filmes       Vetor de filmes
 * @param  numfilmes    Número de filmes da base de dados
 * @param  numsugestoes Número de sugestões a serem feitas
 * @return              Vetor de inteiros de tamanho numsugestoes com o índice
 *                            no vetor de filmes dos filmes sugeridos.
 */
int *SugestaoPorPopularidade(Lista *usuarios, Filme *filmes, int numfilmes, int numsugestoes);

/**
 * Descobre por meio da similaridade de Jaccard o usuário mais similar a um
 * usuário especificado.
 * @param  usuarios  Lista de usuários
 * @param  numfilmes Número de filmes da base de dados
 * @param  user_id   ID do usuário ao qual se quer encontrar um usuário similar
 * @return           Endereço do usuário mais similar ao usuário de ID user_id
 */
Usuario *ObterUsuarioMaisSimilar(Lista *usuarios, int numfilmes, int user_id);

/**
 * Preenche a lista de saída da função de sugestão por similaridade com os fil-
 * mes mais recentes assistidos pelo usuário mais similar.
 * @param filmes       Vetor de filmes
 * @param saida        Lista de saída (vetor de int) alocada (porém vazia)
 * @param usuario      Usuário do qual serão selecionados os filmes
 * @param numfilmes    Número de filmes da base de dados
 * @param numsugestoes Número de sugestões a serem realizadas.
 */
void SelecionarFilmesMaisRecentes(Filme *filmes, int *saida, Usuario *usuario, int numfilmes, int numsugestoes);

/**
 * Obtém sugestões de filme com base na similaridade entre um usuário especifi-
 * cado e outro usuário da lista.
 * @param  usuarios     Lista de usuários
 * @param  filmes       Vetor de filmes
 * @param  numfilmes    Número de filmes da base de dados
 * @param  numsugestoes Número de sugestões a serem realizadas
 * @param  user_id      ID do usuário ao qual se quer encontrar um usuário simi-
 *                      lar
 * @return              Vetor de inteiros de tamanho numsugestoes com o índice
 *                            no vetor de filmes dos filmes sugeridos.
 */
int *SugestaoPorSimilaridade(Lista *usuarios, Filme *filmes, int numfilmes, int numsugestoes, int user_id);

#endif