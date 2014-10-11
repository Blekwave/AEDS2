#include "valloc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern unsigned char memoria[MAX_MEM];
Ldenc *auxiliar;

////////////////////////
// Funções auxiliares //
////////////////////////

memchunk *InicializarMemchunk(bool used, size_t size){
    memchunk *temp = (memchunk *)malloc(sizeof(memchunk));
    temp->used = used;
    temp->size = size;
    return temp;
}

memchunk *ObterMemchunk(Ndenc *nodo){
    return (memchunk *)ObterDados(nodo);
}

// Encontra lacuna no vetor MEM onde é possível alocar "tam" bytes
Ndenc *EncontrarLacuna(size_t tam){
    Ndenc *atual = ObterPrimeiro(auxiliar);
    // É seguro assumir que a lista auxiliar sempre tem pelo menos um elemento
    // Portanto, o do while abaixo não deve falhar em situação alguma
    while (atual != NULL && (ObterMemchunk(atual)->size < tam || ObterMemchunk(atual)->used == true))
        atual = ObterProx(atual);
    return atual;
}

// Encontra nodo na lista auxiliar correspondente ao endereço "ptr" em MEM
Ndenc *EncontrarNodo(void *ptr){
    unsigned char *init = memoria;
    Ndenc *atual = ObterPrimeiro(auxiliar);
    while (atual != NULL && init != ptr){
        init += ObterMemchunk(atual)->size; // Incrementa um ponteiro pelo tamanho de cada nodo
        atual = ObterProx(atual);
    }
    return atual;
}

// Encontra endereço em MEM correspondente ao nodo "nodo" na lista auxiliar
// (operação reversa de "EncontrarNodo")
unsigned char *EncontrarEndereco(Ndenc *nodo){
    unsigned char *init = memoria;
    Ndenc *atual = ObterPrimeiro(auxiliar);
     while (atual != NULL && atual != nodo){
        init += ObterMemchunk(atual)->size;
        atual = ObterProx(atual);
    }
    return init;
}

////////////////////////
// Funções principais //
////////////////////////

// (Propriamente documentadas no arquivo valloc.h)

void *valloc(size_t tam){
    /**
     * Encontra lacuna da qual possa ser alocado um bloco de memória de tamanho
     * tam. Adiciona novo nodo com memchunk de tamanho tam antes da lacuna e re-
     * duz o tamanho da lacuna por tam. Retorna endereço no vetor da memória 
     * alocada ou NULL, caso não seja possível alocar a memória.
     */
    if (tam > 0){
        Ndenc *lacuna = EncontrarLacuna(tam);
        if (lacuna != NULL){
            memchunk *temp = InicializarMemchunk(true, tam);
            Ndenc *novo = AdicionarElemento(auxiliar, ObterAnt(lacuna), (void *)temp);
            ObterMemchunk(lacuna)->size -= tam;
            if (ObterMemchunk(lacuna)->size == 0)
                RemoverElemento(auxiliar, lacuna, NULL);
            return (void *)EncontrarEndereco(novo);
        }
    }
    return NULL;
}

void *vcalloc(size_t num, size_t tam){
    unsigned char *pos = (unsigned char *)valloc(num*tam);
    if (pos != NULL){
        int i;
        for (i = 0; i < num*tam; i++)
            pos[i] = 0; // Zera elementos alocados
    }
    return (void *)pos;
}

