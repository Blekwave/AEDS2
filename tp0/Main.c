#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Filme.h"
#include "Usuarios.h"
#include "Sugestoes.h"
#include "Arquivo.h"

#define BUFFER_TAMANHO 256
#define USER_ID_TAMANHO 11
#define NUM_SUGESTOES 3
#define INPUT_ENDERECO "input.txt"
#define OUTPUT_ENDERECO "output.txt"

int main(int argc, char const *argv[])
{
    FILE *input = fopen(INPUT_ENDERECO, "r");
    if (input == NULL){
        printf("Falha ao abrir arquivo de entrada %s.\n", INPUT_ENDERECO);
        exit(1);
    }
    FILE *output = fopen(OUTPUT_ENDERECO, "w");
    if (input == NULL){
        printf("Falha ao abrir arquivo de saida %s.\n", OUTPUT_ENDERECO);
        exit(1);
    }

    char usuarios_endereco[BUFFER_TAMANHO], filmes_endereco[BUFFER_TAMANHO], buffer[BUFFER_TAMANHO];
    char *pch;
    fgets(buffer, BUFFER_TAMANHO, input);
    pch = strtok(buffer, "\t\n");
    strcpy(filmes_endereco, pch);
    pch = strtok(NULL, "\t\n");
    strcpy(usuarios_endereco, pch);

    int numfilmes = ObterNumFilmes(usuarios_endereco);
    Lista *usuarios = LerUsuarios(usuarios_endereco, numfilmes);
    Filme *filmes = LerFilmes(filmes_endereco, numfilmes);

    if (numfilmes == -1 || usuarios == NULL || filmes == NULL){
        printf("Falha na leitura das bases de dados indicadas.\n");
    } else {
        fprintf(output, "%s\t%s\n\n", filmes_endereco, usuarios_endereco);
    }

    // Sugestões por popularidade
    int *populares = SugestaoPorPopularidade(usuarios, filmes, numfilmes, NUM_SUGESTOES);
    fprintf(output,"Most popular\n");
    int i;
    for (i = 0; i < NUM_SUGESTOES; i++)
        fprintf(output, "%s%c", ObterTitulo(filmes[populares[i]]), i == NUM_SUGESTOES - 1 ? '\n' : '\t' );
    free(populares);

    // Sugestões personalizadas
    int *similaridade, user_id;
    fprintf(output, "\nPersonalizada\n");

    fgetc(input); // Descarta linha em branco (segunda linha do input.txt)
    do {
        fgets(buffer, BUFFER_TAMANHO, input);
        user_id = atoi(buffer);
        similaridade = SugestaoPorSimilaridade(usuarios, filmes, numfilmes, NUM_SUGESTOES, user_id);
        if (similaridade == NULL)
            fprintf(stderr, "ERRO: Nao foi possivel encontrar um usuario similar a %d\n", user_id);
        else {
            fprintf(output, "%d: ", user_id);
            for (i = 0; i < NUM_SUGESTOES && similaridade[i] != -1; i++)
                fprintf(output, "%s%c", ObterTitulo(filmes[similaridade[i]]), (i == NUM_SUGESTOES - 1) || (similaridade[i+1] == -1) ? '\n' : '\t' );
            if (i == 0) // Nenhuma recomendação foi feita, portanto não houve quebra de linha
                fprintf(output, "\n");
            free(similaridade);
        }
    } while (!feof(input));

    DestruirListaDeFilmes(filmes, numfilmes);
    DestruirListaDeUsuarios(usuarios);

    fclose(input);
    fclose(output);
    return 0;
}