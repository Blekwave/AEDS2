#include "Sugestoes_Impressao.h"
#include "Sugestoes.h"
#include "Filme.h"
#include "Usuario.h"
#include "BitString.h"
#include <stdio.h>
#include <stdlib.h>

///////////////
// IMPRESSÃO //
///////////////

#define SEPARADOR '\n'

#define int_nodo(x) (*(int *)x->dados)

/**
 * Imprime o título de um filme e uma tabulação em um arquivo.
 * @param filme   Filme.
 * @param arquivo Arquivo no qual será imprimido o título.
 */
static void ImprimirFilme(Filme *filme, FILE *arquivo){
    fprintf(arquivo, "%d %d%c", Filme_ObterMovieID(filme), Filme_ObterIMDBID(filme), SEPARADOR);
}

//////////////////
// Popularidade //
//////////////////

/**
 * Função auxiliar recursiva que imprime o conteúdo das árvores de busca binária da 
 * hash table das sugestões por popularidade. Percorre a árvore em ordem central.
 * @param raiz          Raiz da sub-árvore sendo imprimida.
 * @param assistidos    BitString que contém informações quanto a se um filme já
 *                      foi assistido pelo alvo ou imprimido na operação. O ín-
 *                      dice da bitstring é o movie_id de cada filme.
 * @param num_sugestoes Número de sugestões a serem imprimidas.
 * @param arquivo       Arquivo no qual os filmes serão imprimidos.
 */
static void ImprimirABBuscaPopularidade(ABNodo *raiz, BitString *assistidos, int *num_sugestoes, FILE *arquivo){
    if (raiz == NULL || *num_sugestoes <= 0)
        return;

    Wrapper_Popularidade *nodo_wrapper = (Wrapper_Popularidade *)ABNodo_ObterDados(raiz);

    ImprimirABBuscaPopularidade(ABNodo_ObterDir(raiz), assistidos, num_sugestoes, arquivo);

    // Não imprime um filme que já foi impresso
    if (BitString_ObterBit(assistidos, nodo_wrapper->filme->movie_id) == 0 && *num_sugestoes > 0){
        ImprimirFilme(nodo_wrapper->filme, arquivo);
        BitString_DefinirBit(assistidos, nodo_wrapper->filme->movie_id, 1);
        (*num_sugestoes)--;
    }

    if (*num_sugestoes > 0)
        ImprimirABBuscaPopularidade(ABNodo_ObterEsq(raiz), assistidos, num_sugestoes, arquivo);

}

/**
 * Imprime as sugestões por popularidade para um usuário em particular.
 * @param tabela        Hash table que contém as sugestões por popularidade.
 * @param chaves        Vetor de chaves em ordem decrescente.
 * @param num_chaves    Número de chaves.
 * @param alvo          Usuário para o qual as sugestões são feitas.
 * @param num_sugestoes Número de sugestões a serem feitas.
 * @param arquivo       Arquivo no qual as sugestões serão impressas.
 */
void Sugestoes_ImprimirPopularidade(HashTable_ABB *tabela, int *chaves,
    int num_chaves, Usuario *alvo, int num_sugestoes, FILE *arquivo){
    BitString *assistidos = BitString_Inicializar(num_chaves);

    // Preenche a lista de assistidos com os filmes que o alvo já assistiu
    Nodo *alvo_assistido_atual = Lista_ObterPrimeiro(Usuario_ObterAssistidos(alvo));

    while (alvo_assistido_atual != NULL){
        BitString_DefinirBit(assistidos, int_nodo(alvo_assistido_atual), 1);
        alvo_assistido_atual = Nodo_ObterProx(alvo_assistido_atual);
    }

    int chaves_indice = 0;
    int tabela_tam = HashTable_ABB_ObterTamanho(tabela);

    // Itera pelas chaves únicas da lista de chaves em ordem decrescente enquan-
    // to ainda há sugestões a serem feitas.
    while (num_sugestoes > 0 && chaves_indice < num_chaves){
        // Computa a posição da chave na tabela hash
        Wrapper_Popularidade wrapper = {chaves[chaves_indice], NULL};
        int pos = Sugestoes_PopularidadeHash(&wrapper, tabela_tam);
        // Determina a árvore correspondente à posição
        ABBusca *arvore = HashTable_ABB_ObterABBusca(tabela, pos);
        ImprimirABBuscaPopularidade(ABBusca_ObterRaiz(arvore), assistidos, &num_sugestoes, arquivo);
        chaves_indice++;
    }

    BitString_Destruir(assistidos);
}

