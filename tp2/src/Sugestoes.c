#include "Sugestoes.h"
#include "Filme.h"
#include "BitString.h"
#include "Racional.h"
#include <stdlib.h>
#include <stdio.h>

//////////////////////////////////
// Wrappers para as Hash Tables //
//////////////////////////////////

/**
 * Inicializa um wrapper para as sugestões por popularidade.
 * @param  visualizacoes Número de visualizações do filme.
 * @param  filme         Endereço do filme.
 * @return               Endereço do wrapper inicializado.
 */
Wrapper_Popularidade *Wrapper_Popularidade_Inicializar(int visualizacoes, Filme *filme){
	Wrapper_Popularidade *novo = malloc(sizeof(Wrapper_Popularidade));
	novo->visualizacoes = visualizacoes;
	novo->filme = filme;
	return novo;
}

/**
 * Inicializa um wrapper para as sugestões por similaridade.
 * @param  jaccard Coeficiente de jaccard.
 * @param  usuario Endereço do usuário que assistiu o filme.
 * @param  filme   Endereço do filme.
 * @return         Endereço do wrapper.
 */
Wrapper_Similaridade *Wrapper_Similaridade_Inicializar(Racional jaccard, Usuario *usuario, Filme *filme){
	Wrapper_Similaridade *novo = malloc(sizeof(Wrapper_Similaridade));
	novo->jaccard = jaccard;
	novo->usuario = usuario;
	novo->filme = filme;
	return novo;
}

//////////////////////////////////////
// Funções auxiliares da hash table //
//////////////////////////////////////

//////////////////
// Popularidade //
//////////////////

/**
 * Compara dois wrappers a e b, retorna verdadeiro se a é maior que b, de acordo
 * com os critérios definidos no trabalho:
 * Data de lançamento > Movie ID
 * @param  a Wrapper_Popularidade a ser comparado.
 * @param  b Wrapper_Popularidade a ser comparado.
 * @return   a > b
 */
bool Sugestoes_PopularidadeComparacao(void *a, void *b){
    Wrapper_Popularidade *x = a;
    Wrapper_Popularidade *y = b;
    return x->filme->ano > y->filme->ano || 
        (x->filme->ano == y->filme->ano && 
            x->filme->movie_id > y->filme->movie_id);
}

/**
 * Compara dois wrappers a e b, retorna verdadeiro se a é igual a b. Isso é feito
 * comparando seus movie_ids, já que eles são chaves únicas.
 * @param  a Wrapper_Popularidade a ser comparado.
 * @param  b Wrapper_Popularidade a ser comparado.
 * @return   a == b
 */
bool Sugestoes_PopularidadeIgualdade(void *a, void *b){
    return ((Wrapper_Popularidade *)a)->filme->movie_id ==
        ((Wrapper_Popularidade *)b)->filme->movie_id;
}

/**
 * Retorna a posição na tabela hash em que um filme deve ser colocado.
 * @param  dados Endereço do Wrapper_Popularidade.
 * @param  tam   Tamanho da tabela hash.
 * @return       Posição i, 0 <= i < tam, na qual o wrapper deve se localizar na
 *               tabela hash.
 */
int Sugestoes_PopularidadeHash(void *dados, int tam){
    return ((Wrapper_Popularidade *)dados)->visualizacoes % tam;
}

//////////////////
// Similaridade //
//////////////////

/**
 * Compara dois usuários a e b, retorna verdadeiro se a é maior que b, de acordo
 * com os critérios definidos no trabalho:
 * User ID
 * @param  a Wrapper_Similaridade a ser comparado.
 * @param  b Wrapper_Similaridade a ser comparado.
 * @return   a > b
 */
bool Sugestoes_SimilaridadeComparacao(void *a, void *b){
    Wrapper_Similaridade *x = a;
    Wrapper_Similaridade *y = b;
    return x->usuario->user_id > y->usuario->user_id ||
        (x->usuario->user_id == y->usuario->user_id &&
            (x->filme->ano > y->filme->ano ||
                (x->filme->ano == y->filme->ano &&
                    x->filme->movie_id > y->filme->movie_id)));
}

/**
 * Compara dois usuarios a e b, retorna verdadeiro se a é igual a b. Isso é feito
 * comparando seus user_ids, já que eles são chaves únicas.
 * @param  a Wrapper_Similaridade a ser comparado.
 * @param  b Wrapper_Similaridade a ser comparado.
 * @return   a == b
 */
