TP1: Alocação de Memória
========================

Victor Pires Diniz - *[victorpiresdiniz@dcc.ufmg.br](mailto:victorpiresdiniz@dcc.ufmg.br)*

Algoritmos e Estruturas de Dados II - 2º Semestre de 2014

Introdução
----------

A alocação dinâmica de memória é um conceito essencial para a programação, sendo imprescindível quando é preciso lidar com estruturas de tamanho indefinido. Na linguagem C, é necessário utilizar funções que gerenciam a disponibilização de recursos ao programa.

Esse trabalho consiste em implementar uma biblioteca, `valloc.h`, que permita a alocação de memória. Isso é feito de forma análoga às funções da biblioteca padrão da linguagem C, (`malloc`, `calloc`, `realloc`, `free`) mas usando um vetor alocado estaticamente, ao invés da memória real do sistema.

Implementação
-------------

A memória a ser alocada pelo programa, como mencionado previamente, não é a memória integral do sistema. Essa implementação lida com um __vetor__ de `unsigned char`, gerenciando as posições ocupadas e livres do vetor em uma __lista duplamente encadeada__ auxiliar. No entanto, as funções tem exatamente o mesmo comportamento das funções da `stdlib.h`.

As únicas diferenças na utilização da biblioteca se referem à necessidade de inicialização e eliminação da lista auxiliar e do tamanho limitado disponível para alocação. (podendo, esse, ser modificado através de uma definição no cabeçalho da biblioteca)

### Funcionamento básico ###

Ao chamar uma função responsável por alocar um bloco da memória, essa função retorna um ponteiro para a primeira posição da memória alocada. Além disso, os metadados sobre a memória são armazenados na lista auxiliar, que contém, como cada nodo, um bloco de memória ocupada ou os trechos livres.

Ao liberar um bloco ocupado na memória, nada ocorre com a memória em si, mas a lista auxiliar é atualizada com o novo estado da memória, o que permite que o trecho liberado possa ser alocado novamente caso seja necessário.

### Sobre a lista auxiliar ###

A lista utilizada para gerir os metadados da biblioteca é uma lista duplamente encadeada chamada a partir da biblioteca `Ldenc.h`. Essa biblioteca contém uma implementação de lista duplamente encadeada genérica, utilizando ponteiros `void` e a biblioteca auxiliar `Ndenc.h`, que define o comportamento de cada nodo da lista. Nem toda a funcionalidade da lista foi necessária para a biblioteca, mas essa funcionalidade existe para torná-la mais versátil e permitir sua reutilização no futuro.

Cada nodo da lista contém um `memchunk`, que é um tipo definido através de um struct de apenas dois campos:

- `size_t size`: tamanho do bloco de memória;
- `bool used`: estado do bloco de memória.

Assim, quando a função de inicializar o gerenciamento da memória é chamada, a lista auxiliar é inicializada com apenas um nodo funcional contendo um `memchunk` vazio cujo tamanho é a memória inteira do programa. Quando é preciso alocar memória, são adicionados novos nodos, reduzindo o espaço livre adjacente ao novo nodo.

O programa contém várias funções auxiliares indisponíveis para o usuário final usadas para determinar, por exemplo, a posição da primeira lacuna livre de tamanho suficiente para a alocação requisitada. Essas funções não constam no arquivo `valloc.h`, mas estão propriamente documentadas no arquivo `valloc.c`.

### Comportamento das funções principais ###

#### valloc ####

```c
void *valloc(size_t tam);
```

Aloca um bloco de memória de tamanho `tam`. Se `tam` é zero ou não há espaço disponível suficiente para a alocação requisitada, a função retorna _NULL_. Se é possível realizar a alocação, a função retorna um endereço relativo à posição do início do bloco de memória alocado.

#### vcalloc ####

```c
void *vcalloc(size_t numBlocos, size_t tamBloco);
```

Aloca `numBlocos` blocos adjacentes de tamanho `tamBloco` e preenche os bits dos blocos alocados com zeros. Se `tamBloco` ou `numBlocos` é zero ou não há espaço disponível suficiente para a alocação requisitada, a função retorna _NULL_. Se é possível realizar a alocação, a função retorna um endereço relativo à posição do início do bloco de memória alocado.