//////////////////
// Similaridade //
//////////////////

/**
 * Função auxiliar recursiva que imprime o conteúdo das árvores de busca binária da 
 * hash table das sugestões por similaridade. Percorre a árvore em ordem central.
 * @param raiz          Raiz da sub-árvore sendo imprimida.
 * @param assistidos    BitString que contém informações quanto a se um filme já
 *                      foi assistido pelo alvo ou imprimido na operação. O ín-
 *                      dice da bitstring é o movie_id de cada filme.
 * @param num_sugestoes Número de sugestões a serem imprimidas.
 * @param arquivo       Arquivo no qual os filmes serão imprimidos.
 */
static void ImprimirABBuscaSimilaridade(ABNodo *raiz, BitString *assistidos, int *num_sugestoes, FILE *arquivo){
    if (raiz == NULL || *num_sugestoes <= 0){
        return;
    }

    Wrapper_Similaridade *nodo_wrapper = (Wrapper_Similaridade *)ABNodo_ObterDados(raiz);

    ImprimirABBuscaSimilaridade(ABNodo_ObterDir(raiz), assistidos, num_sugestoes, arquivo);

    // Não imprime um filme que já foi impresso
    if (BitString_ObterBit(assistidos, nodo_wrapper->filme->movie_id) == 0 && *num_sugestoes > 0){
        ImprimirFilme(nodo_wrapper->filme, arquivo);
        BitString_DefinirBit(assistidos, nodo_wrapper->filme->movie_id, 1);
        (*num_sugestoes)--;
    }

    if (*num_sugestoes > 0)
        ImprimirABBuscaSimilaridade(ABNodo_ObterEsq(raiz), assistidos, num_sugestoes, arquivo);

}

/**
 * Imprime as sugestões por similaridade para um usuário em particular.
 * @param tabela        Hash table que contém as sugestões por similaridade.
 * @param chaves        Vetor de chaves em ordem decrescente.
 * @param num_chaves    Número de chaves.
 * @param alvo          Usuário para o qual as sugestões são feitas.
 * @param num_sugestoes Número de sugestões a serem feitas.
 * @param arquivo       Arquivo no qual as sugestões serão impressas.
 */
void Sugestoes_ImprimirSimilaridade(HashTable_ABB *tabela, Racional *chaves,
    int num_chaves, Usuario *alvo, int num_sugestoes, int num_filmes, FILE *arquivo){
    BitString *assistidos = BitString_Inicializar(num_filmes);

    // Preenche a lista de assistidos com os filmes que o alvo já assistiu
    Nodo *alvo_assistido_atual = Lista_ObterPrimeiro(Usuario_ObterAssistidos(alvo));

    while (alvo_assistido_atual != NULL){
        BitString_DefinirBit(assistidos, int_nodo(alvo_assistido_atual), 1);
        alvo_assistido_atual = Nodo_ObterProx(alvo_assistido_atual);
    }

    int chaves_indice = 0;
    int tabela_tam = HashTable_ABB_ObterTamanho(tabela);

    // Itera pelas chaves únicas da lista de chaves em ordem decrescente enquan-
    // to ainda há sugestões a serem feitas.
    while (num_sugestoes > 0 && chaves_indice < num_chaves){
        // Computa a posição da chave na tabela hash
        Wrapper_Similaridade wrapper = {chaves[chaves_indice], NULL, NULL};
        int pos = Sugestoes_SimilaridadeHash(&wrapper, tabela_tam);
        // Determina a árvore correspondente à posição
        ABNodo *raiz = ABBusca_ObterRaiz(HashTable_ABB_ObterABBusca(tabela, pos));
        // printf("Chave = %d/%d, Pos = %d, Raiz = %p\n", chaves[chaves_indice].num, chaves[chaves_indice].den, pos, raiz);
        ImprimirABBuscaSimilaridade(raiz, assistidos, &num_sugestoes, arquivo);
        chaves_indice++;
    }
    BitString_Destruir(assistidos);
}