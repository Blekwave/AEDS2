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
 * Nº de visualizações > Data de lançamento > Movie ID
 * @param  a Wrapper_Popularidade a ser comparado.
 * @param  b Wrapper_Popularidade a ser comparado.
 * @return   a > b
 */
bool Sugestoes_PopularidadeComparacao(void *a, void *b){
    Wrapper_Popularidade *x = (Wrapper_Popularidade *)a;
    Wrapper_Popularidade *y = (Wrapper_Popularidade *)b;
    return x->visualizacoes > y->visualizacoes || 
        (x->visualizacoes == y->visualizacoes && 
            (x->filme->ano > y->filme->ano || 
                (x->filme->ano == y->filme->ano && 
                    x->filme->movie_id > y->filme->movie_id)));
}

/**
 * Compara dois wrappers a e b, retorna verdadeiro se a é igual a b. Isso é feito
 * comparando seus movie_ids, já que eles são chaves únicas.
 * @param  a Wrapper_Popularidade a ser comparado.
 * @param  b Wrapper_Popularidade a ser comparado.
 * @return   a == b
 */
bool Sugestoes_PopularidadeIgualdade(void *a, void *b){
    return ((Wrapper_Popularidade *)a)->filme->movie_id == ((Wrapper_Popularidade *)b)->filme->movie_id;
}

/**
 * Retorna a posição na tabela hash em que um filme deve ser colocado.
 * @param  dados Endereço do Wrapper_Popularidade.
 * @param  tam   Tamanho da tabela hash.
 * @return       Posição i, 0 <= i < tam, na qual o wrapper deve se localizar na
 *               tabela hash.
 */
int Sugestoes_PopularidadeHash(void *dados, int tam){
    // Versão temporária muito, muito ruim
    return ((Wrapper_Popularidade *)dados)->visualizacoes % tam;
}

//////////////////
// Similaridade //
//////////////////

/**
 * Compara dois usuários a e b, retorna verdadeiro se a é maior que b, de acordo
 * com os critérios definidos no trabalho:
 * Coeficiente de Jaccard (chave) > User ID
 * @param  a Wrapper_Similaridade a ser comparado.
 * @param  b Wrapper_Similaridade a ser comparado.
 * @return   a > b
 */
bool Sugestoes_SimilaridadeComparacao(void *a, void *b){
    Wrapper_Similaridade *x = (Wrapper_Similaridade *)a;
    Wrapper_Similaridade *y = (Wrapper_Similaridade *)b;
    int comp_jaccard = Racional_Comparar(x->jaccard, y->jaccard);
    return comp_jaccard > 0 ||
        (comp_jaccard == 0 && x->usuario->user_id > y->usuario->user_id);
}

/**
 * Compara dois usuarios a e b, retorna verdadeiro se a é igual a b. Isso é feito
 * comparando seus user_ids, já que eles são chaves únicas.
 * @param  a Wrapper_Similaridade a ser comparado.
 * @param  b Wrapper_Similaridade a ser comparado.
 * @return   a == b
 */
bool Sugestoes_SimilaridadeIgualdade(void *a, void *b){
    return ((Wrapper_Similaridade *)a)->usuario->user_id == ((Wrapper_Similaridade *)b)->usuario->user_id;
}

/**
 * Retorna a posição na tabela hash em que um wrapper deve ser colocado.
 * @param  dados Endereço do Wrapper_Similaridade.
 * @param  tam   Tamanho da tabela hash.
 * @return       Posição i, 0 <= i < tam, na qual o usuario deve se localizar na
 *               tabela hash.
 */
int Sugestoes_SimilaridadeHash(void *dados, int tam){
    // Versão temporária muito, muito ruim
    Racional jaccard = ((Wrapper_Similaridade *)dados)->jaccard;
    return ((jaccard.num << 2) + jaccard.den) % tam;
}

///////////////////////////////
// SUGESTÃO POR POPULARIDADE //
///////////////////////////////

// Macro para obter o movie_id de um 'Nodo *' com 'Filme *' nos dados
#define indice_do_nodo(x) (*(int *)(x->dados))

