#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arquivo.h"
#include "Sugestoes.h"
#include "Lista.h"
#include "Usuario.h"
#include "Filme.h"
#include "HashTable_ABB.h"

#define BUFFER_INPUT_TAM 256
#define BUFFER_OUTPUT_TAM 256
#define ENDERECO_TAM 64

#define DEBUG 1 // Remover isso e o resto das gambiarras antes de enviar o trabalho

void ImprimirAltasParada(void *dados){
    Filme *filme = (Filme*)dados;
    printf("%d - %s\n", filme->movie_id, filme->titulo);
}

int main(int argc, char const *argv[])
{
    // Checa parâmetros de chamada do programa
    if (argc < 3){
        fprintf(stderr, "ERRO: Numero insuficiente de argumentos na chamada do programa.\nSintaxe correta: TP2.exe <entrada> <saida>.\n");
        exit(1);
    }

    FILE *arq_input = fopen(argv[1], "r"); // Arquivo de entrada
    if (arq_input == NULL){
        fprintf(stderr, "ERRO: Falha na abertura do arquivo de entrada %s.\n", argv[1]);
        exit(1);
    }

    FILE *arq_output = fopen(argv[2], "w"); // Arquivo de saída
    if (arq_output == NULL){
        fprintf(stderr, "ERRO: Falha na abertura do arquivo de saida %s.\n", argv[2]);
        exit(1);
    }

    // Interpreta a primeira linha do arquivo de entrada, que contém os endere-
    // ços, o número de recomendações e o tamanho da hash
    char input_buffer[BUFFER_INPUT_TAM];
    fgets(input_buffer, BUFFER_INPUT_TAM-1, arq_input);
    
    char endereco_metadata[ENDERECO_TAM], endereco_ratings[ENDERECO_TAM];
    int num_recomendacoes, tamanho_hash;
    char *pch;

    pch = strtok(input_buffer, "\t");
    strcpy(endereco_metadata, pch);

    pch = strtok(NULL, "\t");
    strcpy(endereco_ratings, pch);

    pch = strtok(NULL, "\t");
    num_recomendacoes = atoi(pch);

    pch = strtok(NULL, "\t");
    tamanho_hash = atoi(pch);

    fgetc(arq_input); // Processa a linha em branco (segunda linha do arq_input)

    // Imprime a primeira linha no arquivo de saída
    fprintf(arq_output, "%s\t%s\t%d\t%d\n\n", endereco_metadata, endereco_ratings,
        num_recomendacoes, tamanho_hash);

    // Lê arquivos de avaliações e metadados e preenche as listas
    Lista *usuarios = Arquivo_LerListaDeUsuarios(endereco_ratings);
    Lista *filmes = Arquivo_LerListaDeFilmes(endereco_metadata);

    if (usuarios == NULL || filmes == NULL){
        fprintf(stderr, "ERRO: Falha na leitura da base de dados de usuarios ou filmes.\n");
        exit(1);
    }

    if (DEBUG){
        int num_filmes = Lista_ObterTamanho(filmes), num_usuarios = Lista_ObterTamanho(usuarios);
        printf("Numero de usuarios = %d\nNumero de filmes = %d\n", num_usuarios, num_filmes);
    }
    
    ///////////////
    // Sugestões //
    ///////////////
    
    // Gera hash table de sugestões por popularidade

    int *chaves_popularidade = malloc(sizeof(int) * num_filmes);
    HashTable_ABB *popularidade = Sugestoes_Popularidade(usuarios, filmes, tamanho_hash, &chaves_popularidade);

    if (popularidade == NULL){
        fprintf(stderr, "ERRO: Falha na geracao de sugestoes por popularidade.\n");
        exit(1);
    }

    if (DEBUG){
        ABBusca *arvore = HashTable_ABB_ObterABBusca(popularidade, 5);
        printf("pop->tam: %d\n", popularidade->tam);
        printf("%p\n", arvore->raiz);
        ABBusca_OrdemCentral(arvore->raiz, ImprimirAltasParada);
    }
    
    while (fgets(input_buffer, BUFFER_INPUT_TAM-1, arq_input) != NULL){
        int user_id = atoi(input_buffer);

        // Busca por usuário na lista de usuários
        Nodo *nodo_atual = Lista_ObterCabeca(usuarios);
        while ((nodo_atual = Nodo_ObterProx(nodo_atual)) != NULL &&
            Usuario_ObterID((Usuario *)(Nodo_ObterDados(nodo_atual))) != user_id);

        if (nodo_atual == NULL)
            fprintf(stderr, "ERRO: Usuario de id %d nao existe na base de dados\n", user_id);
        else {
            // Imprimir sugestão por popularidade (placeholder)

            HashTable_ABB *similaridade = Sugestoes_Similaridade(usuarios, (Usuario *)Nodo_ObterDados(nodo_atual), tamanho_hash);

            // Imprimir sugestão por similaridade (placeholder)
            if (DEBUG){
                printf("UserID = %d\nEndereco da hash table = %p\n", user_id, similaridade);
            }
        }
    }

    // Encerramento dos arquivos de entrada e saída.
    fclose(arq_input);
    fclose(arq_output);
    return 0;
}