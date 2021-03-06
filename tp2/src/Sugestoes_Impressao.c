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

#define SEPARADOR "\t"

/**
 * Imprime o título de um filme e uma tabulação em um arquivo.
 * @param filme   Filme.
 * @param arquivo Arquivo no qual será imprimido o título.
 */
static void ImprimirFilme(Filme *filme, FILE *arquivo, int *num_sugestoes){
    fprintf(arquivo, "%s%s", Filme_ObterTitulo(filme), 
        (*num_sugestoes) > 1 ? SEPARADOR : "");
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
 * @param wrapper       Wrapper_Popularidade que contém a chave sendo imprimida
 *                      nesse caminhamento.
 * @param arquivo       Arquivo no qual os filmes serão imprimidos.
 */
static void ImprimirABBuscaPopularidade(ABNodo *raiz, BitString *assistidos, 
    int *num_sugestoes, Wrapper_Popularidade *wrapper, FILE *arquivo){
    if (raiz == NULL || *num_sugestoes <= 0)
        return;

    Wrapper_Popularidade *nodo_wrapper = ABNodo_ObterDados(raiz);

    ImprimirABBuscaPopularidade(ABNodo_ObterDir(raiz), assistidos, 
        num_sugestoes, wrapper, arquivo);

    // Não imprime um filme que já foi impresso
    // Não imprime mais se já foi atingido o número de sugestões
    // Não imprime se a chave do nodo atual não é a que está sendo imprimida
    if (BitString_ObterBit(assistidos, nodo_wrapper->filme->movie_id) == 0 &&
        *num_sugestoes > 0 &&
        (wrapper->visualizacoes == nodo_wrapper->visualizacoes)){
        ImprimirFilme(nodo_wrapper->filme, arquivo, num_sugestoes);
        BitString_DefinirBit(assistidos, nodo_wrapper->filme->movie_id, 1);
        (*num_sugestoes)--;
    }

    if (*num_sugestoes > 0)
        ImprimirABBuscaPopularidade(ABNodo_ObterEsq(raiz), assistidos, 
            num_sugestoes, wrapper, arquivo);

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
    BitString *assistidos = Usuario_ObterAssistidos(alvo);
    BitString *assistidos_copia = 
        BitString_Inicializar(BitString_ObterTamanho(assistidos));
    BitString_Copiar(assistidos_copia, assistidos);

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
        ImprimirABBuscaPopularidade(ABBusca_ObterRaiz(arvore), assistidos_copia,
            &num_sugestoes, &wrapper, arquivo);
        chaves_indice++;
    }
    BitString_Destruir(assistidos_copia);
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
 * @param wrapper       Wrapper_Similaridade que contém a chave sendo imprimida
 *                      nesse caminhamento.
 * @param arquivo       Arquivo no qual os filmes serão imprimidos.
 */
static void ImprimirABBuscaSimilaridade(ABNodo *raiz, BitString *assistidos, 
    int *num_sugestoes, Wrapper_Similaridade *wrapper, FILE *arquivo){
    if (raiz == NULL || *num_sugestoes <= 0){
        return;
    }

    Wrapper_Similaridade *nodo_wrapper = ABNodo_ObterDados(raiz);

    ImprimirABBuscaSimilaridade(ABNodo_ObterDir(raiz), assistidos, 
        num_sugestoes, wrapper, arquivo);

    // Não imprime um filme que já foi impresso
    // Não imprime mais se já foi atingido o número de sugestões
    // Não imprime se a chave do nodo atual não é a que está sendo imprimida
    if (BitString_ObterBit(assistidos, nodo_wrapper->filme->movie_id) == 0 &&
        *num_sugestoes > 0 && 
        (Racional_Comparar(wrapper->jaccard, nodo_wrapper->jaccard) == 0))
    {
        ImprimirFilme(nodo_wrapper->filme, arquivo, num_sugestoes);
        BitString_DefinirBit(assistidos, nodo_wrapper->filme->movie_id, 1);
        (*num_sugestoes)--;
    }

    if (*num_sugestoes > 0)
        ImprimirABBuscaSimilaridade(ABNodo_ObterEsq(raiz), assistidos,
            num_sugestoes, wrapper, arquivo);

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
    BitString *assistidos = Usuario_ObterAssistidos(alvo);
    BitString *assistidos_copia = 
        BitString_Inicializar(BitString_ObterTamanho(assistidos));
    BitString_Copiar(assistidos_copia, assistidos);

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
        ImprimirABBuscaSimilaridade(raiz, assistidos_copia, &num_sugestoes, &wrapper, arquivo);
        chaves_indice++;
    }
    BitString_Destruir(assistidos_copia);
}