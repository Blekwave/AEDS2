#include "BitString.h"
#include <math.h>
#include <stdlib.h>

////////////////////////////////
// Inicialização e destruição //
////////////////////////////////

/**
 * Inicializa uma bitstring.
 * @param  tamanho Tamanho, em BITS, da nova string.
 * @return         Endereço da BitString.
 */
BitString *BitString_Inicializar(int tamanho){
    BitString *nova = malloc(sizeof(BitString));
    nova->tamanho = tamanho;
    int num_blocos = (int)ceil((float)tamanho/CHUNKSIZE);
    nova->vetor = calloc(num_blocos, sizeof(chunk));
    return nova;
}

/**
 * Libera a memória associada à bitstring.
 * @param bitstring BitString a ser destruída.
 */
void BitString_Destruir(BitString *bitstring){
    free(bitstring->vetor);
    free(bitstring);
}

///////////////
// Interface //
///////////////

/**
 * Obtém o valor do bit de determinada ordinalidade.
 * @param  bitstring BitString na qual o bit está.
 * @param  pos       Posição do bit na string, de 0 a tamanho - 1
 * @return           Valor binário do bit.
 */
chunk BitString_ObterBit(BitString *bitstring, int pos){
    return (bitstring->vetor)[pos/CHUNKSIZE] >> pos % CHUNKSIZE & 1;
}

/**
 * Define o valor do bit de determinada ordinalidade.
 * @param bitstring BitString na qual o bit está.
 * @param pos       Posição do bit na string, de 0 a tamanho - 1
 * @param val       Novo valor binário do bit.
 */
void BitString_DefinirBit(BitString *bitstring, int pos, char val){
    if (val)
        (bitstring->vetor)[pos/CHUNKSIZE] |= 1 << pos % CHUNKSIZE;
    else
        (bitstring->vetor)[pos/CHUNKSIZE] &= ~(1 << pos % CHUNKSIZE);
}

/**
 * Obtém o tamanho, em bits, de uma bitstring.
 * @param  bitstring BitString da qual se quer saber o tamanho.
 * @return           Tamanho da bitstring.
 */
int BitString_ObterTamanho(BitString *bitstring){
    return bitstring->tamanho;
}

////////////////////////
// Operadores lógicos //
////////////////////////

/**
 * Realiza a bit a bit NOT em uma bitstring.
 * @param a     BitString A
 * @param saida BitString de tamanho maior ou igual ao de A já inicializada.
 */
void BitString_Not(BitString *a, BitString *saida){
    int i;
    for (i = 0; i <= (a->tamanho/CHUNKSIZE); i++)
        (saida->vetor)[i] = ~((a->vetor)[i]);
}

/**
 * Realiza a operação bit a bit AND entre duas bitstrings A e B. A deve ter com-
 * primento menor ou igual ao de B.
 * @param a     BitString A
 * @param b     BitString B
 * @param saida BitString de tamanho maior ou igual ao de A já inicializada.
 */
void BitString_And(BitString *a, BitString *b, BitString *saida){
    int i;
    for (i = 0; i <= (a->tamanho/CHUNKSIZE); i++)
        (saida->vetor)[i] = (a->vetor)[i] & (b->vetor)[i];
}

/**
 * Realiza a operação bit a bit OR entre duas bitstrings A e B. A deve ter com-
 * primento menor ou igual ao de B.
 * @param a     BitString A
 * @param b     BitString B
 * @param saida BitString de tamanho maior ou igual ao de A já inicializada.
 */
void BitString_Or(BitString *a, BitString *b, BitString *saida){
    int i;
    for (i = 0; i <= (a->tamanho/CHUNKSIZE); i++)
        (saida->vetor)[i] = (a->vetor)[i] | (b->vetor)[i];
}

/**
 * Realiza a operação bit a bit XOR entre duas bitstrings A e B. A deve ter com-
 * primento menor ou igual ao de B.
 * @param a     BitString A
 * @param b     BitString B
 * @param saida BitString de tamanho maior ou igual ao de A já inicializada.
 */
void BitString_Xor(BitString *a, BitString *b, BitString *saida){
    int i;
    for (i = 0; i <= (a->tamanho/CHUNKSIZE); i++)
        (saida->vetor)[i] = (a->vetor)[i] ^ (b->vetor)[i];
}

///////////
// Cópia //
///////////

/**
 * Copia uma BitString.
 * @param destino BitString de destino. Deve ter tamanho maior ou igual ao da
 *                origem.
 * @param origem  BitString de origem.
 */
void BitString_Copiar(BitString *destino, BitString *origem){
    int i;
    for (i = 0; i <= (origem->tamanho/CHUNKSIZE); i++)
        (destino->vetor)[i] = (origem->vetor)[i];
}