void *vrealloc(void *var, size_t tam){
    if (tam == 0){
        vfree(var);
        return NULL;
    }
    if (var == NULL){
        return valloc(tam);
    }
    Ndenc *nodo = EncontrarNodo(var);
    if (nodo == NULL) // Comportamento indefinido na documentação do realloc
        return valloc(tam);
    Ndenc *prox = ObterProx(nodo);
    size_t tamanho_origem = ObterMemchunk(nodo)->size;
    int diferenca = tam - tamanho_origem;
    if (diferenca == 0) // Não é necessário realizar nenhuma operação
        return var;
    if (diferenca < 0){
        /////////////////////////////////////////////////////////////////////
        // Diferença negativa: redução do espaço alocado.                  //
        // Programa checa se o próximo nodo é espaço vazio.                //
        // Em caso afirmativo, ele reduz o nodo atual e aumenta o próximo. //
        // Caso contrário, é adicionado um novo nodo com o espaço liberado.//
        /////////////////////////////////////////////////////////////////////
        ObterMemchunk(nodo)->size = tam;
        if (prox != NULL && ObterMemchunk(prox)->used == false){
            ObterMemchunk(prox)->size -= diferenca;
        } else {
            memchunk *novo = InicializarMemchunk(false, (-1) * diferenca);
            AdicionarElemento(auxiliar, nodo, novo);
        }
        return var;
    }

    /////////////////////////////////////////////////////////////////////////
    // Diferença positiva: alocação de mais espaço.                        //
    // É, primeiro, checado se é possível realocar com o espaço adjacente. //
    // Em caso afirmativo, isso é feito. Caso contrário, a variável é      //
    // realocada para outro ponto da memória e seu conteúdo é movido.      //
    /////////////////////////////////////////////////////////////////////////
    if (prox != NULL){
        memchunk *prox_memchunk = ObterMemchunk(prox);
        if (prox_memchunk->used == false && diferenca <= prox_memchunk->size){
            ObterMemchunk(nodo)->size = tam;
            prox_memchunk->size -= diferenca;
            ///////////////////////////////////////////////////////////////////
            // Caso o elemento adjacente livre tenha exatamente o tamanho    //
            // necessário, ele deve ser removido, já que não deve haver ele- //
            // mentos de espaço zero na memória.                             //
            ///////////////////////////////////////////////////////////////////
            if (prox_memchunk->size == 0)
                RemoverElemento(auxiliar, prox, NULL);
            return var;
        }
    }
    void *novo = valloc(tam);
    if (novo != NULL){
        memmove(novo, var, tamanho_origem);
        vfree(var);
    }
    return novo;
}

void vfree(void *ptr){
    Ndenc *nodo;
    if (ptr == NULL || (nodo = EncontrarNodo(ptr)) == NULL) 
    // ptr não é um endereço alocado pela biblioteca se EncontrarNodo(ptr) == NULL
        return;
    memchunk *atual = ObterMemchunk(nodo);
    atual->used = false;
    Ndenc *ant = ObterAnt(nodo), *prox = ObterProx(nodo);
    // O código abaixo agrega os blocos de memória adjacentes ao bloco liberado.
    // Se o anterior de ant é NULL, ele é o nodo cabeça (que não tem um memchunk)
    if (ant != NULL && ObterAnt(ant) != NULL && ObterMemchunk(ant)->used == false){
        atual->size += ObterMemchunk(ObterAnt(nodo))->size;
        RemoverElemento(auxiliar, ObterAnt(nodo), NULL);
    }
    if (prox != NULL && ObterMemchunk(prox)->used == false){
        atual->size += ObterMemchunk(ObterProx(nodo))->size;
        RemoverElemento(auxiliar, ObterProx(nodo), NULL);
    }
}

/////////////////////////////////////////////
// Gerenciamento da lista auxiliar e saída //
/////////////////////////////////////////////

// Inicializa a lista auxiliar e adiciona nodo correspondente à memória total
void inicializa_gerencia(){
    auxiliar = InicializarLdenc();
    AdicionarAoInicio(auxiliar, (void *)InicializarMemchunk(false, MAX_MEM));
}

// Imprime posição, tamanho e estado de cada fragmento da memória disponível
void imprime_status_memoria(){
    Ndenc *atual = ObterPrimeiro(auxiliar);
    int pos = 0;
    memchunk *temp;
    printf("Status agora:\n");
    do {
        temp = ObterMemchunk(atual);
        printf("Pos: %d, Size: %zu, Status: %s\n", pos, temp->size, temp->used ? "USED" : "FREE");
        pos += temp->size;
    } while ((atual = ObterProx(atual)) != NULL);
}

// Finaliza a lista auxiliar
void finaliza_gerencia(){
    DestruirLdenc(auxiliar, NULL);
}