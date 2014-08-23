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
    int *saida = (int *)malloc(numsugestoes*sizeof(int)), maior, j, k;
    for (i = 0; i < numsugestoes; i++)
        saida[i] = -1;
    for(i = 0; i < numsugestoes; i++){
        // Escolha do filme mais popular
        maior = 0;
        for (j = 1; j < numfilmes; j++)
            if (soma[j] > soma[maior])
                maior = j;

        // Posicionamento do filme de acordo com a data de lançamento
        for (j = 0; j < numsugestoes; j++)
            if (saida[j] == -1){
                saida[j] = maior;
                j = numsugestoes; // Quebra o loop
            }
            else if (ObterAno(filmes[saida[j]]) < ObterAno(filmes[maior])){
                for(k = numsugestoes - 1; k > j; k--)
                    saida[k] = saida[k-1];
                saida[j] = maior;
                j = numsugestoes; // Quebra o loop
            }
        soma[maior] = -1;
    }

    //Debug
    for (i = 0; i < numsugestoes; i++)
        printf("%d: %s\n", saida[i], ObterTitulo(filmes[saida[i]]));

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
    int i, j, k;
    /*
    O procedimento abaixo checa os filmes assistidos pelo usuário de maior 
    similaridade. Se o filme foi assistido, ele, então, compara a data de 
    lançamento até encontrar um filme lançado antes do filme atual. Caso 
    todos os filmes presentes na saída sejam mais novos, nada acontece. Se é 
    possível encaixar o filme escolhido, os filmes posteriores na lista de 
    saída são deslocados um espaço para a frente e ele é, então adicionado, 
    descartando o último da lista. 
    */
    for (int i = 0; i < numsugestoes; i++)
        saida[i] = -1;
    for(i = 0; i < numfilmes; i++){
        if (assistidos[i])
            for(j = 0; j < numsugestoes; j++)
                if (saida[j] == -1){
                    saida[j] = i;
                    j = numsugestoes; // Quebra o loop
                }
                else if (ObterAno(filmes[i]) > ObterAno(filmes[saida[j]])){
                    for(k = numsugestoes - 1; k > j; k--)
                        saida[k] = saida[k-1];
                    saida[j] = i;
                    j = numsugestoes; // Quebra o loop
                }
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