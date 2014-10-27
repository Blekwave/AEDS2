#include "Ndenc.h"
#include <stdlib.h>

/**
 * Aloca a memória para um novo nodo e inicializa seus elementos
 * @param  dados Dados a serem armazenados no nodo
 * @param  prox  Próximo nodo (ou NULL)
 * @param  ant   Ndenc anterior (ou NULL)
 * @return       endereço do novo Ndenc
 */
Ndenc *Ndenc_Inicializar(void *dados, void *prox, void *ant){
    Ndenc *novo = (Ndenc *)malloc(sizeof(Ndenc));
    if (novo != NULL){
        novo->dados = dados;
        novo->prox = prox;
        novo->ant = ant;
    }
    return novo;
}

/**
 * Retorna endereço do próximo Ndenc
 * @param  nodo Ndenc do qual se quer o próximo nodo
 * @return      endereço do próximo nodo
 */
Ndenc *Ndenc_ObterProx(Ndenc *nodo){
    return nodo->prox;
}

/**
 * Redefine o próximo elemento de um nodo
 * @param nodo Ndenc a ser modificado
 * @param prox endereço do próximo nodo (ou NULL)
 */
void Ndenc_DefinirProx(Ndenc *nodo, void *prox){
    nodo->prox = prox;
}

/**
 * Retorna endereço do Ndenc anterior
 * @param  nodo Ndenc do qual se quer o nodo anterior
 * @return      endereço do nodo anterior
 */
Ndenc *Ndenc_ObterAnt(Ndenc *nodo){
    return nodo->ant;
}

/**
 * Redefine o elemento anterior de um nodo
 * @param nodo Ndenc a ser modificado
 * @param ant  endereço do nodo anterior (ou NULL)
 */
void Ndenc_DefinirAnt(Ndenc *nodo, void *ant){
    nodo->ant = ant;
}

/**
 * Retorna o endereço dos dados contidos no nodo
 * @param  nodo Ndenc do qual se quer os dados
 * @return      Ponteiro void com endereço dos dados
 */
void *Ndenc_ObterDados(Ndenc *nodo){
    return nodo->dados;
}

/**
 * Redefine o endereço dos dados do nodo
 * @param nodo  Ndenc a ser modificado
 * @param dados endereço dos dados do Ndenc
 */
void Ndenc_DefinirDados(Ndenc *nodo, void *dados){
    nodo->dados = dados;
}

/**
 * Executa uma função cujo parâmetro são os dados do nodo, caso seja preciso
 * realizar procedimentos especiais para destruir os dados do nodo. Após fazê-
 * -lo, destrói o nodo.
 * @param nodo Ndenc a ser destruído
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Ndenc_Destruir(Ndenc *nodo, void (*DestruirDados)(void *)){
    if (DestruirDados != NULL)
        (*DestruirDados)(nodo->dados);
    if (nodo->dados != NULL)
        free(nodo->dados);
    free(nodo);
}