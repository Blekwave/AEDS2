/**
 * Nodo encadeado - Nodo.h
 * Biblioteca auxiliar para a implementação de lista encadeada
 * Victor Pires Diniz - victorpiresdiniz@dcc.ufmg.br
 */

#include "Nodo.h"
#include <stdlib.h>

/**
 * Aloca a memória para um novo nodo e inicializa seus elementos
 * @param  dados Dados a serem armazenados no nodo
 * @param  prox  Próximo nodo (ou NULL)
 * @return       endereço do novo Nodo
 */
Nodo *Nodo_Inicializar(void *dados, void *prox){
    Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
    if (novo != NULL){
        novo->dados = dados;
        novo->prox = prox;
    }
    return novo;
}

/**
 * Retorna endereço do próximo Nodo
 * @param  nodo Nodo do qual se quer o próximo nodo
 * @return      endereço do próximo nodo
 */
Nodo *Nodo_ObterProx(Nodo *nodo){
    return nodo->prox;
}

/**
 * Redefine o próximo elemento de um nodo
 * @param nodo Nodo a ser modificado
 * @param prox endereço do próximo nodo (ou NULL)
 */
void Nodo_DefinirProx(Nodo *nodo, void *prox){
    nodo->prox = prox;
}

/**
 * Retorna o endereço dos dados contidos no nodo
 * @param  nodo Nodo do qual se quer os dados
 * @return      Ponteiro void com endereço dos dados
 */
void *Nodo_ObterDados(Nodo *nodo){
    return nodo->dados;
}

/**
 * Redefine o endereço dos dados do nodo
 * @param nodo  Nodo a ser modificado
 * @param dados endereço dos dados do Nodo
 */
void Nodo_DefinirDados(Nodo *nodo, void *dados){
    nodo->dados = dados;
}

/**
 * Executa uma função cujo parâmetro são os dados do nodo, caso seja preciso
 * realizar procedimentos especiais para destruir os dados do nodo. Após fazê-
 * -lo, destrói o nodo.
 * @param nodo Nodo a ser destruído
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Nodo_Destruir(Nodo *nodo, void (*DestruirDados)(void *)){
    if (DestruirDados != NULL)
        (*DestruirDados)(nodo->dados);
    if (nodo->dados != NULL)
        free(nodo->dados);
    free(nodo);
}