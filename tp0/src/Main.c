#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Filme.h"
#include "Usuario.h"
#include "Sugestoes.h"
#include "Arquivo.h"

#define BUFFER_TAMANHO 256
#define USER_ID_TAMANHO 11
#define NUM_SUGESTOES 3
#define INPUT_ENDERECO_DEFAULT "input.txt"
#define OUTPUT_ENDERECO_DEFAULT "output.txt"

int main(int argc, char const *argv[])
{
    char input_endereco[BUFFER_TAMANHO], output_endereco[BUFFER_TAMANHO];
    strcpy(input_endereco, argc >= 2 ? argv[1] : INPUT_ENDERECO_DEFAULT);
    strcpy(output_endereco, argc >= 3 ? argv[2] : OUTPUT_ENDERECO_DEFAULT);

    FILE *input = fopen(input_endereco, "r");
    if (input == NULL){
        fprintf(stderr,"Falha ao abrir arquivo de entrada %s.\n", input_endereco);
        exit(1);
    }
    FILE *output = fopen(output_endereco, "w");
    if (output == NULL){
        fprintf(stderr,"Falha ao abrir arquivo de saida %s.\n", output_endereco);
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
        fprintf(stderr,"Falha na leitura das bases de dados indicadas.\n");
        exit(1);
    } else {
        fprintf(output, "%s\t%s\n\n", filmes_endereco, usuarios_endereco);
    }

    // Sugestões por popularidade
    int *populares = SugestaoPorPopularidade(usuarios, filmes, numfilmes, NUM_SUGESTOES);
    fprintf(output,"Most popular\n");
    int i;
    for (i = 0; i < NUM_SUGESTOES; i++)
        fprintf(output, "%s%s", i == 0 ? "" : "\t", ObterTitulo(filmes[populares[i]]));
    fprintf(output, "\n");
    free(populares);

    // Sugestões personalizadas
    int *similaridade, user_id;
    fprintf(output, "\nPersonalizada\n");

    fgetc(input); // Descarta linha em branco (segunda linha do input.txt)
    while (fgets(buffer, BUFFER_TAMANHO, input) != NULL) {
        user_id = atoi(buffer);
        similaridade = SugestaoPorSimilaridade(usuarios, filmes, numfilmes, NUM_SUGESTOES, user_id);
        if (similaridade == NULL)
            fprintf(stderr, "ERRO: Nao foi possivel encontrar um usuario similar a %d\n", user_id);
        else {
            fprintf(output, "%d:", user_id);
            for (i = 0; i < NUM_SUGESTOES && similaridade[i] != -1; i++)
                fprintf(output, "\t%s", ObterTitulo(filmes[similaridade[i]]));
            fprintf(output, "\n");
            free(similaridade);
        }
    }

    DestruirListaDeFilmes(filmes, numfilmes);
    DestruirListaDeUsuarios(usuarios);

    fclose(input);
    fclose(output);
    return 0;
}