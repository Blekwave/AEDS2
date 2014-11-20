#include "Arquivo.h"
#include "Lista.h"
#include "Usuario.h"
#include "Filme.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_USUARIO_TAM 2048
#define BUFFER_FILME_TAM 512
#define BUFFER_TITULO_TAM 128

/**
 * Preenche uma lista encadeada com os usuários lidos de um arquivo.
 * @param  end   Endereço do arquivo a ser lido.
 * @return       Endereço da lista encadeada inicializada (ou NULL)
 */
Lista *Arquivo_LerListaDeUsuarios(char *end, int num_filmes){
    FILE *arq = fopen(end, "r");
    if (arq == NULL)
        return NULL;

    char buffer[BUFFER_USUARIO_TAM]; // Buffer de leitura

    Lista *lista = Lista_Inicializar();

    // fgets retorna NULL em EOF
    while (fgets(buffer, BUFFER_USUARIO_TAM - 1, arq)){
        char *pch = strtok(buffer, " ");
        int user_id = atoi(pch);

        BitString *assistidos = BitString_Inicializar(num_filmes);
        // Preenche a bitstring de filmes assistidos
        while ((pch = strtok(NULL, " "))){
            BitString_DefinirBit(assistidos, atoi(pch), 1);
        }

        Usuario *usuario = Usuario_Inicializar(user_id, assistidos);
        Lista_AdicionarAoFinal(lista, usuario);
    }

    fclose(arq);
    return lista;
}


static void QuicksortFilmeC(Filme **vetor, int inicio, int fim){
    // Partição
    int p_i = inicio, p_f = fim;
    int pivo = (vetor[(inicio+fim)/2])->movie_id;
    while (p_i <= p_f){
        while ((vetor[p_i])->movie_id < pivo) p_i++;
        while ((vetor[p_f])->movie_id > pivo) p_f--;
        if (p_i <= p_f){
            Filme *temp = vetor[p_i];
            vetor[p_i] = vetor[p_f];
            vetor[p_f] = temp;
            p_i++;
            p_f--;
        }
    }
    // Chamada recursiva
    if (inicio < p_f)
        QuicksortFilmeC(vetor, inicio, p_f);
    if (p_i < fim)
        QuicksortFilmeC(vetor, p_i, fim);
}

/**
 * Ordena a lista de filmes usando um vetor auxiliar e quicksort. A ordenação é
 * feita em ordem crescente, tomando o movie_id dos filmes como critério.
 * @param lista Lista de Filmes criada por Arquivo_LerListaDeFilmes.
 */
static void OrdenarListaDeFilmes(Lista *lista){
    int vetor_tam = Lista_ObterTamanho(lista);
    Filme **vetor = malloc(sizeof(Filme *) * vetor_tam);

    // Itera pela lista de filmes, destruindo a lista e populando o vetor de
    // ponteiros de filme.
    Nodo *lista_nodo = Lista_ObterPrimeiro(lista);
    int i = 0;
    while (lista_nodo != NULL){
        vetor[i] = (Filme *)Nodo_ObterDados(lista_nodo);
        i++;
        Nodo *prox = Nodo_ObterProx(lista_nodo);
        free(lista_nodo);
        lista_nodo = prox;
    }

    // Redefine a lista como vazia
    lista->tamanho = 0;
    lista->ultimo = lista->cabeca;
    lista->cabeca->prox = NULL;

    // Ordena o vetor
    QuicksortFilmeC(vetor, 0, vetor_tam - 1);

    // Preenche novamente a lista, em ordem.
    for(i = 0; i < vetor_tam; i++)
        Lista_AdicionarAoFinal(lista, (void *)vetor[i]);

    free(vetor);
}

/**
 * Preenche uma lista encadeada com os filmes lidos de um arquivo. Ordena a
 * lista em ordem crescente por movie_id.
 * @param  end   Endereço do arquivo a ser lido.
 * @return       Endereço da lista encadeada inicializada (ou NULL)
 */
Lista *Arquivo_LerListaDeFilmes(char *end){
    FILE *arq = fopen(end, "r");
    if (arq == NULL)
        return NULL;

    // Buffers de leitura
    char buffer[BUFFER_FILME_TAM], titulo[BUFFER_TITULO_TAM];
    Filme *filme;
    int movie_id, imdb_id, ano;

    Lista *lista = Lista_Inicializar();

    // fgets retorna NULL em EOF
    while (fgets(buffer, BUFFER_FILME_TAM - 1, arq) != NULL){
        movie_id = atoi(strtok(buffer, "\t"));
        strcpy(titulo, strtok(NULL, "\t"));
        imdb_id = atoi(strtok(NULL, "\t"));
        ano = atoi(strtok(NULL, "\t"));

        filme = Filme_Inicializar(movie_id, titulo, imdb_id, ano);
        Lista_AdicionarAoFinal(lista, (void *)filme);
    }

    fclose(arq);

    OrdenarListaDeFilmes(lista);

    return lista;
}
