/**
 * Lista encadeada - Lista.h
 * Biblioteca de lista encadeada genérica com cabeça
 * Victor Pires Diniz - victorpiresdiniz@dcc.ufmg.br
 *
 * Características:
 *   Opera de forma completamente genérica, com armazenamento de dados por meio
 *   de ponteiros void. Permite a ordenação, travessia e remoção com funções ge-
 *   néricas passadas por parâmetro, para comportar qualquer tipo de dados sem
 *   necessidade de alteração no código fonte da biblioteca.
 * 
 *   Contém sempre pelo menos um elemento cabeça, de forma a facilitar a imple-
 *   mentação de vários procedimentos.
 */

#include "Lista.h"
#include <stdlib.h>

/////////////////////////////////
// INICIALIZAÇÃO E FINALIZAÇÃO //
/////////////////////////////////

/**
 * Aloca a memória da nova lista, adiciona o nodo cabeça e atribui seu endereço
 * como primeira e última posições da lista.
 * @return endereço da nova lista.
 */
Lista *Lista_Inicializar(){
    Lista *nova;
    if ((nova = (Lista *)malloc(sizeof(Lista))) != NULL){
        Nodo *cabeca = Nodo_Inicializar(NULL, NULL);
        nova->cabeca = nova->ultimo = cabeca;
        nova->tamanho = 0;
    }
    return nova;
}

/**
 * Libera memória dos nodos da lista e da lista em si. Realiza o procedimento
 * DestruirDados nos dados dos nodos da lista antes da liberação.
 * @param lista Lista a ser liberada.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Lista_Destruir(Lista *lista, void(*DestruirDados)(void *)){
    Nodo *atual = lista->cabeca->prox, *prox;
    Nodo_Destruir(lista->cabeca, NULL);
    while (atual != NULL){
        prox = atual->prox;
        Nodo_Destruir(atual, DestruirDados);
        atual = prox;
    }
    free(lista);
}

//////////////
// INSERÇÃO //
//////////////

/**
 * Adiciona um novo nodo após um nodo especificado.
 * @param  lista Lista ao qual será adicionado o novo elemento.
 * @param  referencia Nodo após o qual será adicionado o novo elemento
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Nodo *Lista_AdicionarElemento(Lista *lista, Nodo *referencia, void *dados){
    Nodo *novo = NULL;
    if (referencia != NULL && (novo = Nodo_Inicializar(dados, referencia->prox)) != NULL){
        referencia->prox = novo;
        if (lista->ultimo == referencia)
            lista->ultimo = novo;
        (lista->tamanho)++;
    }
    return novo;
}

/**
 * Adiciona um novo nodo no início da lista.
 * @param  lista Lista ao qual será adicionado o novo elemento.
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Nodo *Lista_AdicionarAoInicio(Lista *lista, void *dados){
    Nodo *novo = NULL;
    if ((novo = Nodo_Inicializar(dados, lista->cabeca->prox)) != NULL){
        lista->cabeca->prox = novo;
        if (lista->ultimo == lista->cabeca)
            lista->ultimo = novo;
        (lista->tamanho)++;
    }
    return novo;
}

/**
 * Adiciona um novo nodo ao fim da lista.
 * @param  lista Lista ao qual será adicionado o novo elemento.
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Nodo *Lista_AdicionarAoFinal(Lista *lista, void *dados){
    Nodo *novo = NULL;
    if ((novo = Nodo_Inicializar(dados, NULL)) != NULL){
        lista->ultimo->prox = novo;
        lista->ultimo = novo;
        (lista->tamanho)++;
    }
    return novo;
}

/////////////
// REMOÇÃO //
/////////////

/**
 * Remove um elemento da lista. Pode realizar um procedimento especificado para
 * destruir os dados armazenados.
 * @param lista         Lista da qual o elemento será removido.
 * @param nodo          Nodo a ser removido
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Lista_RemoverElemento(Lista *lista, Nodo *nodo, void(*DestruirDados)(void *)){
    Nodo *anterior = Lista_ObterAnterior(lista, nodo);
    /* nodo != NULL e nodo != lista->cabeca não são necessários,
     * pois anterior é NULL nesses casos */
    if (anterior != NULL){
        anterior->prox = nodo->prox;
        if (lista->ultimo == nodo)
            lista->ultimo = anterior;
        Nodo_Destruir(nodo, DestruirDados);
        (lista->tamanho)--;
    }
};