bool Sugestoes_SimilaridadeIgualdade(void *a, void *b){
    return ((Wrapper_Similaridade *)a)->usuario->user_id == 
        ((Wrapper_Similaridade *)b)->usuario->user_id;
}

/**
 * Retorna a posição na tabela hash em que um wrapper deve ser colocado.
 * @param  dados Endereço do Wrapper_Similaridade.
 * @param  tam   Tamanho da tabela hash.
 * @return       Posição i, 0 <= i < tam, na qual o usuario deve se localizar na
 *               tabela hash.
 */
int Sugestoes_SimilaridadeHash(void *dados, int tam){
    Racional jaccard = ((Wrapper_Similaridade *)dados)->jaccard;
    return ((jaccard.num << 2) + jaccard.den) % tam;
}

///////////////////////////////
// SUGESTÃO POR POPULARIDADE //
///////////////////////////////

/**
 * Corrige a sub-árvore especificada, se necessário, para que ela seja um min-
 * -heap. Assume que as sub-árvores cujas raízes são os filhos dessa árvore já
 * são min-heaps.
 * @param v      Vetor de inteiros no qual o heap está.
 * @param inicio Posição da raiz dessa sub-árvore no vetor.
 * @param fim    Última posição válida do vetor.
 */
static void int_minheap(int *v, int inicio, int fim){
    int raiz = inicio;
    while ((raiz * 2 + 1) <= fim){
        int swap = raiz; // Variável que armazena posição a ser trocada
        int filho = raiz * 2 + 1; // Filho esquerdo
        if (v[filho] < v[swap])
            swap = filho;
        filho++; // Filho direito (pode não existir dentro dos limites)
        if (filho <= fim && v[filho] < v[swap])
            swap = filho;
        if (swap != raiz){
            int temp = v[swap];
            v[swap] = v[raiz];
            v[raiz] = temp;
            raiz = swap;
        }
        else
            return; // Raiz é maior que os filhos
    }
}

/**
 * Ordena o vetor em ordem decrescente com heapsort. Usado para ordenar o vetor
 * de chaves da sugestões por popularidade.
 * @param v     Vetor de inteiros.
 * @param v_tam Tamanho do vetor.
 */
static void HeapsortIntD(int *v, int v_tam){
    int i;
    for (i = (v_tam - 2)/2; i >= 0; i--)
        int_minheap(v, i, v_tam - 1);
    i = v_tam - 1;
    while (i > 0){
        int temp = v[0]; v[0] = v[i]; v[i] = temp; //swap
        i--;
        int_minheap(v, 0, i);
    }
}

// Macro para obter o movie_id de um 'Nodo *' com 'Filme *' nos dados
#define indice_do_nodo(x) (*(int *)(((Filme *)x)->dados))

/**
 * Gera um vetor de inteiros contendo as visualizações de cada filme, a partir
 * dos dados das bitstrings de filmes visualizados por cada usuário.
 * @param  usuarios   Lista de usuários.
 * @param  num_filmes Número total de filmes.
 * @return            Endereço para o vetor de número de visualizações.
 */
int *Sugestoes_GerarVetorDeVisualizacoes(Lista *usuarios, int num_filmes){
    int *vetor = calloc(sizeof(int),num_filmes);
    Nodo *nodo_atual = Lista_ObterPrimeiro(usuarios);

    // Itera pela lista de usuários
    while (nodo_atual != NULL){
        BitString *assistidos = Usuario_ObterAssistidos(Nodo_ObterDados(nodo_atual));

        int i;
        for (i = 0; i < num_filmes; i++)
            vetor[i] += BitString_ObterBit(assistidos, i);

        nodo_atual = Nodo_ObterProx(nodo_atual);
    }
    return vetor;
}

/**
 * Inicializa, preenche e retorna uma hash table contendo as sugestões por po-
 * popularidade de filmes para um conjunto de usuários. Gera, também, um vetor
 * de chaves únicas ordenadas. A chave dessa hash table é o número de visuali-
 * zações de cada filme.
 * @param  usuarios      Lista de usuários
 * @param  filmes        Lista de filmes
 * @param  tamanho_hash  Tamanho da hash table a ser gerada.
 * @param  chaves        Endereço do ponteiro no qual o vetor de chaves deverá
 *                       ser criado.
 * @return               Endereço da hash table.
 */