/**
 * Gera um vetor de inteiros contendo as visualizações de cada filme, a partir
 * dos dados das listas de filmes visualizados por cada usuário.
 * @param  usuarios   Lista de usuários.
 * @param  num_filmes Número total de filmes.
 * @return            Endereço para o vetor de número de visualizações.
 */
int *Sugestoes_GerarVetorDeVisualizacoes(Lista *usuarios, int num_filmes){
    int *vetor = calloc(sizeof(int),num_filmes);
    Nodo *usuario_atual = Lista_ObterCabeca(usuarios);
    Nodo *filme_atual;

    // Itera pela lista de usuários
    while ((usuario_atual = Nodo_ObterProx(usuario_atual)) != NULL){
        filme_atual = Lista_ObterCabeca(
            Usuario_ObterAssistidos((Usuario *)Nodo_ObterDados(usuario_atual)));

        // Itera pela lista de filmes assistidos
        while ((filme_atual = Nodo_ObterProx(filme_atual)) != NULL)
            (vetor[indice_do_nodo(filme_atual)])++;
    }
    return vetor;
}

/**
 * Inicializa, preenche e retorna uma hash table contendo as sugestões por po-
 * popularidade de filmes para um conjunto de usuários. Gera, também, um vetor
 * de chaves únicas ordenadas (através de passagem do endereço do ponteiro)
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
        Sugestoes_PopularidadeComparacao, Sugestoes_PopularidadeIgualdade, Sugestoes_PopularidadeHash
    );
    
    // Inicializa variáveis temporárias e iteradores
    Nodo *nodo_atual = Lista_ObterPrimeiro(filmes);
    int i = 0;
    Wrapper_Popularidade *novo_filme;

    // Itera pela lista de filmes
    while (nodo_atual != NULL){
        int movie_id = Filme_ObterMovieID((Filme *)Nodo_ObterDados(nodo_atual));
        // Inicializa novo filme, copiando os dados da lista de filmes
        // Salva as visualizações de acordo com o vetor de visualizações
        novo_filme = Wrapper_Popularidade_Inicializar(
            visualizacoes[movie_id],
            (Filme *)Nodo_ObterDados(nodo_atual)
        );
        // printf("Filme de indice %d: %d views\n", i, visualizacoes[i]);
        HashTable_ABB_AdicionarElemento(tabela, (void *)novo_filme);
        i++;
        nodo_atual = Nodo_ObterProx(nodo_atual);
    }

    // Atribui ao ponteiro de vetor de chaves o vetor de visualizações
    *chaves = visualizacoes;
    return tabela;
}

#define int_nodo(x) (*(int *)x->dados)

///////////////////////////////
// SUGESTÃO POR SIMILARIDADE //
///////////////////////////////

/**
 * Calcula o coeficiente de Jaccard entre dois usuários.
 * @param  usuario_a Endereço de um usuário.
 * @param  usuario_b Endereço de outro usuário.
 * @return   Coeficiente de Jaccard entre dois usuários.
 */
