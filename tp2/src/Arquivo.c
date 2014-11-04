#include "Arquivo.h"
#include "Lista.h"
#include "Usuario.h"
#include "Filme.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_USUARIO_TAM 1024
#define BUFFER_FILME_TAM 128
#define BUFFER_TITULO_TAM 128

/**
 * Preenche uma lista encadeada com os usuários lidos de um arquivo.
 * @param  end   Endereço do arquivo a ser lido.
 * @return       Endereço da lista encadeada inicializada (ou NULL)
 */
Lista *Arquivo_LerListaDeUsuarios(char *end){
    FILE *arq = fopen(end, "r");
    if (arq == NULL)
        return NULL;

    // Buffers de leitura
    char buffer[BUFFER_USUARIO_TAM], *pch;
    Usuario *usuario;
    int *filme_temp;

    Lista *lista = Lista_Inicializar();

    // fgets retorna NULL em EOF
    while (fgets(buffer, BUFFER_USUARIO_TAM - 1, arq) != NULL){
        pch = strtok(buffer, " ");
        usuario = Usuario_Inicializar(atoi(pch), 0, NULL);
        while ((pch = strtok(NULL, " ")) != NULL){
            filme_temp = (int *)malloc(sizeof(int));
            *filme_temp = atoi(pch);
            Lista_AdicionarAoFinal(usuario->assistidos, (void *)filme_temp);
        }
        Lista_AdicionarAoFinal(lista, (void *)usuario);
    }

    fclose(arq);
    return lista;
}

/**
 * Preenche uma lista encadeada com os filmes lidos de um arquivo.
 * @param  end   Endereço do arquivo a ser lido.
 * @return       Endereço da lista encadeada inicializada (ou NULL)
 */
Lista *Arquivo_LerListaDeFilmes(char *end){
    FILE *arq = fopen(end, "r");
    if (arq == NULL)
        return NULL;

    // Buffers de leitura
    char buffer[BUFFER_FILME_TAM], titulo[BUFFER_TITULO_TAM], *pch;
    Filme *filme;
    int movie_id, imdb_id, ano;

    Lista *lista = Lista_Inicializar();

    // fgets retorna NULL em EOF
    while (fgets(buffer, BUFFER_FILME_TAM - 1, arq) != NULL){
        movie_id = atoi(strtok(buffer, "\t"));
        strcpy(titulo, strtok(NULL, "\t"));
        imdb_id = atoi(strtok(buffer, "\t"));
        ano = atoi(strtok(buffer, "\t"));

        filme = Filme_Inicializar(movie_id, titulo, imdb_id, ano, 0);
        Lista_AdicionarAoFinal(lista, (void *)filme);
    }

    fclose(arq);
    return lista;
}

/**
 * Libera a memória da lista de usuários e das estruturas auxiliares.
 * @param lista Lista a ser destruida.
 */
void Arquivo_DestruirListaDeUsuarios(Lista *lista){
    Lista_Destruir(lista, Usuario_DestruirAux);
}

/**
 * Libera a memória da lista de filmes e das estruturas auxiliares.
 * @param lista Lista a ser destruida.
 */
void Arquivo_DestruirListaDeFilmes(Lista *lista){
    Lista_Destruir(lista, Filme_DestruirAux);
}