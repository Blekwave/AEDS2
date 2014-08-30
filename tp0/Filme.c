#include "Filme.h"
#include <string.h>
#include <stdlib.h>

void InicializarFilme(Filme *filme, int movie_id, char *titulo, int imdb_id, int ano){
    filme->movie_id = movie_id;
    filme->titulo = (char *)malloc(strlen(titulo)+1);
    strcpy(filme->titulo, titulo);
    filme->imdb_id = imdb_id;
    filme->ano = ano;
}

void DestruirFilme(Filme filme){
    free(filme.titulo);
}

int ObterAno(Filme filme){
    return filme.ano;
}

char *ObterTitulo(Filme filme){
    return filme.titulo;
}

int ObterIMDBId(Filme filme){
    return filme.imdb_id;
}

int ObterMovieID(Filme filme){
    return filme.movie_id;
}