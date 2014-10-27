/**
 * Árvore Binária de Busca (modificada) - ABBusca_m.h
 * Biblioteca de árvore binária de busca genérica
 * Victor Pires Diniz - victorpiresdiniz@dcc.ufmg.br
 * 
 * Características:
 *   Opera de forma completamente genérica, com armazenamento de dados por meio
 *   de ponteiros void. 
 *   
 *   Se mantém ordenada também de maneira genérica, usando ponteiro de função 
 *   para armazenar uma função personalizada de comparação.
 *
 *   Utiliza a biblioteca ABNodo.h, tendo, assim, acesso ao nodo pai de cada no-
 *   do da árvore em tempo constante.
 *
 * Modificação: diferentemente da versão original dessa biblioteca, ABBusca_m
 * não armazena os ponteiros das funções de comparação e igualdade na própria
 * estrutura. Essas funções são passadas por parâmetro para as funções que ne-
 * cessitam de tal funcionalidade.
 */

#ifndef _ABBUSCA_M_H_
#define _ABBUSCA_M_H_

#include "ABNodo.h"
#include <stdbool.h>

///////////////////////////////////////////////////////////////////////////////////
// Sobre a comparação: considerando os dois parâmetros a e b, se a função retor- //
// na true, a deve se situar à direita de b. Caso contrário, a deve se situar à  //
// esquerda de b.                                                                //
///////////////////////////////////////////////////////////////////////////////////

typedef struct {
    ABNodo *raiz;
} ABBusca;

/////////////////////////////////
// INICIALIZAÇÃO E FINALIZAÇÃO //
/////////////////////////////////

/**
 * Inicializa a árvore binária de busca sem nenhum nodo.
 * @return            Endereço da nova árvore.
 */
ABBusca *ABBusca_Inicializar();

/**
 * Destrói os nodos da árvore a partir de um nodo raiz, operando recursivamente
 * em pós-ordem.
 * 
 * Uma função auxiliar pode ser passada para liberar a memória do conteúdo dos
 * dados. Essa função não deve liberar "dados" em si, isso é feito pelo proce-
 * dimento principal.
 * @param  raiz          Nodo inicial (raiz) da operação recursiva na árvore.
 * @param  DestruirDados Procedimento auxiliar de destruição a ser executado (ou
 *                       NULL, caso não seja necessário).
 */
void ABBusca_DestruirGalho(ABNodo *raiz, void(*DestruirDados)(void *dados));

/**
 * Destrói todos os nodos da árvore, operando recursivamente em pós-ordem.
 * 
 * Uma função auxiliar pode ser passada para liberar a memória do conteúdo dos
 * dados. Essa função não deve liberar "dados" em si, isso é feito pelo proce-
 * dimento principal.
 * @param  árvore        Árvore a ser destruída.
 * @param  DestruirDados Procedimento auxiliar de destruição a ser executado (ou
 *                       NULL, caso não seja necessário).
 */
void ABBusca_Destruir(ABBusca *arvore, void(*DestruirDados)(void *dados));

//////////////
// INSERÇÃO //
//////////////

/**
 * Adiciona novo elemento à árvore na posição apropriada.
 * @param  arvore     ABBusca à qual o elemento será adicionado.
 * @param  dados      Endereço dos dados do novo elemento.
 * @param  Comparacao Função de comparação a ser utilizada para manter a ordena-
 *                    ção da estrutura. Retorna verdadeiro se a fica à direita
 *                    de b. Retorna falso se a fica à esquerda de b.
 * @return            Endereço do novo elemento.
 */
ABNodo *ABBusca_AdicionarElemento(ABBusca *arvore, void *dados,
    bool(*Comparacao)(void *a, void *b));

/////////////////////////////
// CAMINHAMENTO (genérico) //
/////////////////////////////

/**
 * Atravessa a árvore em ordem central, executando a operação especificada nos
 * dados da árvore em cada nodo.
 * @param  raiz     Nodo inicial (raiz) da operação recursiva na árvore.
 * @param  Operacao Operação a ser executada.
 */
void ABBusca_OrdemCentral(ABNodo *raiz, void(*Operacao)(void *dados));

/**
 * Atravessa a árvore em pré-ordem, executando a operação especificada nos
 * dados da árvore em cada nodo.
 * @param  raiz     Nodo inicial (raiz) da operação recursiva na árvore.
 * @param  Operacao Operação a ser executada.
 */
