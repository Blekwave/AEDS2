#ifndef _SUGESTOES_IMPRESSAO_IDS_H
#define _SUGESTOES_IMPRESSAO_IDS_H

#include "Filme.h"
#include "Usuario.h"
#include "BitString.h"
#include "HashTable_ABB.h"
#include "Racional.h"
#include <stdio.h>

///////////////
// IMPRESSÃO //
///////////////

//////////////////
// Popularidade //
//////////////////

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
    int num_chaves, Usuario *alvo, int num_sugestoes, FILE *arquivo);

//////////////////
// Similaridade //
//////////////////

/**
 * Imprime as sugestões por similaridade para um usuário em particular.
 * @param tabela        Hash table que contém as sugestões por similaridade.
 * @param chaves        Vetor de chaves em ordem decrescente.
 * @param num_chaves    Número de chaves.
 * @param alvo          Usuário para o qual as sugestões são feitas.
 * @param num_sugestoes Número de sugestões a serem feitas.
 * @param num_filmes    Número de filmes da base de dados.
 * @param arquivo       Arquivo no qual as sugestões serão impressas.
 */
void Sugestoes_ImprimirSimilaridade(HashTable_ABB *tabela, Racional *chaves,
    int num_chaves, Usuario *alvo, int num_sugestoes, int num_filmes, FILE *arquivo);

#endif