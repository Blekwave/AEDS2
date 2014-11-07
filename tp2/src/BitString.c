#include "BitString.h"
#include <math.h>
#include <stdlib.h>

#define BYTE 8 // Tecnicamente eu deveria usar CHAR_BIT, mas pelo amor de deus.

/**
 * Inicializa uma bitstring.
 * @param  tamanho Tamanho, em BITS, da nova string.
 * @return         Endereço da BitString.
 */
BitString *BitString_Inicializar(int tamanho){
    BitString *nova = malloc(sizeof(BitString));
    nova->tamanho = tamanho;
    nova->tam_bloco = sizeof(chunk) * BYTE;
    int num_blocos = (int)ceil((float)tamanho/nova->tam_bloco);
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

#include <stdio.h>

/**
 * Obtém o valor do bit de determinada ordinalidade.
 * @param  bitstring BitString na qual o bit está.
 * @param  pos       Posição do bit na string, de 0 a tamanho - 1
 * @return           Valor binário do bit.
 */
chunk BitString_ObterBit(BitString *bitstring, int pos){
    return (bitstring->vetor)[pos/(bitstring->tam_bloco)] >> pos % (bitstring->tam_bloco) & 1 ;
}

/**
 * Define o valor do bit de determinada ordinalidade.
 * @param bitstring BitString na qual o bit está.
 * @param pos       Posição do bit na string, de 0 a tamanho - 1
 * @param val       Novo valor binário do bit.
 */
void BitString_DefinirBit(BitString *bitstring, int pos, chunk val){
    if (val)
        (bitstring->vetor)[pos/(bitstring->tam_bloco)] |= 1 << pos % (bitstring->tam_bloco);
    else
        (bitstring->vetor)[pos/(bitstring->tam_bloco)] &= ~(1 << pos % (bitstring->tam_bloco));
}