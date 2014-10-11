TP1: Alocação de Memória
========================

Victor Pires Diniz - *[victorpiresdiniz@dcc.ufmg.br](mailto:victorpiresdiniz@dcc.ufmg.br)*

Algoritmos e Estruturas de Dados II - 2º Semestre de 2014

Índice
------

- [TP1: Alocação de Memória](#tp1-alocação-de-memória)
  - __Índice__
  - [Introdução](#introdução)
  - [Implementação](#implementação)
    - [Funcionamento básico](#funcionamento-básico)
    - [Sobre a lista auxiliar](#sobre-a-lista-auxiliar)
    - [Comportamento das funções principais](#comportamento-das-funções-principais)
      - [valloc](#valloc)
      - [vcalloc](#vcalloc)
      - [vrealloc](#vrealloc)
      - [vfree](#vfree)
    - [Programa principal](#programa-principal)
    - [Detalhes técnicos](#detalhes-técnicos)
  - [Análise de complexidade](#análise-de-complexidade)
    - [Ndenc.h](#ndench)
      - [Funções de interface](#funções-de-interface)
      - [InicializarNdenc](#inicializarndenc)
      - [DestruirNdenc](#destruirndenc)
      - [Resumo (Ndenc.h)](#resumo-ndench)
    - [Ldenc.h](#ldench)
      - [Funções de adição de elementos](#funções-de-adição-de-elementos)
      - [Funções de remoção de elementos](#funções-de-remoção-de-elementos)
      - [Funções de interface](#funções-de-interface-1)
      - [Funções de troca e deslocamento](#funções-de-troca-e-deslocamento)
      - [ObterElementoPorIndice](#obterelementoporindice)
      - [InicializarLdenc](#inicializarldenc)
      - [DestruirLdenc](#destruirldenc)
      - [Resumo (Ldenc.h)](#resumo-ldench)
    - [Valloc.h](#valloch)
      - [Funções auxiliares](#funções-auxiliares)
        - [InicializarMemchunk](#inicializarmemchunk)
        - [ObterMemchunk](#obtermemchunk)
        - [Funções de busca ou travessia](#funções-de-busca-ou-travessia)
        - [Resumo (valloc.h/auxiliares)](#resumo-vallochauxiliares)
      - [Funções principais](#funções-principais)
        - [valloc](#valloc-1)
        - [vcalloc](#vcalloc-1)
        - [vrealloc](#vrealloc-1)
        - [vfree](#vfree-1)
        - [Resumo (valloc.h/principais)](#resumo-vallochprincipais)
      - [Gerenciamento da lista auxiliar e saída](#gerenciamento-da-lista-auxiliar-e-saída)
        - [inicializa\_gerencia](#inicializa\_gerencia)
        - [imprime_status_memoria](#imprime_status_memoria)
        - [finaliza\_gerencia](#finaliza\_gerencia)
        - [Resumo (valloc.h/aux)](#resumo-vallochaux)
  - [Testes](#testes)
    - [Sintaxe do interpretador](#sintaxe-do-interpretador)
    - [Testes realizados](#testes-realizados)
      - [Testes de terceiros](#testes-de-terceiros)
        - [1.tst.i](#1tsti)
        - [11.tst.i](#11tsti)
        - [12.tst.i](#12tsti)
      - [Testes de minha autoria](#testes-de-minha-autoria)
        - [t1.i](#t1i)
        - [t2.i](#t2i)
      - [Teste adicional: uso da memória](#teste-adicional-uso-da-memória)
        - [teste1.c](#teste1c)
  - [Conclusão](#conclusão)
  - [Anexos](#anexos)
    - [Listagem dos programas](#listagem-dos-programas)

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

Nesse trabalho, o programa principal é um interpretador que permite testar o comportamento da biblioteca através de um arquivo de entrada. Ele é analisado em mais detalhes na seção de testes dessa documentação.

### Detalhes técnicos ###

Esse programa está dividido em três bibliotecas, (`valloc`, `Ldenc`, `Ndenc`) contendo, cada uma, um arquivo `.c` e um arquivo `.h`, além do programa principal `main.c`. `Ldenc` é responsável por implementar o TAD da lista duplamente encadeada, usando `Ndenc` e a sua implementação de nodo para isso.

`valloc` é a parte principal do trabalho, responsável pela implementação do sistema de alocação dinâmica de memória. Essa biblioteca também implementa um TAD rudimentar `memchunk` para auxiliar no gerenciamento da memória alocada.

O programa foi compilado e testado no GCC 4.8.1 nos ambientes Windows (Windows 8.1/MinGW) e Linux (Cygwin/GCC). Ele pode ser compilado em qualquer um desses ambientes com o seguinte comando:

    gcc main.c valloc.c Ldenc.c Ndenc.c -o TP1 -Wall

A execução do programa, então, pode ser efetuada chamando o mesmo pela linha de comando e passando como parâmetro um arquivo de texto contendo a entrada do interpretador: (mais detalhes na seção de testes)

    ./TP1 input.txt

Análise de complexidade
-----------------------

Ordem de complexidade no pior caso em função das operações e acessos a elementos da estrutura de dados.

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

Essa função apenas aloca a memória necessária para o nodo e inicializa seus valores. Sua ordem de complexidade é __O(1)__, por não conter nenhum laço de repetição ou chamada recursiva.

#### DestruirNdenc ####

A função _DestruirNdenc_, à primeira vista, aparenta ser uma função que roda em tempo constante, por não conter estruturas que permitam a repetição. No entanto, ela pode realizar uma chamada a outra função passada através de um ponteiro por um de seus argumentos. Por esse motivo, a complexidade dessa função é __O(x)__, sendo _x_ a ordem de complexidade da função chamada. Caso não seja chamada nenhuma função, _DestruirNdenc_ opera em tempo constante.

#### Resumo (Ndenc.h) ####

| Função           | Ordem |
|------------------|-------|
| ObterProx        | O(1)  |
| DefinirProx      | O(1)  |
| ObterAnt         | O(1)  |
| DefinirAnt       | O(1)  |
| ObterDados       | O(1)  |
| DefinirDados     | O(1)  |
| InicializarNdenc | O(1)  |
| DestruirNdenc*   | O(x)  |

*As funções marcadas recebem como parâmetro um ponteiro de função. __x__, no caso, é a ordem de complexidade da função chamada.

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

##### InicializarMemchunk #####

Apenas realiza operações na estrutura de dados e aloca memória. Similarmente a _InicializarNdenc_, tem ordem de complexidade __O(1)__.

##### ObterMemchunk #####

Opera como camada de abstração, sem executar nenhum loop ou chamada recursiva. Tem ordem de complexidade __O(1)__.

##### Funções de busca ou travessia #####

- EncontrarLacuna
- EncontrarNodo
- EncontrarEndereco

Essas funções se comportam similarmente no sentido em que todas elas percorrem os elementos da lista auxiliar até encontrar um certo item, de acordo com um critério em particular. Isso caracteriza uma operação de busca em lista, que, por passar, em pior caso, por todos os _n_ elementos da lista, tem ordem de complexidade __O(n)__.

##### Resumo (valloc.h/auxiliares) #####

| Função              | Ordem |
|---------------------|-------|
| InicializarMemchunk | O(1)  |
| ObterMemchunk       | O(1)  |
| EncontrarLacuna     | O(n)  |
| EncontrarNodo       | O(n)  |
| EncontrarEndereco   | O(n)  |

#### Funções principais ####

##### valloc #####

O pior caso da função _valloc_ ocorre quando ela encontra uma lacuna válida e aloca, de fato, a memória. Nesse caso, são feitas chamadas a várias funções, mas ainda sem nenhum laço de repetição ou chamada recursiva. As funções de maior ordem de complexidade chamadas são _EncontrarLacuna_ e _EncontrarEndereco_, ambas de ordem _O(n)_. Assim, a ordem de complexidade em pior caso da função _valloc_ é __O(n)__.

##### vcalloc #####

A função _vcalloc_ apenas realiza uma chamada a _valloc_ e zera os elementos no vetor da memória. Ambos os procedimentos operam em tempo linear, e, portanto, a função tem ordem de complexidade __O(n)__.

##### vrealloc #####

A função _vrealloc_ não contém laços de repetição ou chamadas recursivas, realizando apenas uma série de operações. As funções de maior ordem de complexidade chamadas são _EncontrarNodo_ e _memmove_, que operam ambas em tempo linear. Nesse sentido, _vrealloc_ tem ordem de complexidade __O(n)__.

##### vfree #####

Assim como as funções anteriores, essa função não contém loops ou chamadas recursivas. A função de maior ordem de complexidade presente, no caso, é _EncontrarNodo_, função _O(n)_. Dessa forma, _vfree_ tem ordem de complexidade __O(n)__.

##### Resumo (valloc.h/principais) #####

| Função   | Ordem |
|----------|-------|
| valloc   | O(n)  |
| vcalloc  | O(n)  |
| vrealloc | O(n)  |
| vfree    | O(n)  |

#### Gerenciamento da lista auxiliar e saída ####

##### inicializa\_gerencia #####

Essa função apenas realiza chamadas a _InicializarLdenc_, _AdicionarAoInicio_ e _InicializarMemchunk_, que operam em tempo constante. Não há loops ou chamadas recursivas, o que faz com que _inicializa\_gerencia_ tenha ordem de complexidade __O(1)__.

##### imprime_status_memoria #####

Essa função apenas realiza chamadas a funções que operam em tempo constante. No entanto, ela tem um loop, percorrendo toda a extensão da lista auxiliar, no qual ela realiza operações relevantes. Assim, a função tem ordem de complexidade __O(n)__.

##### finaliza\_gerencia #####

A única operação realizada por essa função é uma chamada a _DestruirLdenc_, destruindo a lista auxiliar sem usar uma função auxiliar para fazê-lo. Nesse contexto, _DestruirLdenc_ tem ordem de complexidade _O(n)_, e, por isso, a ordem de complexidade de _finaliza\_gerencia_ é __O(n)__.


##### Resumo (valloc.h/aux) #####

| Função                 | Ordem |
|------------------------|-------|
| inicializa_gerencia    | O(1)  |
| imprime_status_memoria | O(n)  |
| finaliza_gerencia      | O(n)  |

Testes
------

A maior parte dos testes foram realizados através da entrada do programa principal fornecido, que é um intepretador construído para realizar testes com a biblioteca _valloc.h_.

### Sintaxe do interpretador ###

O programa principal lê sua entrada a partir de um arquivo de texto, especificado como parâmetro do programa. A primeira linha desse arquivo determina quantas variáveis serão utilizadas no teste, através do comando `VAR NUM`, sendo `NUM` o número de variáveis. As variáveis podem, então, ser acessadas nos outros comandos do interpretador como `VX`, substituindo-se `X` por um número de 0 a `NUM` - 1.

A partir daí, as linhas seguintes determinam qual função será chamada, quais os seus parâmetros e a qual variável será atribuída sua saída, de acordo com a sintaxe abaixo:

- `VALLOC TAM VAR`: chama a função `valloc` com tamanho `TAM` e atribui sua saída a `VAR`;
- `VCALLOC TAMBLOCO NUMBLOCOS VAR`: chama a função `vcalloc` com tamanho de bloco  `TAMBLOCO`, número de blocos `NUMBLOCOS` e atribui sua saída a `VAR`;
- `VREALLOC TAM VAR`: chama a função `vrealloc` com endereço `VAR`, tamanho `TAM` e atribui sua saída a `VAR`;
- `VFREE VAR`: chama a função `vfree` com endereço `VAR`;
- `PRINT`: chama a função `imprime_status_memoria`.

É importante que haja apenas uma linha em branco no programa, ao final. Caso essa linha não esteja presente, o último comando não será lido. Se houver alguma linha em branco além dessa, o programa pode apresentar uma falha de segmentação.

### Testes realizados ###

#### Testes de terceiros ####

Os testes abaixo foram fornecidos pela monitoria ou pelos professores.

##### 1.tst.i #####

__Entrada:__

```
VAR 2
PRINT
VALLOC 10 V0
PRINT
VCALLOC 10 2 V1
PRINT
VREALLOC 20 V0
PRINT
VFREE V0
VFREE V1
PRINT

```

__Saída:__

```
VAR 2
Status agora:
Pos: 0, Size: 1024576, Status: FREE

VALLOC 10 V0    OK
Status agora:
Pos: 0, Size: 10, Status: USED
Pos: 10, Size: 1024566, Status: FREE

VCALLOC 10 2 V1 OK
Status agora:
Pos: 0, Size: 10, Status: USED
Pos: 10, Size: 20, Status: USED
Pos: 30, Size: 1024546, Status: FREE

VREALLOC 20 V0  OK
Status agora:
Pos: 0, Size: 10, Status: FREE
Pos: 10, Size: 20, Status: USED
Pos: 30, Size: 20, Status: USED
Pos: 50, Size: 1024526, Status: FREE

VFREE 0

VFREE 1
Status agora:
Pos: 0, Size: 1024576, Status: FREE

```

##### 11.tst.i #####

__Entrada:__

```
VAR 2
PRINT
VALLOC 20 V0
PRINT
VCALLOC 10 2 V1
PRINT
VREALLOC 30 V0
PRINT
VFREE V1
PRINT
VALLOC 40 V1
PRINT
VFREE V0
PRINT
VCALLOC 15 2 V0
PRINT
VREALLOC 60 V0
PRINT
VREALLOC 10 V0
PRINT
VREALLOC 1 V1
PRINT
VREALLOC 10 V1
PRINT
VREALLOC 0 V1
PRINT
VFREE V1
PRINT
VALLOC 1024577 V1
PRINT
VFREE V0
PRINT
VFREE V1
PRINT

```

__Saída:__

```
VAR 2
Status agora:
Pos: 0, Size: 1024576, Status: FREE

VALLOC 20 V0    OK
Status agora:
Pos: 0, Size: 20, Status: USED
Pos: 20, Size: 1024556, Status: FREE

VCALLOC 10 2 V1 OK
Status agora:
Pos: 0, Size: 20, Status: USED
Pos: 20, Size: 20, Status: USED
Pos: 40, Size: 1024536, Status: FREE

VREALLOC 30 V0  OK
Status agora:
Pos: 0, Size: 20, Status: FREE
Pos: 20, Size: 20, Status: USED
Pos: 40, Size: 30, Status: USED
Pos: 70, Size: 1024506, Status: FREE

VFREE 1
Status agora:
Pos: 0, Size: 40, Status: FREE
Pos: 40, Size: 30, Status: USED
Pos: 70, Size: 1024506, Status: FREE

VALLOC 40 V1    OK
Status agora:
Pos: 0, Size: 40, Status: USED
Pos: 40, Size: 30, Status: USED
Pos: 70, Size: 1024506, Status: FREE

VFREE 0
Status agora:
Pos: 0, Size: 40, Status: USED
Pos: 40, Size: 1024536, Status: FREE

VCALLOC 15 2 V0 OK
Status agora:
Pos: 0, Size: 40, Status: USED
Pos: 40, Size: 30, Status: USED
Pos: 70, Size: 1024506, Status: FREE

VREALLOC 60 V0  OK
Status agora:
Pos: 0, Size: 40, Status: USED
Pos: 40, Size: 60, Status: USED
Pos: 100, Size: 1024476, Status: FREE

VREALLOC 10 V0  OK
Status agora:
Pos: 0, Size: 40, Status: USED
Pos: 40, Size: 10, Status: USED
Pos: 50, Size: 1024526, Status: FREE

VREALLOC 1 V1   OK
Status agora:
Pos: 0, Size: 1, Status: USED
Pos: 1, Size: 39, Status: FREE
Pos: 40, Size: 10, Status: USED
Pos: 50, Size: 1024526, Status: FREE

VREALLOC 10 V1  OK
Status agora:
Pos: 0, Size: 10, Status: USED
Pos: 10, Size: 30, Status: FREE
Pos: 40, Size: 10, Status: USED
Pos: 50, Size: 1024526, Status: FREE

VREALLOC 0 V1   NULL
Status agora:
Pos: 0, Size: 40, Status: FREE
Pos: 40, Size: 10, Status: USED
Pos: 50, Size: 1024526, Status: FREE

VFREE 1
Status agora:
Pos: 0, Size: 40, Status: FREE
Pos: 40, Size: 10, Status: USED
Pos: 50, Size: 1024526, Status: FREE

VALLOC 1024577 V1   NULL
Status agora:
Pos: 0, Size: 40, Status: FREE
Pos: 40, Size: 10, Status: USED
Pos: 50, Size: 1024526, Status: FREE

VFREE 0
Status agora:
Pos: 0, Size: 1024576, Status: FREE

VFREE 1
Status agora:
Pos: 0, Size: 1024576, Status: FREE

```

##### 12.tst.i #####

__Entrada:__

```
VAR 4
PRINT
VALLOC 1024576 V0
PRINT
VALLOC 1 V3
PRINT

```

__Saída:__

```
VAR 4
Status agora:
Pos: 0, Size: 1024576, Status: FREE

VALLOC 1024576 V0   OK
Status agora:
Pos: 0, Size: 1024576, Status: USED

VALLOC 1 V3 NULL
Status agora:
Pos: 0, Size: 1024576, Status: USED

```

#### Testes de minha autoria ####

##### t1.i #####

__Entrada:__

```
VAR 5
PRINT
VALLOC 10 V0
VALLOC 20 V1
VALLOC 30 V2
PRINT
VREALLOC 10 V1
PRINT
VALLOC 9 V3
PRINT
VFREE V3
VFREE V1
PRINT
VALLOC 40 V4
PRINT
VREALLOC 30 V0
PRINT
VFREE V2
VCALLOC 10 3 V3
PRINT
VFREE V3
VFREE V4
VFREE V0
PRINT

```

__Saída:__

```
VAR 5
Status agora:
Pos: 0, Size: 1024576, Status: FREE

VALLOC 10 V0    OK

VALLOC 20 V1    OK

VALLOC 30 V2    OK
Status agora:
Pos: 0, Size: 10, Status: USED
Pos: 10, Size: 20, Status: USED
Pos: 30, Size: 30, Status: USED
Pos: 60, Size: 1024516, Status: FREE

VREALLOC 10 V1  OK
Status agora:
Pos: 0, Size: 10, Status: USED
Pos: 10, Size: 10, Status: USED
Pos: 20, Size: 10, Status: FREE
Pos: 30, Size: 30, Status: USED
Pos: 60, Size: 1024516, Status: FREE

VALLOC 9 V3 OK
Status agora:
Pos: 0, Size: 10, Status: USED
Pos: 10, Size: 10, Status: USED
Pos: 20, Size: 9, Status: USED
Pos: 29, Size: 1, Status: FREE
Pos: 30, Size: 30, Status: USED
Pos: 60, Size: 1024516, Status: FREE

VFREE 3

VFREE 1
Status agora:
Pos: 0, Size: 10, Status: USED
Pos: 10, Size: 20, Status: FREE
Pos: 30, Size: 30, Status: USED
Pos: 60, Size: 1024516, Status: FREE

VALLOC 40 V4    OK
Status agora:
Pos: 0, Size: 10, Status: USED
Pos: 10, Size: 20, Status: FREE
Pos: 30, Size: 30, Status: USED
Pos: 60, Size: 40, Status: USED
Pos: 100, Size: 1024476, Status: FREE

VREALLOC 30 V0  OK
Status agora:
Pos: 0, Size: 30, Status: USED
Pos: 30, Size: 30, Status: USED
Pos: 60, Size: 40, Status: USED
Pos: 100, Size: 1024476, Status: FREE

VFREE 2

VCALLOC 10 3 V3 OK
Status agora:
Pos: 0, Size: 30, Status: USED
Pos: 30, Size: 30, Status: USED
Pos: 60, Size: 40, Status: USED
Pos: 100, Size: 1024476, Status: FREE

VFREE 3

VFREE 4

VFREE 0
Status agora:
Pos: 0, Size: 1024576, Status: FREE

```

##### t2.i #####

__Entrada:__

```
VAR 1
PRINT
VALLOC 1024576 V0
PRINT
VREALLOC 1024577 V0
PRINT
VFREE V0
PRINT

```

__Saída:__

```
VAR 1
Status agora:
Pos: 0, Size: 1024576, Status: FREE

VALLOC 1024576 V0   OK
Status agora:
Pos: 0, Size: 1024576, Status: USED

VREALLOC 1024577 V0 NULL
Status agora:
Pos: 0, Size: 1024576, Status: USED

VFREE 0
Status agora:
Pos: 0, Size: 1024576, Status: USED

```

#### Teste adicional: uso da memória ####

Os testes realizados com o interpretador funcionam bem para avaliar o comportamento das funções e realizar um diagnóstico completo. No entanto, eles falham em, de fato, verificar se a memória alocada pode ser utilizada corretamente.

Por essa razão, foi realizado um teste adicional sem uso do interpretador, com um programa principal diferente, testando o uso da memória em situações convencionais. O teste pode ser utilizado compilando o código fonte abaixo juntamente com as bibliotecas `valloc.h`, `Ldenc.h` e `Ndenc.h`, da mesma forma que o programa principal foi compilado.

##### teste1.c #####

```c
#include "valloc.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int *vetor;
    inicializa_gerencia();

    vetor = valloc(sizeof(int)*5);
    printf("Alocando 5 inteiros (sizeof int = %d)\n", sizeof(int));
    for(int i = 0; i < 5; i++)
        printf("vetor[%d] = %d\n", i, vetor[i]);
    imprime_status_memoria();
    printf("Inicializando os elementos\n");
    vetor[0] = 3;
    vetor[1] = 6;
    vetor[2] = 38;
    vetor[3] = 12;
    vetor[4] = 155;
    for(int i = 0; i < 5; i++)
        printf("vetor[%d] = %d\n", i, vetor[i]);

    int *vetor2 = vcalloc(20, sizeof(int));
    printf("Alocando 20 inteiros\n");

    imprime_status_memoria();

    printf("Alterando o elemento oob \"vetor[5]\" com o valor 144\n");
    vetor[5] = 144;

    for(int i = 0; i < 20; i++)
        printf("vetor2[%d] = %d\n", i, vetor2[i]);

    imprime_status_memoria();

    vetor = vrealloc(vetor, sizeof(int)*20);
    printf("Realocando o primeiro vetor para vinte elementos.\n");

    imprime_status_memoria();

    for(int i = 0; i < 20; i++)
        printf("vetor[%d] = %d\n", i, vetor[i]);

    printf("Realocando o segundo vetor para 120 elementos\n");
    vetor2 = vrealloc(vetor2, sizeof(int)*120);

    imprime_status_memoria();

    for(int i = 0; i < 120; i++)
        printf("vetor2[%d] = %d\n", i, vetor2[i]);

    printf("Realocando o segundo vetor para tres elementos\n");
    vetor2 = vrealloc(vetor2, sizeof(int)*3);

    imprime_status_memoria();

    for(int i = 0; i < 3; i++)
        printf("vetor2[%d] = %d\n", i, vetor2[i]);

    vfree(vetor);
    vfree(vetor2);

    imprime_status_memoria();

    printf("Alocando tres inteiros com calloc\n");
    vetor = vcalloc(3, sizeof(int));

    for(int i = 0; i < 3; i++)
        printf("vetor[%d] = %d\n", i, vetor[i]);

    imprime_status_memoria();

    vfree(vetor);

    finaliza_gerencia();
    return 0;
}
```

__Saída:__

```
Alocando 5 inteiros (sizeof int = 4)
vetor[0] = 0
vetor[1] = 0
vetor[2] = 0
vetor[3] = 0
vetor[4] = 0
Status agora:
Pos: 0, Size: 20, Status: USED
Pos: 20, Size: 1024556, Status: FREE
Inicializando os elementos
vetor[0] = 3
vetor[1] = 6
vetor[2] = 38
vetor[3] = 12
vetor[4] = 155
Alocando 20 inteiros
Status agora:
Pos: 0, Size: 20, Status: USED
Pos: 20, Size: 80, Status: USED
Pos: 100, Size: 1024476, Status: FREE
Alterando o elemento oob "vetor[5]" com o valor 144
vetor2[0] = 144
vetor2[1] = 0
vetor2[2] = 0
vetor2[3] = 0
vetor2[4] = 0
vetor2[5] = 0
vetor2[6] = 0
vetor2[7] = 0
vetor2[8] = 0
vetor2[9] = 0
vetor2[10] = 0
vetor2[11] = 0
vetor2[12] = 0
vetor2[13] = 0
vetor2[14] = 0
vetor2[15] = 0
vetor2[16] = 0
vetor2[17] = 0
vetor2[18] = 0
vetor2[19] = 0
Status agora:
Pos: 0, Size: 20, Status: USED
Pos: 20, Size: 80, Status: USED
Pos: 100, Size: 1024476, Status: FREE
Realocando o primeiro vetor para vinte elementos.
Status agora:
Pos: 0, Size: 20, Status: FREE
Pos: 20, Size: 80, Status: USED
Pos: 100, Size: 80, Status: USED
Pos: 180, Size: 1024396, Status: FREE
vetor[0] = 3
vetor[1] = 6
vetor[2] = 38
vetor[3] = 12
vetor[4] = 155
vetor[5] = 0
vetor[6] = 0
vetor[7] = 0
vetor[8] = 0
vetor[9] = 0
vetor[10] = 0
vetor[11] = 0
vetor[12] = 0
vetor[13] = 0
vetor[14] = 0
vetor[15] = 0
vetor[16] = 0
vetor[17] = 0
vetor[18] = 0
vetor[19] = 0
Realocando o segundo vetor para 120 elementos
Status agora:
Pos: 0, Size: 100, Status: FREE
Pos: 100, Size: 80, Status: USED
Pos: 180, Size: 480, Status: USED
Pos: 660, Size: 1023916, Status: FREE
vetor2[0] = 144
vetor2[1] = 0
vetor2[2] = 0
vetor2[3] = 0
vetor2[4] = 0
vetor2[5] = 0
vetor2[6] = 0
vetor2[7] = 0
vetor2[8] = 0
vetor2[9] = 0
vetor2[10] = 0
vetor2[11] = 0
vetor2[12] = 0
vetor2[13] = 0
vetor2[14] = 0
vetor2[15] = 0
vetor2[16] = 0
vetor2[17] = 0
vetor2[18] = 0
vetor2[19] = 0
vetor2[20] = 0
vetor2[21] = 0
vetor2[22] = 0
vetor2[23] = 0
vetor2[24] = 0
vetor2[25] = 0
vetor2[26] = 0
vetor2[27] = 0
vetor2[28] = 0
vetor2[29] = 0
vetor2[30] = 0
vetor2[31] = 0
vetor2[32] = 0
vetor2[33] = 0
vetor2[34] = 0
vetor2[35] = 0
vetor2[36] = 0
vetor2[37] = 0
vetor2[38] = 0
vetor2[39] = 0
vetor2[40] = 0
vetor2[41] = 0
vetor2[42] = 0
vetor2[43] = 0
vetor2[44] = 0
vetor2[45] = 0
vetor2[46] = 0
vetor2[47] = 0
vetor2[48] = 0
vetor2[49] = 0
vetor2[50] = 0
vetor2[51] = 0
vetor2[52] = 0
vetor2[53] = 0
vetor2[54] = 0
vetor2[55] = 0
vetor2[56] = 0
vetor2[57] = 0
vetor2[58] = 0
vetor2[59] = 0
vetor2[60] = 0
vetor2[61] = 0
vetor2[62] = 0
vetor2[63] = 0
vetor2[64] = 0
vetor2[65] = 0
vetor2[66] = 0
vetor2[67] = 0
vetor2[68] = 0
vetor2[69] = 0
vetor2[70] = 0
vetor2[71] = 0
vetor2[72] = 0
vetor2[73] = 0
vetor2[74] = 0
vetor2[75] = 0
vetor2[76] = 0
vetor2[77] = 0
vetor2[78] = 0
vetor2[79] = 0
vetor2[80] = 0
vetor2[81] = 0
vetor2[82] = 0
vetor2[83] = 0
vetor2[84] = 0
vetor2[85] = 0
vetor2[86] = 0
vetor2[87] = 0
vetor2[88] = 0
vetor2[89] = 0
vetor2[90] = 0
vetor2[91] = 0
vetor2[92] = 0
vetor2[93] = 0
vetor2[94] = 0
vetor2[95] = 0
vetor2[96] = 0
vetor2[97] = 0
vetor2[98] = 0
vetor2[99] = 0
vetor2[100] = 0
vetor2[101] = 0
vetor2[102] = 0
vetor2[103] = 0
vetor2[104] = 0
vetor2[105] = 0
vetor2[106] = 0
vetor2[107] = 0
vetor2[108] = 0
vetor2[109] = 0
vetor2[110] = 0
vetor2[111] = 0
vetor2[112] = 0
vetor2[113] = 0
vetor2[114] = 0
vetor2[115] = 0
vetor2[116] = 0
vetor2[117] = 0
vetor2[118] = 0
vetor2[119] = 0
Realocando o segundo vetor para tres elementos
Status agora:
Pos: 0, Size: 100, Status: FREE
Pos: 100, Size: 80, Status: USED
Pos: 180, Size: 12, Status: USED
Pos: 192, Size: 1024384, Status: FREE
vetor2[0] = 144
vetor2[1] = 0
vetor2[2] = 0
Status agora:
Pos: 0, Size: 1024576, Status: FREE
Alocando tres inteiros com calloc
vetor[0] = 0
vetor[1] = 0
vetor[2] = 0
Status agora:
Pos: 0, Size: 12, Status: USED
Pos: 12, Size: 1024564, Status: FREE

```

Conclusão
---------

Não houve grandes problemas na implementação do trabalho, sendo possível concluí-lo dentro do prazo.

As maiores dificuldades ocorreram devido a problemas no comportamento das funções principais da biblioteca em casos extremos de teste, mas com a elaboração de testes de qualidade foi possível descobrir a localização dos erros e consertá-los.

Anexos
------

### Listagem dos programas ###

- Ldenc.h
- Ldenc.c
- Ndenc.h
- Ndenc.c
- valloc.h
- valloc.c
- main.c
