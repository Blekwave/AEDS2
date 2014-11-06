#include "Sugestoes.h"
#include "Filme.h"
#include <stdlib.h>

//////////////////////////////////////
// Funções auxiliares da hash table //
//////////////////////////////////////

// Wrappers

// Comentar isso
Wrapper_Popularidade *Wrapper_Popularidade_Inicializar(int visualizacoes, Filme *filme){
	Wrapper_Popularidade *novo = malloc(sizeof(Wrapper_Popularidade));
	novo->visualizacoes = visualizacoes;
	novo->filmes = filmes;
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
    return ((int)(Wrapper_Similaridade *)dados->jaccard*1000) % tam;
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
 * popularidade de filmes para um conjunto de usuários.
 * @param  usuarios      Lista de usuários
 * @param  filmes        Lista de filmes
 * @param  tamanho_hash  Tamanho da hash table a ser gerada.
 * @return               Endereço da hash table.
 */
HashTable_ABB *Sugestoes_Popularidade(Lista *usuarios, Lista *filmes, int tamanho_hash){
    // Obtém lista de visualizações
    int *visualizacoes = Sugestoes_GerarVetorDeVisualizacoes(usuarios, 
        Lista_ObterTamanho(filmes));

    // Inicializa hash table
    HashTable_ABB *tabela = HashTable_ABB_Inicializar(tamanho_hash,
        Sugestoes_FilmeComparacao, Sugestoes_FilmeIgualdade, Sugestoes_FilmeHash
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

    // Libera a memória da lista de visualizações, alocada no começo da função
    free(visualizacoes);
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

    int intersecao = 0, uniao = 0;
    while (a != NULL && b != NULL){
        if (a != NULL && b != NULL){
            int val_a = int_nodo(a), val_b = int_nodo(b);
            if (val_a == val_b){
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
 * laridade entre uma base de usuários e um usuário alvo.
 * @param  usuarios     Lista de usuários
 * @param  alvo         Usuário alvo
 * @param  tamanho_hash Tamanho da hash table
 * @return              Endereço da hash table
 */
HashTable_ABB *Sugestoes_Similaridade(Lista *usuarios, Usuario *alvo,
    int tamanho_hash){

    // Inicializa hash table
    HashTable_ABB *tabela = HashTable_ABB_Inicializar(tamanho_hash,
        Sugestoes_UsuarioComparacao, Sugestoes_UsuarioIgualdade, Sugestoes_UsuarioHash);

    Nodo *nodo_atual = Lista_ObterCabeca(usuarios);
    Wrapper_Similaridade *novo_filme;
    Usuario *usuario_atual;
    
    // Preenche a hash table com os usuários, definindo os valores de Jaccard
    while ((nodo_atual = Nodo_ObterProx(nodo_atual)) != NULL){
        usuario_atual = (Usuario *)Nodo_ObterDados(nodo_atual);

        novo_filme = Wrapper_Similaridade_Inicializar(
            Sugestoes_Jaccard(alvo, usuario_atual),
            (Usuario *)Nodo_ObterDados(nodo_atual),
            (Fi) // WIP
        );

        HashTable_ABB_AdicionarElemento(tabela, (void *)novo_usuario);
    }
    return tabela;
}
