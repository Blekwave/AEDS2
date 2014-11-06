#include "Filme.h"
#include <string.h>
#include <stdlib.h>

/**
 * Inicializa um filme com os dados fornecidos.
 * @param filme         Endereço do filme a ser inicializado.
 * @param movie_id      ID do filme.
 * @param titulo        Título do filme.
 * @param imdb_id       ID do filme no IMDB.
 * @param ano           Ano de lançamento do filme.
 */
Filme *Filme_Inicializar(int movie_id, char *titulo, int imdb_id, int ano){
    Filme *filme = (Filme *)malloc(sizeof(Filme));
    filme->movie_id = movie_id;
    filme->titulo = (char *)malloc(strlen(titulo)+1);
    strcpy(filme->titulo, titulo);
    filme->imdb_id = imdb_id;
    filme->ano = ano;
    return filme;
}

/**
 * Libera a memória utilizada pelos elementos do filme
 * (O título é o único elemento alocado dinamicamente, no caso)
 * @param filme Filme a ser destruído
 */
void Filme_Destruir(Filme *filme){
    free(filme->titulo);
    free(filme);
}

/**
 * Função auxiliar para destruir filme. Construída para ser usada em conjunto
 * com as funções de destruir lista.
 * @param dados Endereço do usuário.
 */
void Filme_DestruirAux(void *dados){
    free(((Filme *)dados)->titulo);
}

/**
 * Retorna o ano de lançamento do filme
 * @param  filme Filme
 * @return       Ano de lançamento do filme
 */
int Filme_ObterAno(Filme *filme){
    return filme->ano;
}

/**
 * Retorna o título do filme
 * @param  filme Filme
 * @return       Endereço do título do filme
 */
char *Filme_ObterTitulo(Filme *filme){
    return filme->titulo;
}

/**
 * Retorna o IMDB ID do filme
 * @param  filme Filme
 * @return       IMDB ID do filme
 */
int Filme_ObterIMDBID(Filme *filme){
    return filme->imdb_id;
}

/**
 * Retorna o Movie ID do filme
 * @param  filme Filme
 * @return       Movie ID do filme
 */
int Filme_ObterMovieID(Filme *filme){
    return filme->movie_id;
}