#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arquivo.h"
#include "Sugestoes.h"
#include "Lista.h"
#include "Usuario.h"
#include "Filme.h"
#include "HashTable_ABB.h"
#include "Racional.h"

#define BUFFER_INPUT_TAM 256
#define BUFFER_OUTPUT_TAM 256
#define ENDERECO_TAM 64

int main(int argc, char const *argv[])
{
    // Checa parâmetros de chamada do programa
    if (argc < 3)
    {
        fprintf(stderr, "ERRO: Numero insuficiente de argumentos na chamada do programa.\nSintaxe correta: TP2.exe <entrada> <saida>.\n");
        exit(1);
    }

    FILE *arq_input = fopen(argv[1], "r"); // Arquivo de entrada
    if (arq_input == NULL)
    {
        fprintf(stderr, "ERRO: Falha na abertura do arquivo de entrada %s.\n", argv[1]);
        exit(1);
    }

    FILE *arq_output = fopen(argv[2], "w"); // Arquivo de saída
    if (arq_output == NULL)
    {
        fprintf(stderr, "ERRO: Falha na abertura do arquivo de saida %s.\n", argv[2]);
        exit(1);
    }

    ///////////////////////////
    // Leitura de parâmetros //
    ///////////////////////////
    
    // Interpreta a primeira linha do arquivo de entrada, que contém os endere-
    // ços, o número de recomendações e o tamanho da hash
    char input_buffer[BUFFER_INPUT_TAM];
    fgets(input_buffer, BUFFER_INPUT_TAM-1, arq_input);
    
    char endereco_metadata[ENDERECO_TAM], endereco_ratings[ENDERECO_TAM];

    strcpy(endereco_metadata, strtok(input_buffer, "\t"));
    strcpy(endereco_ratings, strtok(NULL, "\t"));
    int num_sugestoes = atoi(strtok(NULL, "\t"));
    int tamanho_hash = atoi(strtok(NULL, "\t"));

    fgetc(arq_input); // Processa a linha em branco (segunda linha do arq_input)

    // Imprime a primeira linha no arquivo de saída
    fprintf(arq_output, "%s\t%s\t%d\t%d\n\n", endereco_metadata, 
        endereco_ratings, num_sugestoes, tamanho_hash);

    ///////////////////////////////
    // Leitura de bases de dados //
    ///////////////////////////////

    // Lê arquivos de avaliações e metadados e preenche as listas
    Lista *usuarios = Arquivo_LerListaDeUsuarios(endereco_ratings);
    Lista *filmes = Arquivo_LerListaDeFilmes(endereco_metadata);

    if (usuarios == NULL || filmes == NULL)
    {
        fprintf(stderr, "ERRO: Falha na leitura da base de dados de usuarios ou filmes.\n");
        exit(1);
    }

    int num_filmes = Lista_ObterTamanho(filmes),
        num_usuarios = Lista_ObterTamanho(usuarios);

    ///////////////
    // Sugestões //
    ///////////////
    
    // Obtém sugestões por popularidade
    int *chaves_popularidade;
    HashTable_ABB *popularidade = Sugestoes_Popularidade(usuarios, filmes, 
        tamanho_hash, &chaves_popularidade);
    
    // Itera pelos usuários especificados no arquivo de entrada
    while (fgets(input_buffer, BUFFER_INPUT_TAM-1, arq_input) != NULL){
        int user_id = atoi(input_buffer);

        // Busca por nodo correspondente na lista de usuários
        Nodo *nodo_atual = Lista_ObterCabeca(usuarios);
        while ((nodo_atual = Nodo_ObterProx(nodo_atual)) != NULL &&
            Usuario_ObterID((Usuario *)(Nodo_ObterDados(nodo_atual))) != user_id);

        if (nodo_atual == NULL){
            fprintf(stderr, "ERRO: Usuario de id %d nao existe na base de dados\n", user_id);
        }
        else { // Usuário encontrado, computa e imprime sugestões
            Usuario *usuario_atual = (Usuario *)Nodo_ObterDados(nodo_atual);

            // Imprime sugestões por popularidade
            fprintf(arq_output, "%d:\nMost popular\n", user_id);
            Sugestoes_ImprimirPopularidade(popularidade, chaves_popularidade,
                num_filmes, usuario_atual, num_sugestoes, arq_output);

            // Obtém sugestões por similaridade
            Racional *chaves_similaridade; // tamanho: usuarios->tam - 1
            HashTable_ABB *similaridade = Sugestoes_Similaridade(usuarios, filmes, (Usuario *)Nodo_ObterDados(nodo_atual), tamanho_hash, &chaves_similaridade);

            // Imprime sugestões por similaridade
            fprintf(arq_output, "\n\nPersonalizada\n");
            Sugestoes_ImprimirSimilaridade(similaridade, chaves_similaridade,
                num_usuarios - 1, usuario_atual, num_sugestoes, num_filmes, arq_output);
            fprintf(arq_output, "\n\n");

            HashTable_ABB_Destruir(similaridade, NULL);
            free(chaves_similaridade);
        }
    }

    HashTable_ABB_Destruir(popularidade, NULL);
    free(chaves_popularidade);

    Lista_Destruir(filmes, Filme_DestruirAux);
    Lista_Destruir(usuarios, Usuario_DestruirAux);

    // Encerramento dos arquivos de entrada e saída.
    fclose(arq_input);
    fclose(arq_output);
    return 0;
}