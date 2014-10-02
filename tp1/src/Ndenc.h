#ifndef _NDENC_H_
#define _NDENC_H_

typedef struct ndenc {
    void *dados;
    struct ndenc *prox;
    struct ndenc *ant;
} Ndenc;

/**
 * Aloca a memória para um novo nodo e inicializa seus elementos
 * @param  dados Dados a serem armazenados no nodo
 * @param  prox  Próximo nodo (ou NULL)
 * @param  ant   Ndenc anterior (ou NULL)
 * @return       endereço do novo Ndenc
 */
Ndenc *InicializarNdenc(void *dados, void *prox, void *ant);

/**
 * Retorna endereço do próximo Ndenc
 * @param  nodo Ndenc do qual se quer o próximo nodo
 * @return      endereço do próximo nodo
 */
Ndenc *ObterProx(Ndenc *nodo);

/**
 * Redefine o próximo elemento de um nodo
 * @param nodo Ndenc a ser modificado
 * @param prox endereço do próximo nodo (ou NULL)
 */
void DefinirProx(Ndenc *nodo, void *prox);

/**
 * Retorna endereço do Ndenc anterior
 * @param  nodo Ndenc do qual se quer o nodo anterior
 * @return      endereço do nodo anterior
 */
Ndenc *ObterAnt(Ndenc *nodo);

/**
 * Redefine o elemento anterior de um nodo
 * @param nodo Ndenc a ser modificado
 * @param ant  endereço do nodo anterior (ou NULL)
 */
void DefinirAnt(Ndenc *nodo, void *ant);

/**
 * Retorna o endereço dos dados contidos no nodo
 * @param  nodo Ndenc do qual se quer os dados
 * @return      Ponteiro void com endereço dos dados
 */
void *ObterDados(Ndenc *nodo);

/**
 * Redefine o endereço dos dados do nodo
 * @param nodo  Ndenc a ser modificado
 * @param dados endereço dos dados do Ndenc
 */
void DefinirDados(Ndenc *nodo, void *dados);

/**
 * Executa uma função cujo parâmetro são os dados do nodo, caso seja preciso
 * realizar procedimentos especiais para destruir os dados do nodo. Após fazê-
 * -lo, destrói o nodo.
 * @param nodo Ndenc a ser destruído
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void DestruirNdenc(Ndenc *nodo, void (*DestruirDados)(void *));

#endif