Racional Sugestoes_Jaccard(Usuario *usuario_a, Usuario *usuario_b){
    Nodo *a = Lista_ObterPrimeiro(Usuario_ObterAssistidos(usuario_a));
    Nodo *b = Lista_ObterPrimeiro(Usuario_ObterAssistidos(usuario_b));

    // Itera pelas listas de filmes assistidos dos dois usuários
    // Avança na lista cujo ponteiro tem o filme de menor valor
    int intersecao = 0, uniao = 0;
    while (a != NULL || b != NULL){
        if (a != NULL && b != NULL){
            int val_a = int_nodo(a), val_b = int_nodo(b);
            if (val_a == val_b){
                // Ambos usuários assistiram o filme
                intersecao++;
                a = Nodo_ObterProx(a);
                b = Nodo_ObterProx(b);
            }
            else if (val_a < val_b)
                a = Nodo_ObterProx(a);
            else
                b = Nodo_ObterProx(b);
        }
        else if (a != NULL)
            a = Nodo_ObterProx(a);
        else
            b = Nodo_ObterProx(b);
        uniao++;
    }
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
        Sugestoes_SimilaridadeComparacao, Sugestoes_SimilaridadeIgualdade, Sugestoes_SimilaridadeHash);

    // Vetor com as chaves a ser retornado (através dos parâmetros)
    *chaves = (Racional *)calloc(sizeof(Racional), Lista_ObterTamanho(usuarios) - 1);
    int chaves_indice = 0;
    
    /////////////////////////////////////////////////////
    // Ok, o que diabos está acontecendo ali em baixo? //
    ///////////////////////////////////////////////////////////////////////////////
    // Essa função itera pela lista de usuários da base de dados.                //
    // Para cada usuário (com exceção do alvo), o programa adiciona à hash ta-   //
    // ble os filmes que o alvo não assistiu, usando o wrapper definido no ar-   //
    // quivo Sugestoes.h.                                                        //
    //                                                                           //
    // Ele faz isso passando pela lista de filmes assistidos do usuário alvo e   //
    // de cada outro usuário de forma síncrona. Começando do início de ambas as  //
    // listas, o programa vai avançando. Cada nodo das duas listas contém um va- //
    // lor inteiro correspondente a um filme. As listas estão ordenadas.         //
    //                                                                           //
    // O programa avança o ponteiro cujo nodo tem menor valor (atribuindo a ele  //
    // o valor de Nodo_ObterProx). Se o nodo apontado relativo ao usuário da     //
    // iteração (não o alvo) tem valor menor, o filme correspondente a esse va-  //
    // lor é adicionado à hash table. Se os dois tem o mesmo valor, ambos são    //
    // incrementados. Caso a lista de filmes do alvo acabe mas a do usuário da   //
    // iteração não, os filmes são adicionados (já que isso indica que o alvo    //
    // não os assistiu).                                                         //
    ///////////////////////////////////////////////////////////////////////////////

    Nodo *usuarios_nodo_atual = Lista_ObterCabeca(usuarios);
    while ((usuarios_nodo_atual = Nodo_ObterProx(usuarios_nodo_atual)) != NULL){
        Usuario *usuario_atual = (Usuario *)Nodo_ObterDados(usuarios_nodo_atual);

        if (usuario_atual != alvo){
            Racional jaccard = Sugestoes_Jaccard(alvo, usuario_atual);

            (*chaves)[chaves_indice] = jaccard;
            chaves_indice++;

            Nodo *usuario_assistido_atual = Lista_ObterPrimeiro(Usuario_ObterAssistidos(usuario_atual));
            Nodo *alvo_assistido_atual = Lista_ObterPrimeiro(Usuario_ObterAssistidos(alvo));
            Nodo *filmes_nodo_atual = Lista_ObterPrimeiro(filmes);

            // Posição numérica do ponteiro de nodo da lista de filmes.
            // Usado para obter o endereço do filme com base em um valor numéri-
            // co de forma relativamente eficiente.
            int i = 0;

            // Itera pela lista de filmes assistidos pelo usuário
            while (usuario_assistido_atual != NULL){
                int usuario_atual_val = int_nodo(usuario_assistido_atual);
                int alvo_atual_val;

                if (alvo_assistido_atual != NULL && 
                    (alvo_atual_val = int_nodo(alvo_assistido_atual)) <= usuario_atual_val){
                    // Casos em que não se adiciona um filme à hash table
                    if (usuario_atual_val == alvo_atual_val){
                        usuario_assistido_atual = Nodo_ObterProx(usuario_assistido_atual);
                        alvo_assistido_atual = Nodo_ObterProx(alvo_assistido_atual);
                    } else { // usuario_atual_val > alvo_atual_val
                        alvo_assistido_atual = Nodo_ObterProx(alvo_assistido_atual);
                    }
                } else {
                    // alvo_assistido_atual == NULL ou usuario_atual_val < alvo_atual_val
                    // Adiciona-se um filme à hash table

                    // Encontra na lista de filmes o filme 
                    while (i < usuario_atual_val){
                        filmes_nodo_atual = Nodo_ObterProx(filmes_nodo_atual);
                        i++;
                    }

                    // Adiciona novo filme
                    Wrapper_Similaridade *novo_filme = 
                        Wrapper_Similaridade_Inicializar(jaccard, usuario_atual, (Filme *)Nodo_ObterDados(filmes_nodo_atual));
                    HashTable_ABB_AdicionarElemento(tabela, (void *)novo_filme);

                    usuario_assistido_atual = Nodo_ObterProx(usuario_assistido_atual);
                }
            }
        }
    }
    return tabela;
}