void ABBusca_PreOrdem(ABNodo *raiz, void(*Operacao)(void *dados));

/**
 * Atravessa a árvore em pós-ordem, executando a operação especificada nos
 * dados da árvore em cada nodo.
 * @param  raiz     Nodo inicial (raiz) da operação recursiva na árvore.
 * @param  Operacao Operação a ser executada.
 */
void ABBusca_PosOrdem(ABNodo *raiz, void(*Operacao)(void *dados));

///////////
// BUSCA //
///////////

/**
 * Encontra o elemento cujos dados correspondem aos fornecidos à função em uma
 * árvore.
 * @param  arvore     Árvore na qual o elemento está.
 * @param  dados      Dados do elemento a ser encontrado.
 * @param  Comparacao Função de comparação a ser utilizada para manter a ordena-
 *                    ção da estrutura. Retorna verdadeiro se a fica à direita
 *                    de b. Retorna falso se a fica à esquerda de b.
 * @param  Igualdade  Função de comparação a ser utilizada para operações de
 *                    busca. Retorna verdadeiro se a é igual a b pelos critérios
 *                    definidos.
 * @return            Endereço do nodo correspondente (ou NULL, caso não haja 
 *                    tal)
 */
ABNodo *ABBusca_EncontrarElemento(ABBusca *arvore, void *dados,
    bool(*Comparacao)(void *a, void *b), bool(*Igualdade)(void *a, void *b));

/**
 * Encontra o elemento mínimo de um galho.
 * @param  raiz Raiz do galho do qual se quer o elemento mínimo.
 * @return      Endereço do nodo correspondente (ou NULL, caso não haja tal)
 */
ABNodo *ABBusca_EncontrarMinimo(ABNodo *raiz);

/**
 * Encontra o elemento máximo de um galho.
 * @param  raiz Raiz do galho do qual se quer o elemento máximo.
 * @return      Endereço do nodo correspondente (ou NULL, caso não haja tal)
 */
ABNodo *ABBusca_EncontrarMaximo(ABNodo *raiz);

/**
 * Encontra o antecessor de um nodo especificado.
 * @param  nodo   Nodo do qual se quer o antecessor.
 * @return        Endereço do antecessor (ou NULL, caso ele seja o mínimo)
 */
ABNodo *ABBusca_EncontrarAntecessor(ABNodo *nodo);

/**
 * Encontra o sucessor de um nodo especificado.
 * @param  nodo   Nodo do qual se quer o sucessor.
 * @return        Endereço do sucessor (ou NULL, caso ele seja o máximo)
 */
ABNodo *ABBusca_EncontrarSucessor(ABNodo *nodo);

/////////////
// REMOÇÃO //
/////////////

/**
 * Define novo como filho do nodo pai de velho, efetivamente substituindo uma
 * sub-árvore por outra sub-árvore. Não modifica os filhos do novo nodo: essa
 * responsabilidade fica para quem chama essa função.
 * @param arvore Árvore principal na qual estão os nodos
 * @param velho  Nodo a ser substituído
 * @param novo   Nodo a ser transplantado para a posição do velho.
 */
void ABBusca_TransplantarElemento(ABBusca *arvore, ABNodo *velho, ABNodo *novo);

/**
 * Remove um elemento da árvore binária de busca, mantendo a ordenação da árvo-
 * re da forma apropriada. 
 * @param  arvore        Árvore na qual o elemento está.
 * @param  nodo          Nodo a ser removido.
 * @param  DestruirDados Endereço da função a ser executada quando esta função
 *                       for chamada ou NULL. Essa função é responsável por li-
 *                       berar a memória alocada na estrutura contida pelo nodo,
 *                       mas liberar o conteúdo de nodo->dados é responsabili-
 *                       dade desta função, não sendo preciso fazer uma função
 *                       auxiliar para isso.
 */
void ABBusca_RemoverElemento(ABBusca *arvore, ABNodo *nodo,
    void(*DestruirDados)(void *dados));

///////////////
// INTERFACE //
///////////////

/**
 * Retorna o endereço da raiz da árvore
 * @param  arvore Árvore da qual se quer a raiz
 * @return        Endereço da raiz da árvore
 */
ABNodo *ObterRaiz(ABBusca *arvore);

/**
 * Redefine o endereço da raiz da árvore
 * @param arvore Árvore da qual se quer redefinir o endereço
 * @param raiz   Novo endereço da raiz
 */
void DefinirRaiz(ABBusca *arvore, ABNodo *raiz);

#endif