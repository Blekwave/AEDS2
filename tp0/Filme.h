#ifndef _FILME_H_
#define _FILME_H_

typedef struct {
    int movie_id;
    char *titulo;
    int imdb_id;
    int ano;
} Filme;

void InicializarFilme(Filme *filme, int movie_id, char *titulo, int imdb_id, int ano);
void DestruirFilme(Filme filme);
int ObterAno(Filme filme);
char *ObterTitulo(Filme filme);
int ObterIMDBId(Filme filme);
int ObterMovieID(Filme filme);


#endif