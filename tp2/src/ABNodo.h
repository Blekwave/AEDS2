/**
 * Nodo de Árvore Binária - ABNodo.h
 * Biblioteca auxiliar de nodo genérico de árvore binária
 * Victor Pires Diniz - victorpiresdiniz@dcc.ufmg.br
 * 
 * Características:
 *   Opera de forma completamente genérica, com armazenamento de dados por meio
 *   de ponteiros void. Pode ser utilizado em árvores binárias de diversos tipos.
 */

#ifndef _ABNODO_H_
#define _ABNODO_H_

typedef struct abnodo {
    struct abnodo *pai;
    struct abnodo *esq;
    struct abnodo *dir;
    void *dados;
} ABNodo;

/////////////////////////////////
// INICIALIZAÇÃO E FINALIZAÇÃO //
/////////////////////////////////

/**
 * Inicializa um nodo de árvore binária.
 * esq e dir são inicializados como NULL.
 * @param  dados Endereço dos dados armazenados no nodo.
 * @return       Endereço no novo nodo ou NULL, caso não tenha sido possível
 *               alocar a memória necessária.
 */
ABNodo *ABNodo_Inicializar(ABNodo *pai, void *dados);

/**
 * Destrói um nodo especificado, liberando a memória alocada por ele e, possi-
 * velmente realizando um procedimento para destruir os dados.
 * @param  nodo          Endereço do nodo.
 * @param  DestruirDados Endereço da função a ser executada quando esta função
 *                       for chamada ou NULL. Essa função é responsável por li-
 *                       berar a memória alocada na estrutura contida pelo nodo,
 *                       mas liberar o conteúdo de nodo->dados é responsabili-
 *                       dade desta função, não sendo preciso fazer uma função
 *                       auxiliar para isso.
 */
void ABNodo_Destruir(ABNodo *nodo, void(*DestruirDados)(void *dados));

///////////////
// INTERFACE //
///////////////

/**
 * Retorna o endereço do nodo pai.
 * @param  nodo Nodo do qual se quer obter a informação.
 * @return      Endereço do nodo pai.
 */
ABNodo *ABNodo_ObterPai(ABNodo *nodo);


/**
 * Retorna o endereço do nodo filho à esquerda.
 * @param  nodo Nodo do qual se quer obter a informação.
 * @return      Endereço do nodo filho à esquerda.
 */
ABNodo *ABNodo_ObterEsq(ABNodo *nodo);

/**
 * Retorna o endereço do nodo filho à direita.
 * @param  nodo Nodo do qual se quer obter a informação.
 * @return      Endereço do nodo filho à direita.
 */
ABNodo *ABNodo_ObterDir(ABNodo *nodo);

/**
 * Retorna o endereço dos dados armazenados.
 * @param  nodo Nodo do qual se quer obter a informação.
 * @return      Endereço dos dados armazenados.
 */
void *ABNodo_ObterDados(ABNodo *nodo);

/**
 * Redefine o endereço do nodo pai desse nodo.
 * @param  nodo Nodo que se quer modificar.
 * @param  pai  Endereço novo.
 */
void ABNodo_DefinirPai(ABNodo *nodo, ABNodo *pai);

/**
 * Redefine o endereço do nodo filho à esquerda desse nodo.
 * @param  nodo Nodo que se quer modificar.
 * @param  esq  Endereço novo.
 */
void ABNodo_DefinirEsq(ABNodo *nodo, ABNodo *esq);

/**
 * Redefine o endereço do nodo filho à direita desse nodo.
 * @param  nodo Nodo que se quer modificar.
 * @param  dir  Endereço novo.
 */
void ABNodo_DefinirDir(ABNodo *nodo, ABNodo *dir);

/**
 * Redefine o endereço dos dados armazenados nesse nodo.
 * @param  nodo  Nodo que se quer modificar.
 * @param  dados Endereço novo.
 */
void ABNodo_DefinirDados(ABNodo *nodo, void *dados);

#endif