///////////////
// IMPRESSÃO //
///////////////

#define SEPARADOR '\t'

/**
 * Imprime o título de um filme e uma tabulação em um arquivo.
 * @param filme   Filme.
 * @param arquivo Arquivo no qual será imprimido o título.
 */
static void ImprimirFilme(Filme *filme, FILE *arquivo){
    fprintf(arquivo, "%s%c", Filme_ObterTitulo(filme), SEPARADOR);
}

//////////////////
// Popularidade //
//////////////////

/**
 * Função auxiliar recursiva que imprime o conteúdo das árvores de busca binária da 
 * hash table das sugestões por popularidade. Percorre a árvore em ordem central.
 * @param raiz          Raiz da sub-árvore sendo imprimida.
 * @param assistidos    BitString que contém informações quanto a se um filme já
 *                      foi assistido pelo alvo ou imprimido na operação. O ín-
 *                      dice da bitstring é o movie_id de cada filme.
 * @param num_sugestoes Número de sugestões a serem imprimidas.
 * @param arquivo       Arquivo no qual os filmes serão imprimidos.
 */
static void ImprimirABBuscaPopularidade(ABNodo *raiz, BitString *assistidos, int *num_sugestoes, FILE *arquivo){
    if (raiz == NULL || *num_sugestoes <= 0)
        return;

    Wrapper_Popularidade *nodo_wrapper = (Wrapper_Popularidade *)ABNodo_ObterDados(raiz);

    ImprimirABBuscaPopularidade(ABNodo_ObterDir(raiz), assistidos, num_sugestoes, arquivo);

    // Não imprime um filme que já foi impresso
    if (BitString_ObterBit(assistidos, nodo_wrapper->filme->movie_id) == 0 && *num_sugestoes > 0){
        ImprimirFilme(nodo_wrapper->filme, arquivo);
        BitString_DefinirBit(assistidos, nodo_wrapper->filme->movie_id, 1);
        (*num_sugestoes)--;
    }

    if (*num_sugestoes > 0)
        ImprimirABBuscaPopularidade(ABNodo_ObterEsq(raiz), assistidos, num_sugestoes, arquivo);

}

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
    int num_chaves, Usuario *alvo, int num_sugestoes, FILE *arquivo){
    BitString *assistidos = BitString_Inicializar(num_chaves);

    // Preenche a lista de assistidos com os filmes que o alvo já assistiu
    Nodo *alvo_assistido_atual = Lista_ObterPrimeiro(Usuario_ObterAssistidos(alvo));

    while (alvo_assistido_atual != NULL){
        BitString_DefinirBit(assistidos, int_nodo(alvo_assistido_atual), 1);
        alvo_assistido_atual = Nodo_ObterProx(alvo_assistido_atual);
    }

    int chaves_indice = 0;
    int tabela_tam = HashTable_ABB_ObterTamanho(tabela);

    // Itera pelas chaves únicas da lista de chaves em ordem decrescente enquan-
    // to ainda há sugestões a serem feitas.
    while (num_sugestoes > 0 && chaves_indice < num_chaves){
        // Computa a posição da chave na tabela hash
        Wrapper_Popularidade wrapper = {chaves[chaves_indice], NULL};
        int pos = Sugestoes_PopularidadeHash(&wrapper, tabela_tam);
        // Determina a árvore correspondente à posição
        ABBusca *arvore = HashTable_ABB_ObterABBusca(tabela, pos);
        ImprimirABBuscaPopularidade(ABBusca_ObterRaiz(arvore), assistidos, &num_sugestoes, arquivo);
        chaves_indice++;
    }

    BitString_Destruir(assistidos);
}

