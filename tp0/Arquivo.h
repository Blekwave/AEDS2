#ifndef _ARQUIVO_H_
#define _ARQUIVO_H_

int ObterNumFilmes(char *endereco);
Filme *LerFilmes(char *endereco, int numfilmes);
void DestruirListaDeFilmes(Filme *filmes, int numfilmes);
void DestruirListaDeUsuarios(Usuarios *lista);
Usuarios *LerUsuarios(char *endereco, int numfilmes);

#endif