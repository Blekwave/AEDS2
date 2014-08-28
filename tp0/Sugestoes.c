#include <stdlib.h>
#include <stdio.h>
#include "Usuarios.h"
#include "Filme.h"

/*
 MOST POPULAR
 */
int *SugestaoPorPopularidade(Usuarios *usuarios, Filme *filmes, int numfilmes, int numsugestoes){
    bool *assistidos;
    Usuario *atual = usuarios->primeiro;

    // Cria matriz com o número de visualizações de cada filmes
    int *soma = (int *)calloc(numfilmes, sizeof(int)), i;
    do {
        assistidos = ObterAssistidos(*atual);
        for(i = 0; i < numfilmes; i++)
            soma[i] += assistidos[i];
        atual = ObterProx(*atual);
    } while (atual != NULL);

    // Gera o vetor com os índices dos filmes mais populares
    int *saida = (int *)malloc(numsugestoes*sizeof(int)), maior, j, k, presente;

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
Usuario *ObterUsuarioMaisSimilar(Usuarios *usuarios, int numfilmes, int user_id){
    Usuario *usuario = BuscarUsuarioPorID(*usuarios, user_id);
    if (usuario == NULL)
        return NULL;
    Usuario *atual = usuarios->primeiro, *maior = NULL;
    double maiorval = -1, temp;
    do {
        if (atual != usuario){
            temp = Jaccard(*usuario, *atual, numfilmes);
            if (temp > maiorval || (temp == maiorval && ObterID(*atual) < ObterID(*maior))){
                maiorval = temp;
                maior = atual;
            }
        }
    } while ((atual = ObterProx(*atual)) != NULL);
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

int *SugestaoPorSimilaridade(Usuarios *usuarios, Filme *filmes, int numfilmes, int numsugestoes, int user_id){
    Usuario *similar = ObterUsuarioMaisSimilar(usuarios, numfilmes, user_id);
    if (similar == NULL)
        return NULL;
    int *saida = (int *)malloc(numsugestoes*sizeof(int));
    SelecionarFilmesMaisRecentes(filmes, saida, ObterAssistidos(*similar), numfilmes, numsugestoes);
    return saida;    
}