HashTable_ABB *Sugestoes_Popularidade(Lista *usuarios, Lista *filmes, 
    int tamanho_hash, int **chaves){
    // Obtém lista de visualizações
    int *visualizacoes = Sugestoes_GerarVetorDeVisualizacoes(usuarios, 
        Lista_ObterTamanho(filmes));

    // Inicializa hash table
    HashTable_ABB *tabela = HashTable_ABB_Inicializar(tamanho_hash,
        Sugestoes_PopularidadeComparacao, Sugestoes_PopularidadeIgualdade,
        Sugestoes_PopularidadeHash);
    
    // A lista de filmes está ordenada por movie_id em ordem crescente. Assim,
    // é possível determinar o movie_id apenas incrementando a variável abaixo.
    int movie_id = 0;

    // Itera pela lista de filmes
    Nodo *nodo_atual = Lista_ObterPrimeiro(filmes);
    while (nodo_atual != NULL){
        // Inicializa novo filme, copiando os dados da lista de filmes
        // Salva as visualizações de acordo com o vetor de visualizações
        Wrapper_Popularidade *novo_filme = Wrapper_Popularidade_Inicializar(
            visualizacoes[movie_id], Nodo_ObterDados(nodo_atual));
        HashTable_ABB_AdicionarElemento(tabela, novo_filme);
        movie_id++;
        nodo_atual = Nodo_ObterProx(nodo_atual);
    }

    *chaves = visualizacoes;
    HeapsortIntD(*chaves, Lista_ObterTamanho(filmes));

    return tabela;
}

#define int_nodo(x) (*(int *)x->dados)

///////////////////////////////
// SUGESTÃO POR SIMILARIDADE //
///////////////////////////////

/**
 * Corrige a sub-árvore especificada, se necessário, para que ela seja um min-
 * -heap. Assume que as sub-árvores cujas raízes são os filhos dessa árvore já
 * são min-heaps.
 * @param v      Vetor de números racionais no qual o heap está.
 * @param inicio Posição da raiz dessa sub-árvore no vetor.
 * @param fim    Última posição válida do vetor.
 */
static void racional_minheap(Racional *v, int inicio, int fim){
    int raiz = inicio;
    while ((raiz * 2 + 1) <= fim){
        int swap = raiz; // Variável que armazena posição a ser trocada
        int filho = raiz * 2 + 1; // Filho esquerdo
        if (Racional_Comparar(v[filho],v[swap]) < 0)
            swap = filho;
        filho++; // Filho direito (pode não existir dentro dos limites)
        if (filho <= fim && Racional_Comparar(v[filho],v[swap]) < 0)
            swap = filho;
        if (swap != raiz){
            Racional temp = v[swap];
            v[swap] = v[raiz];
            v[raiz] = temp;
            raiz = swap;
        }
        else
            return; // Raiz é maior que os filhos
    }
}

/**
 * Ordena o vetor em ordem decrescente com heapsort. Usado para ordenar o vetor
 * de chaves nas sugestões por similaridade.
 * @param v     Vetor de números racionais.
 * @param v_tam Tamanho do vetor.
 */
static void HeapsortRacionalD(Racional *v, int v_tam){
    int i;
    for (i = (v_tam - 2)/2; i >= 0; i--)
        racional_minheap(v, i, v_tam - 1);
    i = v_tam - 1;
    while (i > 0){
        Racional temp = v[0]; v[0] = v[i]; v[i] = temp; //swap
        i--;
        racional_minheap(v, 0, i);
    }
}

/**
 * Calcula o coeficiente de Jaccard entre dois usuários.
 * @param  usuario_a Endereço de um usuário.
 * @param  usuario_b Endereço de outro usuário.
 * @param  buffer    BitString inicializada de tamanho numfilmes usada como buf-
 *                   fer.
 * @return           Coeficiente de Jaccard entre dois usuários.
 */
Racional Sugestoes_Jaccard(Usuario *usuario_a, Usuario *usuario_b, 
    BitString *buffer){
    BitString *a = Usuario_ObterAssistidos(usuario_a);
    BitString *b = Usuario_ObterAssistidos(usuario_b);
    int i, max = BitString_ObterTamanho(a);

    BitString_And(a, b, buffer);
    int intersecao = 0;
    for (i = 0; i < max; i++)
        intersecao += BitString_ObterBit(buffer, i);

    BitString_Or(a, b, buffer);
    int uniao = 0;
    for (i = 0; i < max; i++)
        uniao += BitString_ObterBit(buffer, i);

    Racional jaccard;
    Racional_Definir(&jaccard, intersecao, uniao);
    return jaccard;
}

