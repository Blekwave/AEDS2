#ifndef _SUGESTOES_H_
#define _SUGESTOES_H_

int *SugestaoPorPopularidade(Lista *usuarios, Filme *filmes, int numfilmes, int numsugestoes);
Usuario *ObterUsuarioMaisSimilar(Lista *usuarios, int numfilmes, int user_id);
void SelecionarFilmesMaisRecentes(Filme *filmes, int *saida, Usuario *usuario, int numfilmes, int numsugestoes);
int *SugestaoPorSimilaridade(Lista *usuarios, Filme *filmes, int numfilmes, int numsugestoes, int user_id);

#endif