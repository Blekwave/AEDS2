/**
 * Lista duplamente encadeada - Ldenc.h
 * Biblioteca de lista duplamente encadeada genérica com cabeça
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

#include "Ldenc.h"
#include <stdlib.h>

/////////////////////////////////
// INICIALIZAÇÃO E FINALIZAÇÃO //
/////////////////////////////////

/**
 * Aloca a memória da nova lista, adiciona o nodo cabeça e atribui seu endereço
 * como primeira e última posições da lista.
 * @return endereço da nova lista.
 */
Ldenc *Ldenc_Inicializar(){
    Ldenc *nova;
    if ((nova = (Ldenc *)malloc(sizeof(Ldenc))) != NULL){
        // Inicializa o nodo cabeça e o atribui à primeira e à última posições
        Ndenc *cabeca = Ndenc_Inicializar(NULL, NULL, NULL);
        nova->cabeca = nova->ultimo = cabeca;
        nova->tamanho = 0;
    }
    return nova;
}

/**
 * Libera memória dos nodos da lista e da lista em si. Realiza o procedimento
 * DestruirDados nos dados dos nodos da lista antes da liberação.
 * @param lista Ldenc a ser liberada.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Ldenc_Destruir(Ldenc *lista, void(*DestruirDados)(void *)){
    Ndenc *atual = lista->cabeca->prox, *prox;
    Ndenc_Destruir(lista->cabeca, NULL);
    while (atual != NULL){
        prox = atual->prox;
        Ndenc_Destruir(atual, DestruirDados);
        atual = prox;
    }
    free(lista);
}

//////////////
// INSERÇÃO //
//////////////

/**
 * Adiciona um novo nodo após um nodo especificado.
 * @param  lista Ldenc ao qual será adicionado o novo elemento.
 * @param  referencia Ndenc após o qual será adicionado o novo elemento
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Ndenc *Ldenc_AdicionarElemento(Ldenc *lista, Ndenc *referencia, void *dados){
    Ndenc *novo = NULL;
    if (referencia != NULL && (novo = Ndenc_Inicializar(dados, referencia->prox, referencia)) != NULL){
        if (referencia->prox != NULL)
            referencia->prox->ant = novo;
        referencia->prox = novo;
        if (lista->ultimo == referencia)
            lista->ultimo = novo;
        (lista->tamanho)++;
    }
    return novo;
}

/**
 * Adiciona um novo nodo no início da lista.
 * @param  lista Ldenc ao qual será adicionado o novo elemento.
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Ndenc *Ldenc_AdicionarAoInicio(Ldenc *lista, void *dados){
    Ndenc *novo = NULL;
    if ((novo = Ndenc_Inicializar(dados, lista->cabeca->prox, lista->cabeca)) != NULL){
        if (lista->cabeca->prox != NULL)
            lista->cabeca->prox->ant = novo;
        lista->cabeca->prox = novo;
        if (lista->ultimo == lista->cabeca)
            lista->ultimo = novo;
        (lista->tamanho)++;
    }
    return novo;
}

/**
 * Adiciona um novo nodo ao fim da lista.
 * @param  lista Ldenc ao qual será adicionado o novo elemento.
 * @param  dados Endereço dos dados armazenados por esse elemento.
 * @return       Endereço do novo nodo adicionado.
 */