/**
 * Remove elemento após o nodo. Pode realizar um procedimento especificado para
 * destruir os dados armazenados.
 * @param lista         Lista da qual o elemento será removido.
 * @param nodo          Nodo a ser removido
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Lista_RemoverElementoApos(Lista *lista, Nodo *nodo, void(*DestruirDados)(void *)){
    Nodo *temp;
    if (nodo != NULL && nodo->prox != NULL){
        temp = nodo->prox;
        if (temp == lista->ultimo)
            lista->ultimo = nodo;
        nodo->prox = nodo->prox->prox;
        Nodo_Destruir(temp, DestruirDados);
        (lista->tamanho)--;
    }
}

/**
 * Remove o primeiro elemento da lista. Pode realizar um procedimento especi-
 * ficado para destruir os dados armazenados.
 * @param lista         Lista da qual o elemento será removido.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Lista_RemoverPrimeiroElemento(Lista *lista, void(*DestruirDados)(void *)){
    if (lista->tamanho > 0){
        Nodo *temp = lista->cabeca->prox;
        lista->cabeca->prox = lista->cabeca->prox->prox;
        if (temp == lista->ultimo)
            lista->ultimo = lista->cabeca;
        Nodo_Destruir(temp, DestruirDados);
        (lista->tamanho)--;
    }
}

/**
 * Remove o ultimo elemento da lista. Pode realizar um procedimento especifica
 * do para destruir os dados armazenados.
 * @param lista         Lista da qual o elemento será removido.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Lista_RemoverUltimoElemento(Lista *lista, void(*DestruirDados)(void *)){
    if (lista->tamanho > 0){
        Nodo *ant = Lista_ObterAnterior(lista, lista->ultimo);
        ant->prox = NULL;
        Nodo_Destruir(lista->ultimo, DestruirDados);
        lista->ultimo = ant;
        (lista->tamanho)--;
    }
}

/////////////////////////////////////
// DESLOCAMENTO, TROCA E ORDENAÇÃO //
/////////////////////////////////////

/**
 * Desloca um nodo para a posição após o destino especificado.
 * @param lista   Lista na qual as operações são realizadas.
 * @param origem  Nodo a ser deslocado
 * @param destino Nodo após o qual origem deve ser posicionado
 */
void Lista_DeslocarElemento(Lista *lista, Nodo *origem, Nodo *destino){
    Nodo *anterior;
    if (origem == destino || (anterior = Lista_ObterAnterior(lista, origem)) == NULL)
        return;
    anterior->prox = origem->prox;
    origem->prox = destino->prox;
    destino->prox = origem;
    if (lista->ultimo == origem)
        lista->ultimo = anterior;
    else if (lista->ultimo == destino)
        lista->ultimo = origem;
}

/**
 * Troca dois nodos de posição em uma lista.
 * @param lista Lista que contém os nodos
 * @param a     Nodo A
 * @param b     Nodo B
 */
void Lista_TrocarElementos(Lista *lista, Nodo *a, Nodo *b){
    Nodo *anta, *antb, *temp;
    if (a == b)
        return;

    temp = lista->cabeca;
    do {
        if (temp->prox == a)
            anta = temp;
        else if (temp->prox == b)
            antb = temp;
    } while ((temp = temp->prox) != NULL);

    anta->prox = b;
    antb->prox = a;

    temp = a->prox;
    a->prox = b->prox;
    b->prox = temp;

    if (a == lista->ultimo)
        lista->ultimo = b;
    else if (b == lista->ultimo)
        lista->ultimo = a;
}

