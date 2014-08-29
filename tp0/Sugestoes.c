#include <stdlib.h>
#include <stdio.h>
#include "Usuarios.h"
#include "Filme.h"

/*
 MOST POPULAR
 */
int *SugestaoPorPopularidade(Lista *usuarios, Filme *filmes, int numfilmes, int numsugestoes){
    bool *assistidos;
    Nodo *atual = ObterPrimeiro(usuarios);

    // Cria matriz com o número de visualizações de cada filmes
    int *soma = (int *) calloc(numfilmes, sizeof(int)), i;
    do {
        assistidos = ObterAssistidos((Usuario *) ObterDados(atual));
        for(i = 0; i < numfilmes; i++)
            soma[i] += assistidos[i];
        atual = ObterProx(atual);
    } while (atual != NULL);

    // Gera o vetor com os índices dos filmes mais populares
    int *saida = (int *) malloc(numsugestoes*sizeof(int)), maior, j, k, presente;

    // Escolha do filme mais popular
    for(i = 0; i < numsugestoes; i++){
        maior = 0;
        for (j = 1; j < numfilmes; j++){
            if (soma[j] > soma[maior] || ((soma[j] == soma[maior]) && (ObterAno(filmes[j]) > ObterAno(filmes[maior])))){
                presente = 0;
                // Checa se o filme de índice j já está presente na lista de saída
                for (k = 0; k < i; k++)
                    if (saida[k] == j)
                        presente = 1;
                if (!presente)
                    maior = j;
            }
        }
        saida[i] = maior;
    }

    free(soma);
    return saida;
}

/*
 PERSONALIZADA
 */
Usuario *ObterUsuarioMaisSimilar(Lista *usuarios, int numfilmes, int user_id){
    Usuario *usuario = BuscarUsuarioPorID(usuarios, user_id), *comparando, *maior = NULL;
    if (usuario == NULL)
        return NULL;
    Nodo *atual = ObterPrimeiro(usuarios);
    double maiorval = -1, temp;
    do {
        comparando = (Usuario *)ObterDados(atual);
        if (comparando != usuario){
            temp = Jaccard(usuario, comparando, numfilmes);
            if (temp > maiorval || (temp == maiorval && ObterID(comparando) < ObterID(maior))){
                maiorval = temp;
                maior = comparando;
            }
        }
    } while ((atual = ObterProx(atual)) != NULL);
    return maior;
}

void SelecionarFilmesMaisRecentes(Filme *filmes, int *saida, bool *assistidos, int numfilmes, int numsugestoes){
    int i, j, k, maior, presente;
    for(i = 0; i < numsugestoes; i++){
        maior = -1;
        // Seleciona maior filme
        for (j = 0; j < numfilmes; j++){
            if (assistidos[j] && (maior == -1 || ObterAno(filmes[j]) > ObterAno(filmes[maior]))){
                presente = 0;
                // Checa se o filme de índice j já está presente na lista de saída
                for (k = 0; k < i; k++)
                    if (saida[k] == j)
                        presente = 1;
                if (!presente)
                    maior = j;
            }
        }
        saida[i] = maior;
    }
}

int *SugestaoPorSimilaridade(Lista *usuarios, Filme *filmes, int numfilmes, int numsugestoes, int user_id){
    Usuario *similar = ObterUsuarioMaisSimilar(usuarios, numfilmes, user_id);
    if (similar == NULL)
        return NULL;
    int *saida = (int *)malloc(numsugestoes*sizeof(int));
    SelecionarFilmesMaisRecentes(filmes, saida, ObterAssistidos(similar), numfilmes, numsugestoes);
    return saida;    
}