Ndenc *Ldenc_AdicionarAoFinal(Ldenc *lista, void *dados){
    Ndenc *novo = NULL;
    if ((novo = Ndenc_Inicializar(dados, NULL, lista->ultimo)) != NULL){
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
 * @param lista         Ldenc da qual o elemento será removido.
 * @param nodo          Ndenc a ser removido
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Ldenc_RemoverElemento(Ldenc *lista, Ndenc *nodo, void(*DestruirDados)(void *)){
    if (nodo != NULL && nodo != lista->cabeca){
        nodo->ant->prox = nodo->prox;
        if (lista->ultimo == nodo)
            lista->ultimo = nodo->ant;
        else
            nodo->prox->ant = nodo->ant; // Se o nodo é o último, nodo->prox == NULL
        Ndenc_Destruir(nodo, DestruirDados);
        (lista->tamanho)--;
    }
};

/**
 * Remove elemento após o nodo. Pode realizar um procedimento especificado para
 * destruir os dados armazenados.
 * @param lista         Ldenc da qual o elemento será removido.
 * @param nodo          Ndenc a ser removido
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Ldenc_RemoverElementoApos(Ldenc *lista, Ndenc *nodo, void(*DestruirDados)(void *)){
    Ldenc_RemoverElemento(lista, nodo->prox, DestruirDados);
}

/**
 * Remove o primeiro elemento da lista. Pode realizar um procedimento especi-
 * ficado para destruir os dados armazenados.
 * @param lista         Ldenc da qual o elemento será removido.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Ldenc_RemoverPrimeiroElemento(Ldenc *lista, void(*DestruirDados)(void *)){
    if (lista->tamanho > 0){
        Ndenc *temp = lista->cabeca->prox;
        lista->cabeca->prox = lista->cabeca->prox->prox;
        if (lista->cabeca->prox != NULL)
            lista->cabeca->prox->ant = lista->cabeca;
        if (temp == lista->ultimo)
            lista->ultimo = lista->cabeca;
        Ndenc_Destruir(temp, DestruirDados);
        (lista->tamanho)--;
    }
}

/**
 * Remove o ultimo elemento da lista. Pode realizar um procedimento especifica
 * do para destruir os dados armazenados.
 * @param lista         Ldenc da qual o elemento será removido.
 * @param DestruirDados ponteiro de função void cujo parâmetro é um ponteiro
 *                      void correspondente aos dados do nodo. Pode ser NULL,
 *                      caso não haja necessidade de usar essa funcionalidade.
 */
void Ldenc_RemoverUltimoElemento(Ldenc *lista, void(*DestruirDados)(void *)){
    if (lista->tamanho > 0){
        Ndenc *temp = lista->ultimo->ant;
        temp->prox = NULL;
        Ndenc_Destruir(lista->ultimo, DestruirDados);
        lista->ultimo = temp;
        (lista->tamanho)--;
    }
}

/////////////////////////////////////
// DESLOCAMENTO, TROCA E ORDENAÇÃO //
/////////////////////////////////////

/**
 * Desloca um nodo para a posição após o destino especificado.
 * @param lista   Ldenc na qual as operações são realizadas.
 * @param origem  Ndenc a ser deslocado
 * @param destino Ndenc após o qual origem deve ser posicionado
 */
void Ldenc_DeslocarElemento(Ldenc *lista, Ndenc *origem, Ndenc *destino){
    if (origem == destino || origem == lista->cabeca)
        return;

    if (lista->ultimo == origem)
        lista->ultimo = origem->ant;
    else if (lista->ultimo == destino)
        lista->ultimo = origem;

    origem->ant->prox = origem->prox;
    if (origem->prox != NULL)
        origem->prox->ant = origem->ant;

    origem->prox = destino->prox;
    origem->ant = destino;
    if (destino->prox != NULL)
        destino->prox->ant = origem;
    destino->prox = origem;
}

/**
 * Troca dois nodos de posição em uma lista.
 * @param lista Ldenc que contém os nodos
 * @param a     Ndenc A
 * @param b     Ndenc B
 */
void Ldenc_TrocarElementos(Ldenc *lista, Ndenc *a, Ndenc *b){
    Ndenc *temp;
    if (a == b || a == lista->cabeca || b == lista->cabeca)
        return;

    if (a == lista->ultimo)
        lista->ultimo = b;
    else if (b == lista->ultimo)
        lista->ultimo = a;

    a->ant->prox = b;
    if (a->prox != NULL)
        a->prox->ant = b;
    b->ant->prox = a;
    if (b->prox != NULL)
        b->prox->ant = a;

    temp = a->prox;
    a->prox = b->prox;
    b->prox = temp;

    temp = a->ant;
    a->ant = b->ant;
    b->ant = temp;
}

/**
 * Troca o endereço armazenado no ponteiro de dados de dois nodos de uma lista.
 * @param a Ndenc A
 * @param b Ndenc B
 */
void Ldenc_TrocarDados(Ndenc *a, Ndenc *b){
    void *temp = a->dados;
    a->dados = b->dados;
    b->dados = temp;
}

/**
 * Ordena a lista na ordem estipulada pela função de comparação passada.
 * @param  lista      Ldenc a ser ordenada
 * @param  Comparacao Função a ser usada para determinar a ordem na qual a lista
 *                    deve ser ordenada. Os parâmetros recebidos são ponteiros
 *                    void contendo o endereço dos dados de dois elementos a e b
 *                    sendo que a vem antes de b. Assim, se a função lida com 
 *                    inteiros, por exemplo, retornar a > b significa que a lista
 *                    será ordenada em ordem decrescente.
 */
void Ldenc_InsertionSort(Ldenc *lista, int(*Comparacao)(void *, void *)){
    if (lista->tamanho <= 1)
        return;
    Ndenc *atual = lista->cabeca->prox->prox, *i, *prox;
    while (atual != NULL){
        prox = atual->prox;
        i = lista->cabeca;
        while (i != atual && Comparacao(i->prox->dados, atual->dados))
            i = i->prox;
        Ldenc_DeslocarElemento(lista, atual, i);
        atual = prox;
    }
}

///////////////
// TRAVESSIA //
///////////////

/**
 * Aplica uma função aos dados de todos os nodos válidos da lista.
 * @param  lista  Ldenc
 * @param  Funcao função a ser aplicada aos dados dos nodos. A função deve 
 *                retornar void e ter um único argumento do tipo void *.
 */
void Ldenc_Atravessar(Ldenc *lista, void(*Funcao)(void *)){
    if (lista->tamanho <= 0)
        return;
    Ndenc *atual = lista->cabeca->prox;
    do {
        Funcao(atual->dados);
    } while ((atual = atual->prox) != NULL);
}

///////////////
// INTERFACE //
///////////////

/**
 * Retorna endereço do primeiro nodo válido.
 * @param  lista Ldenc da qual se quer o elemento.
 * @return       Endereço do primeiro nodo válido.
 */
Ndenc *Ldenc_ObterPrimeiro(Ldenc *lista){
    return lista->cabeca->prox;
}

/**
 * Retorna endereço do último nodo (podendo este ser o cabeça)
 * @param  lista Ldenc da qual se quer o elemento.
 * @return       Endereço do último nodo.
 */
Ndenc *Ldenc_ObterUltimo(Ldenc *lista){
    return lista->ultimo;
}

/**
 * Retorna endereço do nodo cabeça.
 * @param  lista Ldenc da qual se quer o elemento.
 * @return       Endereço do nodo cabeça.
 */
Ndenc *Ldenc_ObterCabeca(Ldenc *lista){
    return lista->cabeca;
}

/**
 * Retorna endereço do nodo anterior. Função redundante: funcionalidade efetuada
 * por ObterAnt, de "Ndenc.h". Existe para manter compatibilidade com a implemen-
 * tação de lista encadeada simples, na qual essa operação depende da lista e é
 * O(n).
 * @param  lista Ldenc na qual está o nodo.
 * @param  nodo  Ndenc do qual se quer o endereço do anterior.
 * @return       Endereço do nodo anterior.
 */
Ndenc *Ldenc_ObterAnterior(Ldenc *lista, Ndenc *nodo){ // Redundante: ObterAnt
    return nodo->ant;
}

/**
 * Retorna endereço do nodo de índice indice na lista.
 * @param  lista  Ldenc na qual está o nodo.
 * @param  indice Índice natural menor que o tamanho da lista.
 * @return        Endereço do nodo.
 */
Ndenc *Ldenc_ObterElementoPorIndice(Ldenc *lista, int indice){
    if (indice < 0 || indice >= lista->tamanho)
        return NULL;
    Ndenc *atual = lista->cabeca->prox;
    while (indice > 0 && atual != NULL){
        atual = atual->prox;
        indice--;
    }
    return atual;
}

/**
 * Retorna o tamanho da lista, sem contar com a cabeça.
 * @param  lista Ldenc 
 * @return       Número de elementos da lista.
 */
int Ldenc_ObterTamanho(Ldenc *lista){
    return lista->tamanho;
}