/**
 * Troca o endereço armazenado no ponteiro de dados de dois nodos de uma lista.
 * @param a Nodo A
 * @param b Nodo B
 */
void Lista_TrocarDados(Nodo *a, Nodo *b){
    void *temp = a->dados;
    a->dados = b->dados;
    b->dados = temp;
}

/**
 * Ordena a lista na ordem estipulada pela função de comparação passada.
 * @param  lista      Lista a ser ordenada
 * @param  Comparacao Função a ser usada para determinar a ordem na qual a lista
 *                    deve ser ordenada. Os parâmetros recebidos são ponteiros
 *                    void contendo o endereço dos dados de dois elementos a e b
 *                    sendo que a vem antes de b. Assim, se a função lida com 
 *                    inteiros, por exemplo, retornar a > b significa que a lista
 *                    será ordenada em ordem decrescente.
 */
void Lista_InsertionSort(Lista *lista, int(*Comparacao)(void *, void *)){
    if (lista->tamanho <= 1)
        return;
    Nodo *atual = lista->cabeca->prox->prox, *i, *prox;
    while (atual != NULL){
        prox = atual->prox;
        i = lista->cabeca;
        while (i != atual && Comparacao(i->prox->dados, atual->dados))
            i = i->prox;
        Lista_DeslocarElemento(lista, atual, i);
        atual = prox;
    }
}

///////////////
// TRAVESSIA //
///////////////

/**
 * Aplica uma função aos dados de todos os nodos válidos da lista.
 * @param  lista  Lista
 * @param  Funcao função a ser aplicada aos dados dos nodos. A função deve 
 *                retornar void e ter um único argumento do tipo void *.
 */
void Lista_Atravessar(Lista *lista, void(*Funcao)(void *)){
    if (lista->tamanho <= 0)
        return;
    Nodo *atual = lista->cabeca->prox;
    do {
        Funcao(atual->dados);
    } while ((atual = atual->prox) != NULL);
}

///////////////
// INTERFACE //
///////////////

/**
 * Retorna endereço do primeiro nodo válido.
 * @param  lista Lista da qual se quer o elemento.
 * @return       Endereço do primeiro nodo válido.
 */
Nodo *Lista_ObterPrimeiro(Lista *lista){
    return lista->cabeca->prox;
}

/**
 * Retorna endereço do último nodo (podendo este ser o cabeça)
 * @param  lista Lista da qual se quer o elemento.
 * @return       Endereço do último nodo.
 */
Nodo *Lista_ObterUltimo(Lista *lista){
    return lista->ultimo;
}

/**
 * Retorna endereço do nodo cabeça.
 * @param  lista Lista da qual se quer o elemento.
 * @return       Endereço do nodo cabeça.
 */
Nodo *Lista_ObterCabeca(Lista *lista){
    return lista->cabeca;
}

/**
 * Retorna endereço do nodo anterior. O(n)
 * @param  lista Lista na qual está o nodo.
 * @param  nodo  Nodo do qual se quer o endereço do anterior.
 * @return       Endereço do nodo anterior.
 */
Nodo *Lista_ObterAnterior(Lista *lista, Nodo *nodo){
    Nodo *atual = lista->cabeca;
    while(atual->prox != nodo && (atual = atual->prox) != NULL);
    return atual;
}

/**
 * Retorna endereço do nodo de índice indice na lista.
 * @param  lista  Lista na qual está o nodo.
 * @param  indice Índice natural menor que o tamanho da lista.
 * @return        Endereço do nodo.
 */
Nodo *Lista_ObterElementoPorIndice(Lista *lista, int indice){
    if (indice < 0 || indice >= lista->tamanho)
        return NULL;
    Nodo *atual = lista->cabeca->prox;
    while (indice > 0){
        atual = atual->prox;
        indice--;
    }
    return atual;
}

/**
 * Retorna o tamanho da lista, sem contar com a cabeça.
 * @param  lista Lista 
 * @return       Número de elementos da lista.
 */
int Lista_ObterTamanho(Lista *lista){
    return lista->tamanho;
}