#### vrealloc ####

```c
void *vrealloc(void *var, size_t tam);
```

Se `var` é um endereço nulo, a função aloca o espaço `tam`, se comportando como _vrealloc_. Se `tam` é zero, a função libera a memória em `var`, se comportando como _vfree_. Se os dois argumentos são válidos, a função modifica a memória alocada em `var` para o tamanho `tam`.

A função tenta manter o endereço original da alocação, se possível, movendo o bloco apenas se não é possível alocar o tamanho pedido na localização atual na memória. Os dados presentes são movidos para a nova localização. Se o novo tamanho é menor do que o previamente alocado, o final do bloco é truncado. Se o novo tamanho é maior, os dados do espaço recém-adicionado __não são inicializados__.

Se `var` não corresponde a um bloco alocado pela biblioteca, o comportamento é __indefinido__ pelo padrão C. No caso de não haver espaço suficiente para a alocação, a função retorna `NULL` e nada acontece. Se há sucesso na realocação, é retornado o endereço do bloco de memória após a realocação, podendo ser o mesmo valor de `var` ou um valor diferente.

#### vfree ####

```c
void vfree(void *var);
```

Libera a memória alocada previamente pela biblioteca cujo endereço do início do bloco é `var`, permitindo que o espaço seja alocado novamente por outras chamadas. Se `var` é um endereço nulo ou um endereço que não foi alocado pela biblioteca, nenhuma ação é tomada.

### Programa principal ###

Nesse trabalho, o programa principal é um interpretador que permite testar o comportamento da biblioteca através de um arquivo de entrada. Esse programa foi fornecido juntamente com a documentação e, por isso, dispensa análise.

### Detalhes técnicos ###

O programa foi compilado e testado no GCC 4.8.1 nos ambientes Windows (Windows 8.1/MinGW) e Linux (Cygwin/GCC). 

Análise de complexidade
-----------------------

### Ndenc.h ###

#### Funções de interface ####

- ObterProx
- ObterAnt
- ObterDados
- DefinirProx
- DefinirAnt
- DefinirDados

Essas funções apenas retornam ou atribuem a valores da estrutura de dados, servindo apenas como uma camada de abstração para o tipo abstrato de dados. A ordem de complexidade dessas funções é __O(1)__.

#### InicializarNdenc ####

Essa função apenas aloca a memória necessária para o nodo e inicializa seus valores. Sua ordem de complexidade é __O(1)__, por não conter nenhum laço de repetição ou chamada recursiva que pudesse levar a algum tipo de 


### Ldenc.h ###

Ordem de complexidade no pior caso em relação a acessos e operações na lista.

__n__: número de elementos da lista.

#### Funções de adição de elementos ####

- AdicionarElemento
- AdicionarAoInicio
- AdicionarAoFinal

As funções responsáveis por adicionar elementos à lista executam uma série de operações, mas sem nenhum loop ou estrutura que permita a repetição. Por isso, essas funções independem do tamanho da lista e apresentam ordem de complexidade __O(1)__.

#### Funções de remoção de elementos ####

- RemoverElemento
- RemoverElementoApos
- RemoverPrimeiroElemento
- RemoverUltimoElemento

Essas funções, similarmente às funções responsáveis por adicionar elementos à lista, não tem nenhum laço de repetição ou chamada recursiva, tendo, assim, tempo de execução independente do número de elementos da lista.

No entanto, devido ao caráter genérico da lista, há a possibilidade de chamar uma função desconhecida pela biblioteca para liberar o elemento removido, caso isso seja necessário, como se, por exemplo, o nodo contivesse outra lista. Dessa forma, a função tem ordem de complexidade __O(x)__, sendo _x_ a ordem de complexidade da função chamada (ou 1, caso não haja tal chamada, sendo passado _NULL_ como parâmetro).

#### Funções de interface ####

- ObterPrimeiro
- ObterUltimo
- ObterCabeca
- ObterAnterior
- ObterTamanho

As funções listadas tem o único propósito de adicionar uma camada de abstração ao programa, servindo como interface para dados já prontamente disponíveis na estrutura de dados. Por essa razão, a ordem de complexidade dessas funções é __O(1)__.

