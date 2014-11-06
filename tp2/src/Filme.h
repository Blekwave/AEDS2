#ifndef _FILME_H_
#define _FILME_H_

typedef struct {
    int movie_id;
    char *titulo;
    int imdb_id;
    int ano;
} Filme;

/**
 * Inicializa um filme com os dados fornecidos.
 * @param filme         Endereço do filme a ser inicializado.
 * @param movie_id      ID do filme.
 * @param titulo        Título do filme.
 * @param imdb_id       ID do filme no IMDB.
 * @param ano           Ano de lançamento do filme.
 */
Filme *Filme_Inicializar(int movie_id, char *titulo, int imdb_id, int ano);

/**
 * Libera a memória utilizada pelos elementos do filme
 * (O título é o único elemento alocado dinamicamente, no caso)
 * @param filme Filme a ser destruído
 */
void Filme_Destruir(Filme *filme);

/**
 * Função auxiliar para destruir filme. Construída para ser usada em conjunto
 * com as funções de destruir lista.
 * @param dados Endereço do usuário.
 */
void Filme_DestruirAux(void *dados);

/**
 * Retorna o ano de lançamento do filme
 * @param  filme Filme
 * @return       Ano de lançamento do filme
 */
int Filme_ObterAno(Filme *filme);

/**
 * Retorna o título do filme
 * @param  filme Filme
 * @return       Endereço do título do filme
 */
char *Filme_ObterTitulo(Filme *filme);

/**
 * Retorna o IMDB ID do filme
 * @param  filme Filme
 * @return       IMDB ID do filme
 */
int Filme_ObterIMDBID(Filme *filme);

/**
 * Retorna o Movie ID do filme
 * @param  filme Filme
 * @return       Movie ID do filme
 */
int Filme_ObterMovieID(Filme *filme);

#endif