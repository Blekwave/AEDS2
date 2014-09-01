#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Filme.h"
#include "Usuario.h"

#define BUFFER_TAMANHO 256
#define USER_ID_TAMANHO 11

// char *endereco: endereço da lista de USUÁRIOS
int ObterNumFilmes(char *endereco){
    char ch;
    FILE *arquivo = fopen(endereco, "r");
    if (arquivo == NULL)
        return -1;
    int contagem = 0;
    // Conta número de tabs em uma linha para descobrir o número de filmes listados
    while ((ch = fgetc(arquivo)) != '\n')
        if (ch == '\t')
            contagem++;
    fclose(arquivo);
    return contagem;
}

Filme *LerFilmes(char *endereco, int numfilmes){
    FILE *arquivo = fopen(endereco, "r");
    if (arquivo == NULL)
        return NULL;
    Filme *filmes = (Filme *)malloc(sizeof(Filme)*numfilmes);
    char buffer[BUFFER_TAMANHO], titulo[BUFFER_TAMANHO];
    char *pch;
    int movie_id, ano, imdb_id, i;
    for (i = 0; i < numfilmes; i++){
        fgets(buffer, BUFFER_TAMANHO, arquivo);
        pch = strtok(buffer, "\t\n");
        movie_id = atoi(pch);
        pch = strtok(NULL, "\t\n");
        strcpy(titulo, pch);
        pch = strtok(NULL, "\t\n");
        imdb_id = atoi(pch);
        pch = strtok(NULL, "\t\n");
        ano = atoi(pch);
        InicializarFilme(&filmes[i], movie_id, titulo, imdb_id, ano);
    }
    fclose(arquivo);
    return filmes;
}

void DestruirListaDeFilmes(Filme *filmes, int numfilmes){
    int i;
    for (i = 0; i < numfilmes; i++)
        DestruirFilme(filmes[i]);
    free(filmes);
}

void DestruirListaDeUsuarios(Lista *lista){
    // O comportamento do cast de ponteiro de função não é definido no caso abaixo, na teoria
    // Na prática, não deve haver grandes problemas, suponho. Isso é complicado.
    DestruirLista(lista, (void(*)(void *))DestruirUsuario);
}

Lista *LerUsuarios(char *endereco, int numfilmes){
    FILE *arquivo = fopen(endereco, "r");
    if (arquivo == NULL)
        return NULL;
    Lista *lista = InicializarLista();
    int buffer_tamanho = 2 + USER_ID_TAMANHO + numfilmes * 2; //\n + \0 + user_id + \t e bool para cada filme
    char *buffer = (char *)malloc(sizeof(char)*buffer_tamanho);
    char *pch;
    int user_id, i;
    bool *assistidos;
    while (fgets(buffer, buffer_tamanho, arquivo) != NULL){
        pch = strtok(buffer, "\t\n");
        user_id = atoi(pch);
        pch = strtok(NULL, "\t\n");
        if (pch != NULL){ // Importante para evitar usuário extra pela leitura da linha em branco no final do arquivo
            assistidos = (bool *) malloc(sizeof(bool)*numfilmes);
            for (i = 0; pch != NULL; i++){
                assistidos[i] = atoi(pch);
                pch = strtok(NULL, "\t\n");
            }
            AdicionarUsuario(lista, user_id, assistidos);
        }
    }
    fclose(arquivo);
    free(buffer);
    return lista;
}