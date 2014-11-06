#include "Sugestoes.h"
#include "Filme.h"
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

// Comentar isso
Wrapper_Similaridade *Wrapper_Similaridade_Inicializar(double jaccard, Usuario *usuario, Filme *filme){
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
    return x->jaccard > y->jaccard ||
        (x->jaccard == y->jaccard && x->usuario->user_id > y->usuario->user_id);
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
    return ((int)((Wrapper_Similaridade *)dados)->jaccard*1000) % tam;
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
            (vetor[indice_do_nodo(filme_atual) - 1])++;
    }
    return vetor;
}

#include <stdio.h>

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
    Nodo *nodo_atual = Lista_ObterCabeca(filmes);
    int i = 0;
    Wrapper_Popularidade *novo_filme;

    // Itera pela lista de filmes
    while ((nodo_atual = Nodo_ObterProx(nodo_atual)) != NULL){
        // Inicializa novo filme, copiando os dados da lista de filmes
        // Salva as visualizações de acordo com o vetor de visualizações
        novo_filme = Wrapper_Popularidade_Inicializar(
            visualizacoes[i],
            (Filme *)Nodo_ObterDados(nodo_atual)
        );
        // printf("Filme de indice %d: %d views\n", i, visualizacoes[i]);
        HashTable_ABB_AdicionarElemento(tabela, (void *)novo_filme);
        i++;
    }

    // Atribui ao ponteiro de vetor de chaves o vetor de visualizações
    *chaves = visualizacoes;
    return tabela;
}

///////////////////////////////
// SUGESTÃO POR SIMILARIDADE //
///////////////////////////////

#define int_nodo(x) (*(int *)x->dados)

/**
 * Calcula o coeficiente de Jaccard entre dois usuários.
 * @param  usuario_a Endereço de um usuário.
 * @param  usuario_b Endereço de outro usuário.
 * @return   Coeficiente de Jaccard entre dois usuários.
 */
double Sugestoes_Jaccard(Usuario *usuario_a, Usuario *usuario_b){
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
    return (double)intersecao/uniao;
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
    int tamanho_hash, double **chaves){

    // Inicializa hash table
    HashTable_ABB *tabela = HashTable_ABB_Inicializar(tamanho_hash,
        Sugestoes_SimilaridadeComparacao, Sugestoes_SimilaridadeIgualdade, Sugestoes_SimilaridadeHash);

    // Vetor com as chaves a ser retornado (através dos parâmetros)
    *chaves = (double *)calloc(sizeof(double), Lista_ObterTamanho(usuarios) - 1);
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
            double jaccard = Sugestoes_Jaccard(alvo, usuario_atual);
            (*chaves)[chaves_indice] = jaccard;

            Nodo *usuario_assistido_atual = Lista_ObterPrimeiro(Usuario_ObterAssistidos(usuario_atual));
            Nodo *alvo_assistido_atual = Lista_ObterPrimeiro(Usuario_ObterAssistidos(alvo));
            Nodo *filmes_nodo_atual = Lista_ObterPrimeiro(filmes);

            // Posição numérica do ponteiro de nodo da lista de filmes.
            // Usado para obter o endereço do filme com base em um valor numéri-
            // co de forma relativamente eficiente.
            int i = 1;

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
                    // Se adiciona um filme à hash table
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

/////////////////////////
// Ordenação de chaves //
/////////////////////////