/**
 * Inicializa, preenche e retorna uma hash table contendo as sugestões por simi-
 * laridade entre uma base de usuários e um usuário alvo. Gera, também, um vetor
 * de chaves únicas ordenadas (através de passagem do endereço do ponteiro)
 * @param  usuarios     Lista de usuários
 * @param  filmes       Lista de filmes
 * @param  alvo         Usuário alvo
 * @param  tamanho_hash Tamanho da hash table
 * @param  chaves       Endereço do ponteiro no qual o vetor de chaves deverá
 *                      ser criado.
 * @return              Endereço da hash table
 */
HashTable_ABB *Sugestoes_Similaridade(Lista *usuarios, Lista *filmes, Usuario *alvo,
    int tamanho_hash, Racional **chaves){

    // Inicializa hash table
    HashTable_ABB *tabela = HashTable_ABB_Inicializar(tamanho_hash,
        Sugestoes_SimilaridadeComparacao, Sugestoes_SimilaridadeIgualdade,
        Sugestoes_SimilaridadeHash);

    // Vetor com as chaves a ser retornado (através dos parâmetros)
    *chaves = calloc(sizeof(Racional), Lista_ObterTamanho(usuarios) - 1);
    int chaves_indice = 0;

    int num_filmes = Lista_ObterTamanho(filmes);

    // Buffer utilizado para calcular Jaccard e armazenar atual_ass - alvo_ass
    BitString *buffer = BitString_Inicializar(num_filmes);

    BitString *alvo_assistidos = Usuario_ObterAssistidos(alvo);

    // Complemento utilizado para calcular atual_assistidos - alvo_assistidos
    BitString *complemento = BitString_Inicializar(num_filmes);
    BitString_Not(alvo_assistidos, complemento);

    // Itera pela lista de usuários
    Nodo *usuarios_nodo_atual = Lista_ObterPrimeiro(usuarios);
    while (usuarios_nodo_atual != NULL){
        Usuario *usuario_atual = (Usuario *)Nodo_ObterDados(usuarios_nodo_atual);
        if (usuario_atual != alvo){
            // Calcula o coeficiente de jaccard entre o alvo e o usuário atual
            // e o adiciona à lista de chaves da hash table.
            Racional jaccard = Sugestoes_Jaccard(alvo, usuario_atual, buffer);
            (*chaves)[chaves_indice] = jaccard;
            chaves_indice++;

            // // DEBUG
            // printf("Jaccard(%d,%d) = %d/%d = %f\n", alvo->user_id, usuario_atual->user_id,
            //     jaccard.num, jaccard.den, (double)jaccard.num/jaccard.den);

            // BitString *atual_assistidos = Usuario_ObterAssistidos(usuario_atual);
            
            // Os filmes não assistidos pelo alvo e assistidos pelo usuário atu-
            // al podem ser obtidos por uma subtração de conjuntos.
            // A - B = A & ~B
            BitString_And(atual_assistidos, complemento, buffer);

            // Itera pela lista de filmes assistidos pelo usuário
            Nodo *filmes_nodo_atual = Lista_ObterPrimeiro(filmes);
            int filmes_indice;
            for (filmes_indice = 0; filmes_indice < num_filmes; filmes_indice++){
                if (BitString_ObterBit(buffer, filmes_indice)){
                    // Adiciona novo filme se o alvo não o assistiu
                    Wrapper_Similaridade *novo_filme = 
                        Wrapper_Similaridade_Inicializar(jaccard, usuario_atual,
                            Nodo_ObterDados(filmes_nodo_atual));
                    HashTable_ABB_AdicionarElemento(tabela, novo_filme);
                }
                filmes_nodo_atual = Nodo_ObterProx(filmes_nodo_atual);
            }
        }
        usuarios_nodo_atual = Nodo_ObterProx(usuarios_nodo_atual);
    }

    BitString_Destruir(buffer);
    BitString_Destruir(complemento);

    HeapsortRacionalD(*chaves, Lista_ObterTamanho(usuarios) - 1);
    return tabela;
}
