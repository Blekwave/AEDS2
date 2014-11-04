//#include "Sugestoes.h"
#include "HashTable_ABB.h"
#include "Filme.h"
#include "Usuario.h"
#include <stdlib.h>

//////////////////////////////////////
// Funções auxiliares da hash table //
//////////////////////////////////////

////////////
// Filmes //
////////////

/**
 * Compara dois filmes a e b, retorna verdadeiro se a é maior que b, de acordo
 * com os critérios definidos no trabalho:
 * Nº de visualizações > Data de lançamento > Movie ID
 * @param  a Filme a ser comparado.
 * @param  b Filme a ser comparado.
 * @return   a > b
 */
bool Sugestoes_FilmeComparacao(void *a, void *b){
    Filme *x = (Filme *)a;
    Filme *y = (Filme *)b;
    return x->visualizacoes > y->visualizacoes || 
        (x->visualizacoes == y->visualizacoes && 
            (x->ano > y->ano || 
                (x->ano == y->ano && 
                    x->movie_id > y->movie_id)));
}

/**
 * Compara dois filmes a e b, retorna verdadeiro se a é igual a b. Isso é feito
 * comparando seus movie_ids, já que eles são chaves únicas.
 * @param  a Filme a ser comparado.
 * @param  b Filme a ser comparado.
 * @return   a == b
 */
bool Sugestoes_FilmeIgualdade(void *a, void *b){
    return ((Filme *)a)->movie_id == ((Filme *)b)->movie_id;
}

/**
 * Retorna a posição na tabela hash em que um filme deve ser colocado.
 * @param  dados Endereço do filme.
 * @param  tam   Tamanho da tabela hash.
 * @return       Posição i, 0 <= i < tam, na qual o filme deve se localizar na
 *               tabela hash.
 */
int Sugestoes_FilmeHash(void *dados, int tam){
    // Versão temporária muito, muito ruim
    return (Filme_ObterVisualizacoes((Filme *)dados) % tam + tam) % tam;
}

//////////////
// Usuarios //
//////////////

/**
 * Compara dois usuários a e b, retorna verdadeiro se a é maior que b, de acordo
 * com os critérios definidos no trabalho:
 * Coeficiente de Jaccard (chave) > User ID
 * @param  a Usuario a ser comparado.
 * @param  b Usuario a ser comparado.
 * @return   a > b
 */
bool Sugestoes_UsuarioComparacao(void *a, void *b){
    Usuario *x = (Usuario *)a;
    Usuario *y = (Usuario *)b;
    return x->jaccard > y->jaccard ||
        (x->jaccard == y->jaccard && x->user_id > y->user_id);
}

/**
 * Compara dois usuarios a e b, retorna verdadeiro se a é igual a b. Isso é feito
 * comparando seus user_ids, já que eles são chaves únicas.
 * @param  a Usuario a ser comparado.
 * @param  b Usuario a ser comparado.
 * @return   a == b
 */
bool Sugestoes_UsuarioIgualdade(void *a, void *b){
    return ((Usuario *)a)->user_id == ((Usuario *)b)->user_id;
}

/**
 * Retorna a posição na tabela hash em que um usuario deve ser colocado.
 * @param  dados Endereço do usuario.
 * @param  tam   Tamanho da tabela hash.
 * @return       Posição i, 0 <= i < tam, na qual o usuario deve se localizar na
 *               tabela hash.
 */
int Sugestoes_UsuarioHash(void *dados, int tam){
    // Versão temporária muito, muito ruim
    return ((int *)Usuario_ObterJaccard((Usuario *)dados) % tam + tam) % tam;
}

///////////////////////////////
// SUGESTÃO POR POPULARIDADE //
///////////////////////////////

// Macro para obter o movie_id de um 'Nodo *' com 'Filme *' nos dados
#define movie_id_do_nodo(x) (((Filme *)x->dados)->movie_id)

/**
 * Gera um vetor de inteiros contendo as visualizações de cada filme, a partir
 * dos dados das listas de filmes visualizados por cada usuário.
 * @param  usuarios   Lista de usuários.
 * @param  num_filmes Número total de filmes.
 * @return            Endereço para o vetor de número de visualizações.
 */
int *Sugestoes_GerarVetorDeVisualizacoes(Lista *usuarios, int num_filmes){
    int *vetor = (int *)malloc(sizeof(int)*num_filmes);
    Nodo *usuario_atual = Lista_ObterCabeca(usuarios);
    Nodo *filme_atual;

    // Itera pela lista de usuários
    while ((usuario_atual = Nodo_ObterProx(usuario_atual)) != NULL){

        filme_atual = Lista_ObterCabeca(Usuario_ObterAssistidos(
            (Usuario *)ObterDados(usuario_atual)));
        // Itera pela lista de filmes assistidos
        while ((filme_atual = Nodo_ObterProx(filme_atual)) != NULL)
            (vetor[movie_id_do_nodo(filme_atual) - 1])++;
    }
    return vetor;
}

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
    Filme *novo_filme, *filme_atual;

    // Itera pela lista de filmes
    while ((nodo_atual = Nodo_ObterProx(nodo_atual)) != NULL){
        filme_atual = (Filme *)Nodo_ObterDados(nodo_atual);
        // Inicializa novo filme, copiando os dados da lista de filmes
        // Salva as visualizações de acordo com o vetor de visualizações
        novo_filme = Filme_Inicializar(
            Filme_ObterMovieID(filme_atual),
            Filme_ObterTitulo(filme_atual),
            Filme_ObterIMDBID(filme_atual),
            Filme_ObterAno(filme_atual),
            visualizacoes[i]
        );
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

#define int_nodo(x) (int *)x->dados

/**
 * Calcula o coeficiente de Jaccard entre dois usuários.
 * @param  a Endereço de um usuário.
 * @param  b Endereço de outro usuário.
 * @return   Coeficiente de Jaccard entre dois usuários.
 */
double Sugestoes_Jaccard(Usuario *a, Usuario *b){
    Nodo *filme_atual_a = Lista_ObterPrimeiro(Usuario_ObterAssistidos(a));
    Nodo *filme_atual_b = Lista_ObterPrimeiro(Usuario_ObterAssistidos(b));

    int intersecao = 0, uniao = 0;
    while (filme_atual_a != NULL && filme_atual_b != NULL){

    }
}

HashTable_ABB *Sugestoes_Similaridade(Lista *usuarios, Lista *filmes, Usuario *alvo,
    int tamanho_hash){

    // Inicializa hash table
    HashTable_ABB *tabela = HashTable_ABB_Inicializar(tamanho_hash
        Sugestoes_UsuarioComparacao, Sugestoes_UsuarioIgualdade, Sugestoes_UsuarioHash);

    Nodo *nodo_atual = Lista_ObterCabeca(usuarios);
    Usuario *novo_usuario, *usuario_atual;
    
    while ((nodo_atual = Nodo_ObterProx(nodo_atual)) != NULL){
        usuario_atual = (Usuario *)Nodo_ObterDados(nodo_atual);

        novo_usuario = Usuario_Inicializar(
            Usuario_ObterID(usuario_atual),
            Sugestoes_Jaccard(alvo, usuario_atual),

        )
    }

}