#### Funções de troca e deslocamento ####

- TrocarElementos
- TrocarDados
- DeslocarElemento

Essas funções, assim como as anteriores, não apresentam nenhum loop ou chamada recursiva, sendo, também, independentes do tamanho da lista. A ordem de complexidade dessas funções é, por isso, __O(1)__.

#### ObterElementoPorIndice ####

Essa função realiza uma operação de busca, passando por vários elementos da lista até alcançar o índice indicado. No pior caso, é necessário passar por todos os elementos da lista. Assim, trata-se de uma função com complexidade de ordem __O(n)__.

#### InicializarLdenc ####

A função realiza a alocação, inicialização da nova lista e adição do nodo cabeça (_InicializarNdenc_), que são operações que não envolvem nenhum laço de repetição. É desconsiderado o comportamento da função _malloc_, cuja ordem de complexidade não é necessariamente constante, mas não é relativa ao critério utilizado nessa análise. Dessa forma, em relação ao tamanho da lista, a função tem ordem de complexidade __O(1)__.

#### DestruirLdenc ####

A função chama a função _DestruirNdenc_ para cada nodo da lista. _DestruirNdenc_ também é utilizada para liberar o nodo cabeça, mas ela é chamada com o parâmetro da função auxiliar como _NULL_, o que faz com que, nesse caso, ela assuma ordem de complexidade _O(1)_. Considerando que _DestruirNdenc_ tem ordem de complexidade _O(x)_ no resto das situações:

O(_DestruirLdenc_) = O(_DestruirNdenc_)*n + 1
O(_DestruirLdenc_) = O(x)*n
O(_DestruirLdenc_) = O(nx)

Assim, a complexidade da função é __O(nx)__.

#### Resumo (Ldenc.h) ####

| Função                   | Ordem  |
|--------------------------|--------|
| InicializarLdenc         | O(1)   |
| AdicionarElemento        | O(1)   |
| AdicionarAoInicio        | O(1)   |
| AdicionarAoFinal         | O(1)   |
| RemoverElemento*         | O(x)   |
| RemoverElementoApos*     | O(x)   |
| RemoverPrimeiroElemento* | O(x)   |
| RemoverUltimoElemento*   | O(x)   |
| DeslocarElemento         | O(1)   |
| TrocarElementos          | O(1)   |
| TrocarDados              | O(1)   |
| ObterPrimeiro            | O(1)   |
| ObterUltimo              | O(1)   |
| ObterCabeca              | O(1)   |
| ObterAnterior            | O(1)   |
| ObterTamanho             | O(1)   |
| ObterElementoPorIndice   | O(n)   |
| AtravessarLdenc* **      | O(nx)  |
| InsertionSort* **        | O(n²x) |
| DestruirLdenc            | O(nx)  |

*As funções marcadas recebem como parâmetro um ponteiro de função. __x__, no caso, é a ordem de complexidade da função chamada.

**As funções marcadas não são usadas em nenhum momento no trabalho. Elas pertencem à biblioteca por serem úteis em outras circunstâncias. No entanto, elas não foram analisadas em detalhe nessa documentação.

### Valloc.h ###

Ordem de complexidade no pior caso em relação a acessos e operações na lista auxiliar.

__n__: número de elementos da lista auxiliar. 

#### Funções auxiliares ####

| Função              | Ordem |
|---------------------|-------|
| InicializarMemchunk | O(1)  |
| ObterMemchunk       | O(1)  |
| EncontrarLacuna     | O(n)  |
| EncontrarNodo       | O(n)  |
| EncontrarEndereco   | O(n)  |

#### Funções principais ####

| Função   | Ordem |
|----------|-------|
| valloc   | O(n)  |
| vcalloc  | O(n)  |
| vrealloc | O(n)  |
| vfree    | O(n)  |

#### Gerenciamento da lista auxiliar e saída ####

| Função                 | Ordem |
|------------------------|-------|
| inicializa_gerencia    | O(1)  |
| imprime_status_memoria | O(n)  |
| finaliza_gerencia      | O(n)  |