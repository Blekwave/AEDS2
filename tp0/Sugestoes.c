#include <stdlib.h>
#include <stdio.h>
#include "Usuarios.h"
#include "Filme.h"

//#define DEBUG_SOMA
//#define DEBUG_SAIDA
//#define DEBUG_ORDENACAO

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

    #ifdef DEBUG_SOMA
    for(i = 0; i < numfilmes; i++)
        printf("Filme de indice #%d: %d visualizacoes\n", i, soma[i]);
    #endif

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

        #ifdef DEBUG_ORDENACAO
        printf("Loop i = %d: [", i);
        for (j = 0; j < i+1; j++)
            printf("%d%s", saida[j], j == i ? "]\n" : ", ");
        #endif
    }

    #ifdef DEBUG_SAIDA
    for (i = 0; i < numsugestoes; i++)
        printf("Sugestao #%d: Filme de id %d\n", i, saida[i]);
    #endif

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

// void SelecionarFilmesMaisRecentes(Filme *filmes, int *saida, bool *assistidos, int numfilmes, int numsugestoes){
//     int i, j, k;
//     for (int i = 0; i < numsugestoes; i++)
//         saida[i] = -1;
//     for(i = 0; i < numfilmes; i++){
//         if (assistidos[i])
//             for(j = 0; j < numsugestoes; j++)
//                 if (saida[j] == -1){
//                     saida[j] = i;
//                     j = numsugestoes; // Quebra o loop
//                 }
//                 else if (ObterAno(filmes[i]) > ObterAno(filmes[saida[j]])){
//                     for(k = numsugestoes - 1; k > j; k--)
//                         saida[k] = saida[k-1];
//                     saida[j] = i;
//                     j = numsugestoes;
//                 }
//     }
// }

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