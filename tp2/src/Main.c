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

#define DEBUG 0 // Remover isso e o resto das gambiarras antes de enviar o trabalho

void ImprimirAltasParada(void *dados){
    Wrapper_Popularidade *wrapper = (Wrapper_Popularidade *)dados;
    printf("%d - %s\n", wrapper->filme->movie_id, wrapper->filme->titulo);
}

void ImprimirAltasParadaAlt(void *dados){
    Wrapper_Similaridade *wrapper = (Wrapper_Similaridade *)dados;
    printf("%d - %s\nJaccard: %f\n", wrapper->filme->movie_id, wrapper->filme->titulo, (float)(wrapper->jaccard.num)/(wrapper->jaccard.den));
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

    ///////////////////////////
    // Leitura de parâmetros //
    ///////////////////////////
    
    // Interpreta a primeira linha do arquivo de entrada, que contém os endere-
    // ços, o número de recomendações e o tamanho da hash
    char input_buffer[BUFFER_INPUT_TAM];
    fgets(input_buffer, BUFFER_INPUT_TAM-1, arq_input);
    
    char endereco_metadata[ENDERECO_TAM], endereco_ratings[ENDERECO_TAM];
    int num_sugestoes, tamanho_hash;
    char *pch;

    pch = strtok(input_buffer, "\t");
    strcpy(endereco_metadata, pch);

    pch = strtok(NULL, "\t");
    strcpy(endereco_ratings, pch);

    pch = strtok(NULL, "\t");
    num_sugestoes = atoi(pch);

    pch = strtok(NULL, "\t");
    tamanho_hash = atoi(pch);

    fgetc(arq_input); // Processa a linha em branco (segunda linha do arq_input)

    // Imprime a primeira linha no arquivo de saída
    fprintf(arq_output, "%s\t%s\t%d\t%d\n\n", endereco_metadata, endereco_ratings,
        num_sugestoes, tamanho_hash);

    ///////////////////////////////
    // Leitura de bases de dados //
    ///////////////////////////////

    // Lê arquivos de avaliações e metadados e preenche as listas
    Lista *usuarios = Arquivo_LerListaDeUsuarios(endereco_ratings);
    Lista *filmes = Arquivo_LerListaDeFilmes(endereco_metadata);

    if (usuarios == NULL || filmes == NULL){
        fprintf(stderr, "ERRO: Falha na leitura da base de dados de usuarios ou filmes.\n");
        exit(1);
    }

    int num_filmes = Lista_ObterTamanho(filmes),
        num_usuarios = Lista_ObterTamanho(usuarios);

    if (DEBUG){
        printf("Numero de usuarios = %d\nNumero de filmes = %d\n", num_usuarios, num_filmes);
    }

    if (DEBUG){
        Nodo *nodo_atual = Lista_ObterPrimeiro(filmes);
        while (nodo_atual != NULL){
            Filme *filme_atual = (Filme *)Nodo_ObterDados(nodo_atual);
            printf("ID: %d | Titulo: %s\n", filme_atual->movie_id, filme_atual->titulo);
            nodo_atual = Nodo_ObterProx(nodo_atual);
        }
        printf("Fim\n");
    }
    
    ///////////////
    // Sugestões //
    ///////////////
    
    // Gera hash table de sugestões por popularidade

    int *chaves_popularidade;
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
    
    // Itera pelos usuários especificados no arquivo de entrada
    while (fgets(input_buffer, BUFFER_INPUT_TAM-1, arq_input) != NULL){
        int user_id = atoi(input_buffer);

        if (DEBUG){
            printf("\nUsuario %d\n", user_id);
        }

        // Busca por usuário na lista de usuários
        Nodo *nodo_atual = Lista_ObterCabeca(usuarios);
        while ((nodo_atual = Nodo_ObterProx(nodo_atual)) != NULL &&
            Usuario_ObterID((Usuario *)(Nodo_ObterDados(nodo_atual))) != user_id);

        if (nodo_atual == NULL)
            fprintf(stderr, "ERRO: Usuario de id %d nao existe na base de dados\n", user_id);
        else {
            Usuario *usuario_atual = (Usuario *)Nodo_ObterDados(nodo_atual);

            fprintf(arq_output, "%d:\nMost popular\n", user_id);

            Sugestoes_ImprimirPopularidade(popularidade, chaves_popularidade,
                num_filmes, usuario_atual, num_sugestoes, arq_output);

            Racional *chaves_similaridade; // tamanho: usuarios->tam - 1
            HashTable_ABB *similaridade = Sugestoes_Similaridade(usuarios, filmes, (Usuario *)Nodo_ObterDados(nodo_atual), tamanho_hash, &chaves_similaridade);

            if (DEBUG){
                int i = 0;
                printf("Chaves:\n");
                while (i < num_usuarios - 1){
                    printf("%d/%d\n", chaves_similaridade[i].num, chaves_similaridade[i].den);
                    i++;
                }
            }

            fprintf(arq_output, "\n\nPersonalizada\n");

            Sugestoes_ImprimirSimilaridade(similaridade, chaves_similaridade,
                num_usuarios - 1, usuario_atual, num_sugestoes, num_filmes, arq_output);
            
            fprintf(arq_output, "\n\n");

            if (DEBUG){
                printf("UserID = %d\nEndereco da hash table = %p\n", user_id, similaridade);
                int i;
                for (i = 0; i < tamanho_hash; i++){
                    ABBusca *arvore = HashTable_ABB_ObterABBusca(similaridade, i);
                    if (arvore->raiz != NULL){
                        printf("Arvore #%d\t", i);
                        printf("Endereco da raiz: %p\n", arvore->raiz);
                        ABBusca_OrdemCentral(arvore->raiz, ImprimirAltasParadaAlt);
                    }
                }
            }

            HashTable_ABB_Destruir(similaridade, NULL);
            free(chaves_similaridade);
        }
    }

    free(chaves_popularidade);
    HashTable_ABB_Destruir(popularidade, NULL);

    Lista_Destruir(filmes, Filme_DestruirAux);
    Lista_Destruir(usuarios, Usuario_DestruirAux);

    // Encerramento dos arquivos de entrada e saída.
    fclose(arq_input);
    fclose(arq_output);
    return 0;
}