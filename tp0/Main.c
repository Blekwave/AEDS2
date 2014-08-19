#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Filme.h"
#include "Usuarios.h"

#define BUFFER_TAMANHO 256
#define NUM_SUGESTOES 3
#define INPUT_ENDERECO "input.txt"
#define OUTPUT_ENDERECO "output.txt"

/*
 ARQUIVO E INICIALIZAÇÃO
 */

// char *endereco: endereço da lista de USUÁRIOS
int ObterNumFilmes(char *endereco){
    char ch;
    FILE *arquivo = fopen(endereco, "r");
    if (arquivo == NULL)
        return -1;
    int contagem = 0;
    while ((ch = fgetc(arquivo)) != '\n')
        if (ch == '\t')
            contagem++;
    fclose(arquivo);
    return contagem;
}

Filme *LerFilmes(char *endereco, int numfilmes){
    FILE *arquivo = fopen(endereco, "r");
    if (arquivo == NULL)
        return NULL;
    Filme *filmes = (Filme *)malloc(sizeof(Filme)*numfilmes);
    char buffer[BUFFER_TAMANHO], titulo[BUFFER_TAMANHO];
    char *pch;
    int movie_id, ano, imdb_id;
    fprintf(stderr, "Sera alocada memoria para %d filmes\n", numfilmes);
    for (int i = 0; i < numfilmes; i++){
        fgets(buffer, BUFFER_TAMANHO, arquivo);
        pch = strtok(buffer, "\t\n");
        movie_id = atoi(pch);
        pch = strtok(NULL, "\t\n");
        strcpy(titulo, pch);
        pch = strtok(NULL, "\t\n");
        imdb_id = atoi(pch);
        pch = strtok(NULL, "\t\n");
        ano = atoi(pch);
        InicializarFilme(&filmes[movie_id], movie_id, titulo, imdb_id, ano);
        fprintf(stderr, "%d, %s\n", movie_id, titulo);
    }
    fprintf(stderr, "Fim da inicializacao\n");
    fclose(arquivo);
    return filmes;
}

void DestruirListaDeFilmes(Filme *filmes, int numfilmes){
    for (int i = 0; i < numfilmes; i++)
        DestruirFilme(filmes[i]);
}

Usuarios *LerUsuarios(char *endereco, int numfilmes){
    FILE *arquivo = fopen(endereco, "r");
    if (arquivo == NULL)
        return NULL;
    Usuarios *lista = (Usuarios *)malloc(sizeof(Usuarios));
    InicializarListaDeUsuarios(lista);
    char buffer[BUFFER_TAMANHO];
    char *pch;
    int user_id, i;
    bool *assistidos;
    while (!feof(arquivo)){
        fgets(buffer, BUFFER_TAMANHO, arquivo);
        pch = strtok(buffer, "\t\n");
        user_id = atoi(pch);
        assistidos = (bool *) malloc(sizeof(bool)*numfilmes);
        pch = strtok(NULL, "\t\n");
        for (i = 0; pch != NULL; i++){
            assistidos[i] = atoi(pch);
            pch = strtok(NULL, "\t\n");
        }
        AdicionarUsuario(lista, user_id, assistidos);
    }
    fclose(arquivo);
    return lista;
}

/*
 MOST POPULAR
 */
