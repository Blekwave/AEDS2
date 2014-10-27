/**
 * Hash Table com Árvore Binária de Busca - HashTable_ABB.h
 * Biblioteca de hash table genérica com tratamento de colusões através de árvo-
 * re binária de busca.
 * Victor Pires Diniz - victorpiresdiniz@dcc.ufmg.br
 * 
 * Características:
 *   Opera de forma completamente genérica, com armazenamento de dados por meio
 *   de ponteiros void.
 *   
 *   Tem tratamento eficiente de colisões através do uso de árvores binárias de
 *   busca para cada posição da tabela.
 */

#include "ABBusca_m.h"

typedef struct {
    ABBusca **arvore;
    int tam;
    bool(*Comparacao)(void *a, void *b); // a > b -> a fica à direita de b
    bool(*Igualdade)(void *a, void *b); // retorna verdadeiro se a == b
    int(*Hash)(void *chave, int tam);
} HashTable_ABB;

/////////////////////////////////
// INICIALIZAÇÃO E FINALIZAÇÃO //
/////////////////////////////////

/**
 * Aloca e inicializa uma hash table de tamanho tam e as estruturas auxiliares
 * necessárias.
 * @param  tam Tamanho da nova hash table.
 * @param  Comparacao Função de comparação a ser utilizada para manter a ordena-
 *                    ção das ABBusca. Retorna verdadeiro se a fica à direita de
 *                    b. Retorna falso se a fica à esquerda de b.
 * @param  Igualdade  Função de comparação a ser utilizada para operações de
 *                    busca. Retorna verdadeiro se a é igual a b pelos critérios
 *                    definidos.
 * @return     Endereço da nova tabela.
 */
HashTable_ABB *HashTable_ABB_Inicializar(int tam,
    bool(*Comparacao)(void *a, void *b), bool(*Igualdade)(void *a, void *b),
    int(*Hash)(void *chave, int tam));

/**
 * Libera a memória e finaliza uma tabela. Pode realizar um procedimento genéri-
 * co auxiliar para destruir as estruturas internas.
 * @param tabela HashTable_ABB a ser destruida.
 * @param  DestruirDados Procedimento auxiliar de destruição a ser executado (ou
 *                       NULL, caso não seja necessário). 
 */
void HashTable_ABB_Destruir(HashTable_ABB *tabela, void(*DestruirDados)(void *dados));

//////////////
// INSERÇÃO //
//////////////

/**
 * Insere na hash table um elemento novo com dados já alocados.
 * @param  tabela HashTable_ABB na qual o elemento será adicionado.
 * @param  dados  Endereço dos dados do elemento.
 * @return        Endereço do nodo da árvore binária da casa da hash table onde
 *                está o novo elemento.
 */
ABNodo *HashTable_ABB_AdicionarElemento(HashTable_ABB *tabela, void *dados);

///////////
// BUSCA //
///////////

/**
 * Busca na hash table por um elemento com dados correspondentes aos fornecidos.
 * @param  tabela HashTable_ABB na qual pode estar o elemento.
 * @param  dados  Endereço de dados alocados correspondentes ao elemento.
 * @return        Endereço do nodo no qual o elemento procurado está (ou NULL)
 */
ABNodo *HashTable_ABB_Buscar(HashTable_ABB *tabela, void *dados);

/////////////
// REMOÇÃO //
/////////////

/**
 * Libera a memória e remove um elemento. Pode realizar um procedimento genéri-
 * co auxiliar para destruir as estruturas internas.
 * @param tabela         HashTable_ABB na qual está o elemento a ser removido.
 * @param dados          Endereço dos dados do elemento a ser removido.
 * @param  DestruirDados Procedimento auxiliar de destruição a ser executado (ou
 *                       NULL, caso não seja necessário). 
 */
void HashTable_ABB_RemoverElemento(HashTable_ABB *tabela, void *dados, 
    void(*DestruirDados)(void *dados));

///////////////
// INTERFACE //
///////////////

/**
 * Retorna o tamanho da tabela.
 * @param  tabela HashTable_ABB da qual se quer a propriedade
 * @return        Tamanho da hash table.
 */
int HashTable_ABB_ObterTamanho(HashTable_ABB *tabela);

/**
 * Retorna o endereço da função de comparação das árvores binárias de busca da
 * hash table.
 * @param  tabela HashTable_ABB da qual se quer a função.
 * @return        Endereço da função de comparação.
 */
bool(*HashTable_ABB_ObterComparacao(HashTable_ABB *tabela))(void *a, void *b);

/**
 * Retorna o endereço da função de igualdade das árvores binárias de busca da
 * hash table.
 * @param  tabela HashTable_ABB da qual se quer a função.
 * @return        Endereço da função de igualdade.
 */
bool(*HashTable_ABB_ObterIgualdade(HashTable_ABB *tabela))(void *a, void *b);

/**
 * Retorna o endereço da função hash da hash table.
 * @param  tabela HashTable_ABB da qual se quer a função.
 * @return        Endereço da função hash.
 */
int(*HashTable_ABB_ObterHash(HashTable_ABB *tabela))(void *chave, int tam);

/**
 * Retorna o endereço da árvore de busca em uma posição da tabela.
 * @param  tabela HashTable_ABB na qual a árvore está.
 * @param  pos    Inteiro i, 0 <= i < tam, correspondente à posição da árvore na
 *                tabela hash.
 * @return        Endereço da árvore binária de busca na tabela hash.
 */
ABBusca *HashTable_ABB_ObterABBusca(HashTable_ABB *tabela, int pos);