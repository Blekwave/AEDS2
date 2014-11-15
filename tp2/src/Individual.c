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
    if (argc < 4)
    {
        fprintf(stderr, "ERRO: Numero insuficiente de argumentos na chamada do programa.\nSintaxe correta: Individual.exe <configuracoes> <num_sugestoes> <assistidos>.\n");
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

    ///////////////////
    // Usuário dummy //
    ///////////////////

    // Inicializa bitstring de assistidos do usuário dummy.
    // Não é preciso destruí-la manualmente, já que o dummy é adicionado à lista
    // global de usuários.
    BitString *assistidos = BitString_Inicializar(num_filmes);

    // Adiciona filmes assistidos passados ao programa pela linha de comando
    int i;
    for (i = 3; i < argc; i++){
         BitString_DefinirBit(assistidos, atoi(argv[i]), 1); 
    }

    // Inicializa usuário dummy para imprimir as sugestões
    Usuario *dummy = Usuario_Inicializar(-1, assistidos);

    // É importante adicionar o dummy à lista de usuários para garantir que o
    // vetor de chaves tenha o tamanho certo. Isso não é necessário no programa
    // de geração de filmes mais populares, já que o tamanho do vetor de chaves
    // das sugestões por popularidade depende apenas do número de filmes.
    Lista_AdicionarAoFinal(usuarios, (void *)dummy);

    int num_usuarios = Lista_ObterTamanho(usuarios);

    ///////////////
    // Sugestões //
    ///////////////
    
    // Obtém sugestões por similaridade
    Racional *chaves_similaridade;
    HashTable_ABB *similaridade = Sugestoes_Similaridade(usuarios, filmes, dummy,
        tamanho_hash, &chaves_similaridade);

    // Imprime as sugestões as sugestões por popularidade na saída padrão, para
    // que esta possa ser redirecionada e utilizada pelo webapp.
    Sugestoes_ImprimirSimilaridade(similaridade, chaves_similaridade, 
        num_usuarios - 1, dummy, num_sugestoes, num_filmes, stdout);

    HashTable_ABB_Destruir(similaridade, NULL);
    free(chaves_similaridade);

    Lista_Destruir(filmes, Filme_DestruirAux);
    Lista_Destruir(usuarios, Usuario_DestruirAux);

    // Encerramento dos arquivos de entrada e saída.
    fclose(arq_config);
    return 0;
}