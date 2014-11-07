#ifndef _BITSTRING_H_
#define _BITSTRING_H_

typedef char chunk;

typedef struct {
    chunk *vetor;
    int tam_bloco;
    int tamanho;
} BitString;

/**
 * Inicializa uma bitstring.
 * @param  tamanho Tamanho, em BITS, da nova string.
 * @return         Endereço da BitString.
 */
BitString *BitString_Inicializar(int tamanho);

/**
 * Libera a memória associada à bitstring.
 * @param bitstring BitString a ser destruída.
 */
void BitString_Destruir(BitString *bitstring);

/**
 * Obtém o valor do bit de determinada ordinalidade.
 * @param  bitstring BitString na qual o bit está.
 * @param  pos       Posição do bit na string, de 0 a tamanho - 1
 * @return           Valor binário do bit.
 */
chunk BitString_ObterBit(BitString *bitstring, int pos);

/**
 * Define o valor do bit de determinada ordinalidade.
 * @param bitstring BitString na qual o bit está.
 * @param pos       Posição do bit na string, de 0 a tamanho - 1
 * @param val       Novo valor binário do bit.
 */
void BitString_DefinirBit(BitString *bitstring, int pos, chunk val);

#endif