int *SugestaoPorPopularidade(Usuarios *usuarios, int numfilmes, int numsugestoes){
    bool *assistidos;
    Usuario *atual = usuarios->primeiro;
    int *soma = (int *)calloc(numfilmes, sizeof(int)), i;
    do {
        assistidos = ObterAssistidos(*atual);
        for(i = 0; i < numfilmes; i++)
            soma[i] += assistidos[i];
    } while ((atual = ObterProx(*atual)) != NULL);
    int *saida = (int *)malloc(numsugestoes*sizeof(int)), maior, j;
    for(i = 0; i < numsugestoes; i++){
        maior = 0;
        for (j = 1; j < numfilmes; j++)
            if (soma[j] > soma[maior])
                maior = j;
        saida[i] = maior;
        soma[maior] = -1;
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
    Usuario *atual = usuarios->primeiro, *maior;
    double maiorval = 0, temp;
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

void SelecionarFilmesMaisRecentes(Filme *filmes, int *saida, Usuario *usuario, int numfilmes, int numsugestoes){
    int i, j, k;
    bool *assistidos = ObterAssistidos(*usuario);
    /*
    Ok, tô com dó de mim mesmo, vou comentar isso. O procedimento abaixo checa
    os filmes assistidos pelo usuário de maior similaridade. Se o filme foi
    assistido, ele, então, compara a data de lançamento até encontrar um filme
    lançado antes do filme atual. Caso todos os filmes presentes na saída sejam
    mais novos, nada acontece. Se é possível encaixar o filme escolhido, os 
    filmes posteriores na lista de saída são deslocados um espaço para a frente
    e ele é, então adicionado, descartando o último da lista.
     */
    for(i = 0; i < numfilmes; i++){
        if (assistidos[i])
            for(j = 0; j < numsugestoes; j++)
                if (ObterAno(filmes[i]) > ObterAno(filmes[saida[j]])){
                    for(k = numsugestoes - 1; k > j; k--)
                        saida[k] = saida[k-1]; // ÁREA DE RISCO
                    saida[j] = i;
                }
    }
}

int *SugestaoPorSimilaridade(Usuarios *usuarios, Filme *filmes, int numfilmes, int numsugestoes, int user_id){
    Usuario *similar = ObterUsuarioMaisSimilar(usuarios, numfilmes, user_id);
    if (similar == NULL)
        return NULL;
    int *saida = (int *)malloc(numsugestoes*sizeof(int));
    for (int i = 0; i < numsugestoes; i++)
        saida[i] = -1;
    SelecionarFilmesMaisRecentes(filmes, saida, similar, numfilmes, numsugestoes);
    return saida;    
}

int main(int argc, char const *argv[])
{
    FILE *input = fopen(INPUT_ENDERECO, "r");
    if (input == NULL){
        printf("Falha ao abrir arquivo de entrada %s.\n", INPUT_ENDERECO);
        exit(1);
    }
    FILE *output = fopen(OUTPUT_ENDERECO, "w");
    if (input == NULL){
        printf("Falha ao abrir arquivo de saida %s.\n", OUTPUT_ENDERECO);
        exit(1);
    }

    char usuarios_endereco[BUFFER_TAMANHO], filmes_endereco[BUFFER_TAMANHO], buffer[BUFFER_TAMANHO];
    char *pch;
    fgets(buffer, BUFFER_TAMANHO, input);
    pch = strtok(buffer, "\t\n");
    strcpy(filmes_endereco, pch);
    pch = strtok(NULL, "\t\n");
    strcpy(usuarios_endereco, pch);

    fprintf(stderr, "%s\t%s\n\n", filmes_endereco, usuarios_endereco);

    int numfilmes = ObterNumFilmes(usuarios_endereco);
    Usuarios *usuarios = LerUsuarios(usuarios_endereco, numfilmes);
    fprintf(stderr, "Vivo\n");
    Filme *filmes = LerFilmes(filmes_endereco, numfilmes);

    if (numfilmes == -1 || usuarios == NULL || filmes == NULL){
        printf("Falha na leitura das bases de dados indicadas.\n");
    } else {
        fprintf(output, "%s\t%s\n\n", filmes_endereco, usuarios_endereco);
    }

    // Sugestões por popularidade
    int *populares = SugestaoPorPopularidade(usuarios, numfilmes, NUM_SUGESTOES);
    fprintf(output,"Most popular\n");
    for (int i = 0; i < NUM_SUGESTOES; i++)
        fprintf(output, "%s%c", ObterTitulo(filmes[populares[i]]), i == NUM_SUGESTOES - 1 ? '\n' : '\t' );
    free(populares);

    // Sugestões personalizadas
    Usuario *atual = usuarios->primeiro;
    int *similaridade, user_id;
    fprintf(output, "\nPersonalizada\n");
    do {
        user_id = ObterID(*atual);
        fprintf(output, "%d: ", user_id);
        similaridade = SugestaoPorSimilaridade(usuarios, filmes, numfilmes, NUM_SUGESTOES, user_id);
        for (int i = 0; i < NUM_SUGESTOES; i++)
            fprintf(output, "%s%c", ObterTitulo(filmes[similaridade[i]]), i == NUM_SUGESTOES - 1 ? '\n' : '\t' );
        free(similaridade);
    } while ((atual = ObterProx(*atual)) != NULL);

    DestruirListaDeFilmes(filmes, numfilmes);
    DestruirListaDeUsuarios(usuarios);

    fclose(input);
    fclose(output);
    return 0;
}