//////////////////
// Similaridade //
//////////////////

/**
 * Função auxiliar recursiva que imprime o conteúdo das árvores de busca binária da 
 * hash table das sugestões por similaridade. Percorre a árvore em ordem central.
 * @param raiz          Raiz da sub-árvore sendo imprimida.
 * @param assistidos    BitString que contém informações quanto a se um filme já
 *                      foi assistido pelo alvo ou imprimido na operação. O ín-
 *                      dice da bitstring é o movie_id de cada filme.
 * @param num_sugestoes Número de sugestões a serem imprimidas.
 * @param arquivo       Arquivo no qual os filmes serão imprimidos.
 */
static void ImprimirABBuscaSimilaridade(ABNodo *raiz, BitString *assistidos, int *num_sugestoes, FILE *arquivo){
    if (raiz == NULL || *num_sugestoes <= 0){
        return;
    }

    Wrapper_Similaridade *nodo_wrapper = (Wrapper_Similaridade *)ABNodo_ObterDados(raiz);

    ImprimirABBuscaSimilaridade(ABNodo_ObterDir(raiz), assistidos, num_sugestoes, arquivo);

    // Não imprime um filme que já foi impresso
    if (BitString_ObterBit(assistidos, nodo_wrapper->filme->movie_id) == 0 && *num_sugestoes > 0){
        ImprimirFilme(nodo_wrapper->filme, arquivo);
        BitString_DefinirBit(assistidos, nodo_wrapper->filme->movie_id, 1);
        (*num_sugestoes)--;
    }

    if (*num_sugestoes > 0)
        ImprimirABBuscaSimilaridade(ABNodo_ObterEsq(raiz), assistidos, num_sugestoes, arquivo);

}

/**
 * Imprime as sugestões por similaridade para um usuário em particular.
 * @param tabela        Hash table que contém as sugestões por similaridade.
 * @param chaves        Vetor de chaves em ordem decrescente.
 * @param num_chaves    Número de chaves.
 * @param alvo          Usuário para o qual as sugestões são feitas.
 * @param num_sugestoes Número de sugestões a serem feitas.
 * @param arquivo       Arquivo no qual as sugestões serão impressas.
 */
void Sugestoes_ImprimirSimilaridade(HashTable_ABB *tabela, Racional *chaves,
    int num_chaves, Usuario *alvo, int num_sugestoes, int num_filmes, FILE *arquivo){
    BitString *assistidos = BitString_Inicializar(num_filmes);

    // Preenche a lista de assistidos com os filmes que o alvo já assistiu
    Nodo *alvo_assistido_atual = Lista_ObterPrimeiro(Usuario_ObterAssistidos(alvo));

    while (alvo_assistido_atual != NULL){
        BitString_DefinirBit(assistidos, int_nodo(alvo_assistido_atual), 1);
        alvo_assistido_atual = Nodo_ObterProx(alvo_assistido_atual);
    }

    int chaves_indice = 0;
    int tabela_tam = HashTable_ABB_ObterTamanho(tabela);

    // Itera pelas chaves únicas da lista de chaves em ordem decrescente enquan-
    // to ainda há sugestões a serem feitas.
    while (num_sugestoes > 0 && chaves_indice < num_chaves){
        // Computa a posição da chave na tabela hash
        Wrapper_Similaridade wrapper = {chaves[chaves_indice], NULL, NULL};
        int pos = Sugestoes_SimilaridadeHash(&wrapper, tabela_tam);
        // Determina a árvore correspondente à posição
        ABNodo *raiz = ABBusca_ObterRaiz(HashTable_ABB_ObterABBusca(tabela, pos));
        // printf("Chave = %d/%d, Pos = %d, Raiz = %p\n", chaves[chaves_indice].num, chaves[chaves_indice].den, pos, raiz);
        ImprimirABBuscaSimilaridade(raiz, assistidos, &num_sugestoes, arquivo);
        chaves_indice++;
    }
    BitString_Destruir(assistidos);
}
