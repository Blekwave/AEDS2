#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arquivo.h"
#include "Sugestoes.h"
#include "Sugestoes_Impressao_IDs.h"
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
        fprintf(stderr, "ERRO: Numero insuficiente de argumentos na chamada do programa.\nSintaxe correta: Populares.exe <configuracoes> <num_sugestoes>.\n");
        exit(1);
    }

    FILE *arq_config = fopen(argv[1], "r"); // Arquivo de entrada
    if (arq_config == NULL)
    {
        fprintf(stderr, "ERRO: Falha na abertura do arquivo de entrada %s.\n", argv[1]);
        exit(1);
    }

    ///////////////////////////
    // Leitura de parâmetros //
    ///////////////////////////
    
    // Interpreta a primeira linha do arquivo de entrada, que contém os endere-
    // ços, o número de recomendações e o tamanho da hash
    char input_buffer[BUFFER_INPUT_TAM];
    fgets(input_buffer, BUFFER_INPUT_TAM-1, arq_config);
    
    char endereco_metadata[ENDERECO_TAM], endereco_ratings[ENDERECO_TAM];

    strcpy(endereco_metadata, strtok(input_buffer, "\t"));
    strcpy(endereco_ratings, strtok(NULL, "\t"));
    int num_sugestoes = atoi(argv[2]);
    int tamanho_hash = atoi(strtok(NULL, "\t"));

    ///////////////////////////////
    // Leitura de bases de dados //
    ///////////////////////////////

    // Lê arquivos de avaliações e metadados e preenche as listas
    Lista *filmes = Arquivo_LerListaDeFilmes(endereco_metadata);
    if (filmes == NULL){
        fprintf(stderr, "ERRO: Falha na leitura da base de dados de filmes.\n");
        exit(1);
    }
    int num_filmes = Lista_ObterTamanho(filmes);

    Lista *usuarios = Arquivo_LerListaDeUsuarios(endereco_ratings, num_filmes);
    if (usuarios == NULL)
    {
        fprintf(stderr, "ERRO: Falha na leitura da base de dados de usuarios.\n");
        exit(1);
    }
    // Unused: int num_usuarios = Lista_ObterTamanho(usuarios);

    ///////////////
    // Sugestões //
    ///////////////
    
    // Obtém sugestões por popularidade
    int *chaves_popularidade;
    HashTable_ABB *popularidade = Sugestoes_Popularidade(usuarios, filmes, 
        tamanho_hash, &chaves_popularidade);
    
    BitString *assistidos_dummy = BitString_Inicializar(num_filmes);

    // Inicializa usuário dummy para imprimir os filmes mais populares.
    Usuario *dummy = Usuario_Inicializar(-1, assistidos_dummy);
    
    // Imprime as sugestões as sugestões por popularidade na saída padrão, para
    // que esta possa ser redirecionada e utilizada pelo webapp.
    Sugestoes_ImprimirPopularidade(popularidade, chaves_popularidade, 
        num_filmes, dummy, num_sugestoes, stdout);

    HashTable_ABB_Destruir(popularidade, NULL);
    free(chaves_popularidade);

    Usuario_Destruir(dummy);

    Lista_Destruir(filmes, Filme_DestruirAux);
    Lista_Destruir(usuarios, Usuario_DestruirAux);

    // Encerramento dos arquivos de entrada e saída.
    fclose(arq_config);
    return 0;
}