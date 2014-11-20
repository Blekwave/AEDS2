TP2: Sistema de Recomendação
============================

Victor Pires Diniz - *[victorpiresdiniz@dcc.ufmg.br](mailto:victorpiresdiniz@dcc.ufmg.br)*

Algoritmos e Estruturas de Dados II - 2º Semestre de 2014

Índice
------

- [TP2: Sistema de Recomendação](#tp2-sistema-de-recomendação)
  - [Índice](#índice)
  - [Introdução](#introdução)
  - [Implementação](#implementação)
    - [Funcionamento básico e arquivo principal](#funcionamento-básico-e-arquivo-principal)
    - [Arquivos de entrada e bases de dados](#arquivos-de-entrada-e-bases-de-dados)
      - [input.txt](#inputtxt)
      - [metadata.txt](#metadatatxt)
      - [ratings.txt](#ratingstxt)
    - [Sistema de sugestões](#sistema-de-sugestões)
      - [Sugestões por popularidade](#sugestões-por-popularidade)
      - [Sugestões por similaridade](#sugestões-por-similaridade)
      - [Impressão das sugestões](#impressão-das-sugestões)
    - [Tipos abstratos de dados](#tipos-abstratos-de-dados)
      - [Lista encadeada (Lista.h)](#lista-encadeada-listah)
      - [Número racional (Racional.h)](#número-racional-racionalh)
      - [BitString (BitString.h)](#bitstring-bitstringh)
      - [Filme (Filme.h)](#filme-filmeh)
      - [Usuário (Usuario.h)](#usuário-usuarioh)
      - [Árvore binária de busca (ABBusca_m.h)](#árvore-binária-de-busca-abbusca_mh)
      - [Hash table com tratamento de colisão por árvore binária de busca (HashTable_ABB.h)](#hash-table-com-tratamento-de-colisão-por-árvore-binária-de-busca-hashtable_abbh)
    - [Detalhes técnicos](#detalhes-técnicos)
  - [Análise de complexidade](#análise-de-complexidade)
    - [Nodo.h](#nodoh)
      - [Funções de interface](#funções-de-interface)
      - [Inicializar](#inicializar)
      - [Destruir](#destruir)
      - [Resumo (Nodo.h)](#resumo-nodoh)
    - [Lista.h](#listah)
      - [ObterAnterior](#obteranterior)
      - [Funções de inserção](#funções-de-inserção)
      - [Funções de remoção](#funções-de-remoção)
      - [Funções de interface](#funções-de-interface-1)
      - [TrocarElementos](#trocarelementos)
      - [DeslocarElemento](#deslocarelemento)
      - [TrocarDados](#trocardados)
      - [ObterElementoPorIndice](#obterelementoporindice)
      - [Inicializar](#inicializar-1)
      - [Destruir](#destruir-1)
      - [Resumo (Lista.h)](#resumo-listah)
    - [ABNodo.h](#abnodoh)
      - [Funções de interface](#funções-de-interface-2)
      - [Inicializar](#inicializar-2)
      - [Destruir](#destruir-2)
      - [Resumo (ABNodo.h)](#resumo-abnodoh)
    - [ABBusca_m.h](#abbusca_mh)
      - [Inicializar](#inicializar-3)
      - [DestruirGalho](#destruirgalho)
      - [Destruir](#destruir-3)
      - [AdicionarElemento](#adicionarelemento)
      - [Funções de caminhamento](#funções-de-caminhamento)
      - [EncontrarElemento](#encontrarelemento)
      - [EncontrarMaximo e EncontrarMinimo](#encontrarmaximo-e-encontrarminimo)
      - [EncontrarAntecessor e EncontrarSucessor](#encontrarantecessor-e-encontrarsucessor)
      - [TransplantarElemento](#transplantarelemento)
      - [RemoverElemento](#removerelemento)
      - [Funções de interface](#funções-de-interface-3)
      - [Resumo (ABBusca_m.h)](#resumo-abbusca_mh)
    - [HashTable_ABB.h](#hashtable_abbh)
      - [Inicializar](#inicializar-4)
      - [Destruir](#destruir-4)
      - [Buscar](#buscar)
      - [AdicionarElemento](#adicionarelemento-1)
      - [RemoverElemento](#removerelemento-1)
      - [Funções de interface](#funções-de-interface-4)
      - [Resumo (HashTable_ABB.h)](#resumo-hashtable_abbh)
    - [BitString.h](#bitstringh)
      - [Inicializar e Destruir](#inicializar-e-destruir)
      - [Funções de interface](#funções-de-interface-5)
      - [Operadores lógicos](#operadores-lógicos)
      - [Copiar](#copiar)
      - [Resumo (BitString.h)](#resumo-bitstringh)
    - [Racional.h](#racionalh)
      - [static MDC](#static-mdc)
      - [Inicializar e Definir](#inicializar-e-definir)
      - [Comparar](#comparar)
      - [Resumo (Racional.h)](#resumo-racionalh)
    - [Filme.h](#filmeh)
    - [Usuario.h](#usuarioh)
    - [Arquivo.h](#arquivoh)
      - [LerListaDeUsuarios](#lerlistadeusuarios)
      - [static QuicksortFilmeC](#static-quicksortfilmec)
      - [static OrdenarListaDeFilmes](#static-ordenarlistadefilmes)
      - [LerListaDeFilmes](#lerlistadefilmes)
      - [Resumo (Arquivo.h)](#resumo-arquivoh)
    - [Sugestoes.h](#sugestoesh)
      - [Wrappers e funções auxiliares](#wrappers-e-funções-auxiliares)
      - [Heapsort e funções auxiliares](#heapsort-e-funções-auxiliares)
      - [GerarVetorDeVisualizacoes](#gerarvetordevisualizacoes)
      - [Popularidade](#popularidade)
      - [Jaccard](#jaccard)
      - [Similaridade](#similaridade)
      - [Resumo (Sugestoes.h)](#resumo-sugestoesh)
    - [Sugestoes_Impressao.h](#sugestoes_impressaoh)
      - [static ImprimirFilme](#static-imprimirfilme)
      - [static ImprimirABBuscaPopularidade](#static-imprimirabbuscapopularidade)
      - [ImprimirPopularidade](#imprimirpopularidade)
      - [static ImprimirABBuscaSimilaridade](#static-imprimirabbuscasimilaridade)
      - [ImprimirSimilaridade](#imprimirsimilaridade)
      - [Resumo (Sugestoes_Impressao.h)](#resumo-sugestoes_impressaoh)
  - [Testes](#testes)
    - [Testes das bibliotecas](#testes-das-bibliotecas)
      - [Lista.h](#listah-1)
        - [Teste0.c](#teste0c)
        - [Teste1.c](#teste1c)
        - [Teste2.c](#teste2c)
      - [ABBusca_m.h](#abbusca_mh-1)
        - [Teste0_m.c](#teste0_mc)
        - [Teste1_m.c](#teste1_mc)
      - [ABNodo.h](#abnodoh-1)
        - [TesteABNodo.c](#testeabnodoc)
      - [BitString.h](#bitstringh-1)
        - [Teste1.c](#teste1c-1)
      - [HashTable_ABB.h](#hashtable_abbh-1)
        - [Teste0.c](#teste0c-1)
    - [Testes do trabalho](#testes-do-trabalho)
      - [1.tst.i](#1tsti)
  - [Conclusão](#conclusão)
  - [Anexos](#anexos)
    - [Listagem dos programas](#listagem-dos-programas)

Introdução
----------

No ambiente atual, oferecer uma experiência personalizada aos usuários de um serviço vem se tornando cada vez mais importante. Para isso, é preciso conhecer o usuário de um sistema e usar métodos inteligentes que lidem com esses dados e gerem informações relevantes para refinar o serviço oferecido.

Nesse trabalho, implementou-se um sistema de recomendações de filmes que oferece diferentes opções ao cliente de acordo com os filmes que ele já assistiu e com os dados de visualização dos outros usuários do sistema. São oferecidos dois tipos de recomendação: uma modalidade recomenda de acordo com os filmes mais populares e a outra recomenda filmes assistidos pelos usuários mais similares ao usuário em questão.

Implementação
-------------

_Observação: Essa seção lida com informações sobre a implementação em certo grau de abstração. Para saber mais sobre os detalhes da implementação das funções em si e de cada biblioteca, é recomendável acessar o código fonte, que contém a documentação de cada função do programa e comentários esclarecedores sobre alguns comportamentos._

O programa lê, para poder gerar as recomendações, duas bases de dados distintas, mas relacionadas: a primeira contém metadados sobre os filmes presentes no sistema (título, ano de lançamento, imdbID e um identificador único), enquanto a segunda contém todos os usuários do sistema e os filmes assistidos por eles, listados pelo identificador (*movie_id*). Esses dados são armazenados em listas encadeadas genéricas.

As sugestões são, então, geradas (a geração das sugestões é explicada em mais detalhes abaixo) e armazenadas para impressão em hash tables. Como mencionado na introdução, são geradas sugestões por **popularidade** (baseadas no número de visualizações) e sugestões por **similaridade**. (Também chamadas de sugestões personalizadas, baseadas nos usuários mais similares ao usuário em questão.) As sugestões por popularidade são geradas apenas uma vez no programa principal, enquanto as sugestões por similaridade são geradas diferentemente para cada usuário.

O procedimento de impressão, por sua vez, lê as hash tables de acordo com determinados critérios e imprime os filmes em ordem decrescente, iterando pela lista de chaves distintas presentes na hash table. Esse procedimento é responsável, também, por impedir que se imprimam filmes que o usuário já assistiu.

### Funcionamento básico e arquivo principal###

Para fins de modularização e praticidade, o programa foi separado em várias bibliotecas. Algumas apenas armazenam procedimentos e subrotinas, enquanto outras implementam tipos abstratos de dados utilizados ao longo do programa.

Inicialmente, o programa lê algumas informações de um arquivo de entrada: endereço das bases de dados, número de sugestões a serem fornecidas, tamanho da hash table a ser utilizada para armazenar as sugestões e o identificador de cada usuário que terá sugestões geradas.

Na leitura das bases de dados, são chamadas as funções da biblioteca *Arquivo.h*. Essas funções leem os arquivos especificados e armazenam os filmes e usuários em listas encadeadas. Cada filme tem seu tipo `Filme`, da biblioteca *Filme.h*, enquanto cada usuário também é armazenado em um tipo `Usuario`, da biblioteca *Usuario.h*.

Os usuários tem, também, uma lista de filmes assistidos. Inicialmente, essa lista era armazenada, também, em uma lista. Para simplificar muito a lógica do programa e garantir melhoras substanciais na performance, foi criado um tipo `BitString` para fazê-lo, que corresponde a uma sequência de bits de tamanho fixo e tem métodos auxiliares para realizar os operadores lógicos bit-a-bit. Esse tipo e essa decisão são explicados em mais detalhes posteriormente.

Com as bases de dados armazenadas na memória com sucesso, inicializa-se o processo de geração de sugestões, que utiliza os procedimentos definidos em *Sugestoes.h*. As sugestões por popularidade são geradas primeiro, já que esses resultados preliminares não dependem do usuário para o qual se quer sugerir filmes. Vale lembrar que isso só é o caso porque a responsabilidade de não gerar sugestões que o usuário já assistiu cabe às funções de impressão: as sugestões finais são diferentes, já que cada usuário assistiu a um conjunto diferente de filmes.

Após a geração das sugestões por popularidade, é preciso iterar pela lista de usuários. Para cada usuário dessa lista, são geradas sugestões por similaridade diferentes, armazenadas em suas respectivas hash tables.

Ainda iterando por cada usuário, são chamados os procedimentos de impressão, da biblioteca auxiliar *Sugestoes_Impressao.h*. Esses procedimentos imprimem as sugestões para cada usuário.

### Arquivos de entrada e bases de dados ###

Esse programa, em seus parâmetros de chamada (mais detalhes na seção de detalhes técnicos), recebe um arquivo de entrada. Como descrito no enunciado do trabalho prático, esse arquivo deve estar disposto de determinada maneira e pode ser usado para realizar testes úteis com o programa.

Ele contém o endereço das bases de dados de filmes, usuários e filmes assistidos, o número de sugestões a serem realizadas e o tamanho das hash tables empregadas no armazenamento das sugestões. Além disso, nele são especificados os usuários para os quais se deve gerar sugestões.

O formato desse arquivo de entrada é o seguinte:

#### input.txt ####

```
metadata.txt   ratings.txt   num_sugestões   tamanho_hashtable

user_id1
user_id2
...
user_idn

```

_Observação: o espaço entre os campos da primeira linha deve ser realizado com **tabulações**._

No caso, *metadata.txt* corresponde ao arquivo contendo metadados dos filmes, e *ratings.txt* corresponde ao arquivo que contém o identificador dos usuários e seus filmes assistidos. Esses arquivos também tem um formato a ser seguido:

#### metadata.txt ####

```
movie_id    título    imdb_id    ano
movie_id    título    imdb_id    ano
...
movie_id    título    imdb_id    ano

```

_Observação: o espaço entre os campos de cada linha deve ser realizado com **tabulações**._

#### ratings.txt ####

```
user_id    movie_id    movie_id    ...    movie_id
user_id    movie_id    movie_id    ...    movie_id
...
user_id    movie_id    movie_id    ...    movie_id

```

_Observação: o espaço entre os campos de cada linha deve ser realizado com **espaços**._

### Sistema de sugestões ###

O sistema de recomendação de filmes gera dois tipos diferentes de recomendações, com semelhanças e diferenças entre eles. Essas recomendações são armazenadas temporariamente em uma hash table para que possam ser imprimidos. Essas hash tables tratam colisões através de árvores binárias de busca, o que permite que a impressão dos filmes recomendados seja realizada através de um simples caminhamento em ordem central. Os detalhes de implementação das hash tables são explicados em mais detalhes na seção sobre esse tipo.

A biblioteca responsável pela geração das hash tables e das sugestões contidas nelas é *Sugestoes.h*. Para imprimir essas sugestões, é utilizada uma biblioteca auxiliar *Sugestoes_Impressao.h*. Essa divisão foi realizada para permitir a implementação de uma biblioteca alternativa para impressão, *Sugestoes_Impressao_IDs.h*, que não imprime o nome dos filmes, mas sim seus IDs e imdbIDs, para uso na interface web do programa no desafio.

Para inserir nas hash tables os filmes, suas chaves e, no caso das sugestões por similaridade, seus usuários relacionados, foram criados dois invólucros, estruturas auxiliares que armazenam dados necessários para as sugestões. Eles são `Wrapper_Similaridade` e `Wrapper_Popularidade`, e armazenam a chave da entrada na hash table, um ponteiro para filme e um ponteiro para usuário, no caso do `Wrapper_Similaridade`. O tipo da chave depende do tipo de sugestão.

#### Sugestões por popularidade ####

As sugestões por popularidade são, como o próprio nome diz, baseadas na popularidade de cada filme, ou seja, no número de visualizações. Processar o número de visualizações dos filmes é simples: basta iterar pelos usuários e incrementar um vetor que contém uma entrada correspondente a cada `movie_id`. Essas sugestões são geradas apenas uma vez em toda a chamada do programa.

Com esse vetor em mãos, é criado um `Wrapper_Popularidade` para cada filme, e a cada um deles é atribuído o seu determinado número de visualizações, que funciona como __chave__ para a hash table. A função hash para inserção na hash table é, nesse caso, extremamente simples:

    Nº de visualizações % tamanho da tabela

Uma vez determinada a posição do wrapper na tabela hash, a inserção na árvore binária de busca utiliza os critérios secundários de ordenação, de acordo com as seguintes prioridades:

    Data de lançamento > Identificador do filme

A chave em si não é um critério para essa ordenação, já que filtrar pela chave é responsabilidade das funções de impressão.

A função de sugestões por popularidade retorna, além da hash table, um vetor com as chaves utilizadas, ordenadas em ordem decrescente, para uso na função de impressão. Esse vetor é ordenado através do __Heapsort__.

A decisão quanto ao algoritmo a ser utilizado veio da necessidade de prevenir um pior caso muito acentuado, já que uma adaptação desse programa é utilizada para gerar as sugestões na interface web do desafio. Como os dados representam o número de visualizações de filmes, não existe garantia de que eles não podem assumir uma forma ineficiente para o Quicksort, se aproximando do pior caso. Por mais que o Quicksort seja mais rápido no caso médio, é muito importante manter o tempo de execução do programa sob controle, pois pequenos problemas no desempenho de sites geram [grandes impactos na experiência do usuário][loading-time].

[loading-time]: https://blog.kissmetrics.com/loading-time/ "How Loading Time Affects Your Bottom Line"

#### Sugestões por similaridade ####

Ao contrário das sugestões por popularidade, as sugestões por similaridade são únicas para cada usuário, já que elas dependem da similaridade entre um determinado usuário para o qual as sugestões são geradas (que será chamado de alvo daqui em diante) e o resto dos usuários da base de dados. O cálculo dessa similaridade é gerado através da [Similaridade de Jaccard][jaccard], que tem a seguinte fórmula:

    (Interseção dos assistidos de A e B)/(União dos assistidos de A e B)

Calcular a similaridade em si é muito fácil, devido ao tipo escolhido para armazenar os filmes assistidos por cada usuário (`BitString`). Basta realizar a operação bit-a-bit __and__ para obter a interseção e a operação __or__ para obter a união. Então, é simples questão de contar o número de bits '1' em cada `BitString` dos resultados.

A Similaridade de Jaccard entre os usuários é a chave da hash table. Armazenar esse valor é algo que requer cuidado, porém, já que, apesar da estrutura mais comum para armazenar uma divisão não-inteira ser um tipo `float` ou `double`, tipos de ponto flutuante [não são boas chaves para hash tables][hash-float]. Existem sérios problemas associados a confiar nesses tipos para comparações de igualdade, já que eles não passam de aproximações, e alguns valores, quando computados em situações diferentes, podem gerar valores ligeiramente diferentes e causar problemas.

A forma encontrada para resolver esse problema foi armazenar essa razão na sua forma racional: como uma fração simplificada, guardando numerador e denominador. Esse é o tipo `Racional`, da biblioteca *Racional.h*. 

O resto do processo é parecido com o das sugestões por popularidade. Cada filme (e o usuário que assistiu o filme) tem seu endereço inserido na hash table juntamente com a chave racional através de um `Wrapper_Similaridade`. A função hash continua simples, mas dessa vez depende de dois valores: o numerador e o denominador da chave. Assim, é preciso lidar com os dois de forma que ambos influenciem a posição na qual o registro será inserido. A função, portanto, segue abaixo:

    (Numerador << 2 + Denominador) % Tamanho da tabela

O critério de ordenação das árvores de cada espaço da tabela hash depende, dessa vez, tanto do identificador do usuário que assistiu o filme quanto de metadados do filme em si. Por isso a necessidade de se armazenar ponteiros para ambos dados no invólucro adicionado à tabela hash. Esse critério segue a seguinte ordem de prioridades:

    Identificador do usuário > Ano de lançamento > Identificador do filme

Da mesma forma que as sugestões por popularidade, a função que gera as sugestões também retorna um vetor ordenado decrescentemente com as chaves racionais correspondentes aos coeficientes de jaccard obtidos.

#### Impressão das sugestões ####

Os procedimentos de impressão das sugestões por popularidade e similaridade são bastante parecidos. Ambos começam com uma hash table contendo as sugestões e um vetor de chaves em ordem decrescente. Além disso, é realizada uma cópia da `BitString` de filmes assistidos pelo usuário _alvo_. Isso permite armazenar quais filmes já foram imprimidos e evitar que se imprima o mesmo filme duas vezes. Essa `BitString` começa como uma cópia dos filmes assistidos do alvo porque não se deve imprimir um filme que o alvo já assistiu, como definido anteriormente nessa documentação, assim como na especificação do trabalho.

Com isso, itera-se pela lista de chaves, começando da maior das chaves e mantendo uma referência ao número de sugestões a serem imprimidas, evitando imprimir mais do que o requisitado. Existem circunstâncias em que não se imprimem sugestões o suficiente, como, por exemplo, caso o usuário tenha assistido todos os filmes. Generalizando, isso ocorre caso a união dos filmes assistidos por todos os usuários menos o alvo subtraído dos filmes assistidos pelo alvo tenha cardinalidade menor do que o número pedido de sugestões.

Para cada chave, computa-se a posição na hash table e imprimem-se os registros que correspondem àquela chave, ou seja, tem a mesma chave armazenada no invólucro. Isso é feito para todas as chaves até que uma das condições de parada ocorra:

- Sejam imprimidos filmes o suficiente;
- Não haja filmes restantes a imprimir.

[jaccard]: http://www.wikiwand.com/en/Jaccard_index "Jaccard index (Wikipedia)"
[hash-float]: http://stackoverflow.com/questions/4238122/hash-function-for-floats "Hash function for floats (Stack Overflow)"

### Tipos abstratos de dados ###

#### Lista encadeada (Lista.h) ####

A lista encadeada é essencial para realizar esse trabalho, já que ela permite armazenar as bases de dados. A implementação utilizada é uma adaptação da biblioteca utilizada no TP0, que lida com os dados de forma genérica utilizando ponteiros do tipo `void`, que permitem armazenar qualquer tipo de informação na lista.

A implementação dessa lista é dividida entre a biblioteca principal *Lista.h* e a biblioteca auxiliar *Nodo.h*, que contém os procedimentos e a estrutura do nodo genérico de lista encadeada. Foi preferível utilizar a lista encadeada ao invés da duplamente encadeada porque não foi utilizado nenhum procedimento que se beneficiaria do ponteiro para o nodo anterior nesse trabalho.

#### Número racional (Racional.h) ####

A biblioteca de números racionais está presente no arquivo *Racional.h* e implementa uma estrutura bastante simples, que contém dois inteiros: um numerador e um denominador. Esse tipo foi utilizado para armazenar o coeficiente de Jaccard sem que ele sofresse dos problemas de armazenar uma razão como um numeral de ponto flutuante.

Para evitar problemas com frações equivalentes, as funções de inicialização e definição de número racional simplificam a fração automaticamente. Foi implementada também uma função de comparação que opera de forma similar a strcmp: para dois racionais _a_ e _b_ retorna 0 se a é igual a b, um valor menor que zero se a é menor que b e um valor maior que zero se a é maior que b. Essa função é imprescindível para inserir e buscar nas árvores binárias da hash table.

#### BitString (BitString.h) ####

Uma [bit string][bit-string] (também conhecida por outros nomes, como bit array, bitset ou, simplesmente, vetor de bits) é uma forma de armazenar, compactamente, uma sequência de bits. Nesse programa, essa estrutura é utilizada para armazenar o conteúdo de um conjunto, sendo cada bit da `BitString` o indicador da presença ou ausência do elemento no conjunto.

Com a `BitString`, realizar operações em conjuntos pode ser feito com operações bit-a-bit, como _and_ para interseção ou _or_ pra união. Assim, armazenar os filmes assistidos pelo usuário nessa estrutura se mostrou uma forma muito eficiente e compacta de processar o coeficiente de Jaccard e também revelou bom desempenho em outras partes do programa, especialmente em comparação com as opções óbvias, como uma lista encadeada.

A implementação da estrutura em si é feita através de um vetor de `char`, acessando os bits da bit string com bit shifts e operadores lógicos comuns.

[bit-string]: http://www.wikiwand.com/en/Bit_array "Bit array (Wikipedia)"

#### Filme (Filme.h) ####

Esse tipo é uma estrutura simples que permite armazenar os metadados de cada filme. Contém campos para título, ano de lançamento, identificador único e imdbID, assim como funções de interface para cada um desses campos.

#### Usuário (Usuario.h) ####

Assim como o tipo `Filme`, esse também é um tipo simples para armazenar os dados de cada usuário presente na base de dados. Armazena, além do identificador de cada usuário, uma `BitString` que contém o conjunto dos filmes assistidos pelo usuário em questão.

#### Árvore binária de busca (ABBusca_m.h) ####

Uma árvore binária de busca é uma árvore binária (em que cada nodo tem dois filhos) em que todos os nodos cumprem a propriedade que o filho esquerdo é menor que o pai e que o filho direito é maior que o pai. O tipo `ABBusca` da biblioteca *ABBusca_m.h* implementa esse tipo abstrato de dados de forma genérica, armazenando os dados de cada nodo em ponteiros do tipo `void`. A biblioteca auxiliar *ABNodo.h* contém a implementação do nodo de árvore binária.

Para permitir que a estrutura opere de forma completamente genérica e sem distinção do tipo que ela armazena, é preciso definir, também, para cada instância da árvore, funções de comparação distintas, já que várias operações primárias desse tipo dependem da comparação, e a comparação, por sua vez, depende do tipo e dos critérios escolhidos.

Assim, as funções de inserção, busca e outras operações que precisam comparar os dados de elementos recebem um ponteiro de função de comparação e/ou igualdade. Essas funções recebem como parâmetro, por definição, os endereços dos dados de cada nodo (através de ponteiros `void`) e retornam um `bool` (da biblioteca padrão `stdbool.h`) se o primeiro nodo é considerado maior que o segundo (ou igual, para a função de igualdade).

Em retrospecto, seria possível, também, consolidar ambas funções em uma só, como foi feito na biblioteca de números racionais, mas isso também tem pontos negativos no desempenho.

*Observação: a biblioteca se chama ABBusca_m.h por ser uma versão modificada da biblioteca de árvore binária de busca original ABBusca.h implementada por mim. A principal diferença é que a biblioteca original armazenava os ponteiros para as funções de comparação e igualdade no próprio struct da árvore. Para implementar a hash table, isso era menos eficaz do que armazenar esses endereços das funções na estrutura da hash table e recebê-los como parâmetros das funções que precisavam de tais endereços. Armazenar na árvore os endereços implicava em ter muitos ponteiros redundantes para as mesmas duas funções.*

#### Hash table com tratamento de colisão por árvore binária de busca (HashTable_ABB.h) ####

A biblioteca *HashTable_ABB.h* implementa uma [hash table][hash-table] genérica, assim como as outras estruturas de dados utilizadas nesse trabalho. Para tratar as colisões eventuais, são utilizadas árvores binárias de busca implementadas na biblioteca *ABBusca_m.h*, analisada anteriormente.

Essa hash table tem, para cada uma das suas posições, uma árvore binária de busca na qual são armazenados os elementos de cada posição. Além disso, são guardadas em ponteiros de função as funções de comparação e igualdade das árvores binárias de busca assim como a função hash da hash table. Permitir o armazenamento de funções personalizadas e utilizar uma árvore binária de busca que armazena dados genericamente permite, também, que essa hash table opere de forma genérica.

As operações da tabela hash em si são simples, e, nesse programa, são utilizadas diretamente poucas dessas operações. O que distingue essa tabela hash de uma tabela hash convencional é a sua maneira de tratar colisões e as formas criativas de aproveitar essa característica, como é feito pelos procedimentos de geração e impressão de sugestões desse trabalho.

Mais detalhes sobre o funcionamento dessa estrutura e sobre procedimentos auxiliares estão disponíveis no código fonte. (Arquivos *HashTable_ABB.h* e *HashTable_ABB.c*.)

[hash-table]: http://www.wikiwand.com/en/Hash_table "Hash table (Wikipedia)"

### Detalhes técnicos ###


O programa foi compilado e testado no GCC 4.8.1 nos ambientes Windows (Windows 8.1/MinGW) e Linux (Cygwin/GCC). Ele pode ser compilado em qualquer um desses ambientes com o seguinte comando:

    gcc Main.c HashTable_ABB.c ABBusca_m.c ABNodo.c Arquivo.c BitString.c Filme.c Usuario.c Nodo.c Lista.c Racional.c Sugestoes.c Sugestoes_Impressao.c -o TP2 -Wall

A execução do programa, então, pode ser efetuada chamando o mesmo pela linha de comando e passando como parâmetro o endereço do arquivo de entrada e o endereço do arquivo de saída:

    ./TP2 input.txt output.txt

Análise de complexidade
-----------------------

_Ordem de complexidade no __pior caso__ em função das operações e acessos a elementos das estruturas de dados._

_Todas as funções são listadas **sem o prefixo correspondente** ao nome da biblioteca. Ex.: Nodo\_ObterProx está listada apenas como ObterProx na seção da biblioteca Nodo.h._

### Nodo.h ###

#### Funções de interface ####

- ObterProx
- ObterDados
- DefinirProx
- DefinirDados

Essas funções apenas retornam ou atribuem a valores da estrutura de dados, servindo apenas como uma camada de abstração para o tipo abstrato de dados. A ordem de complexidade dessas funções é __O(1)__.

#### Inicializar ####

Essa função apenas aloca a memória necessária para o nodo e inicializa seus valores. Sua ordem de complexidade é __O(1)__, por não conter nenhum laço de repetição ou chamada recursiva.

#### Destruir ####

A função _Destruir_, à primeira vista, aparenta ser uma função que roda em tempo constante, por não conter estruturas que permitam a repetição. No entanto, ela pode realizar uma chamada a outra função passada através de um ponteiro por um de seus argumentos. Por esse motivo, a complexidade dessa função é __O(x)__, sendo _x_ a ordem de complexidade da função chamada. Caso não seja chamada nenhuma função, _Destruir_ opera em tempo constante.

#### Resumo (Nodo.h) ####

| Função           | Ordem |
|------------------|-------|
| ObterProx        | O(1)  |
| DefinirProx      | O(1)  |
| ObterDados       | O(1)  |
| DefinirDados     | O(1)  |
| Inicializar      | O(1)  |
| Destruir*        | O(x)  |

*As funções marcadas recebem como parâmetro um ponteiro de função. __x__, no caso, é a ordem de complexidade da função chamada.

### Lista.h ###

_Ordem de complexidade no pior caso em relação a acessos e operações na lista._

__n__: número de elementos da lista.

#### ObterAnterior ####

Essa função itera pelos elementos da lista. No pior caso, ela tem que atravessar toda a lista (o elemento não pertence à lista), apresentando ordem de complexidade __O(n)__.

#### Funções de inserção ####

- AdicionarElemento
- AdicionarAoInicio
- AdicionarAoFinal

As funções responsáveis por adicionar elementos à lista executam uma série de operações, mas sem nenhum loop ou estrutura que permita a repetição. Por isso, essas funções independem do tamanho da lista e apresentam ordem de complexidade __O(1)__.

#### Funções de remoção ####

Devido ao caráter genérico da lista, há a possibilidade de chamar uma função desconhecida pela biblioteca para liberar o elemento removido, caso isso seja necessário, como se, por exemplo, o nodo contivesse outra lista. Dessa forma, todas as funções de remoção tem a função de complexidade multiplicada por x, sendo _x_ a ordem de complexidade da função chamada (ou 1, caso não haja tal chamada, sendo passado _NULL_ como parâmetro).

- RemoverElementoApos
- RemoverPrimeiroElemento

Essas funções não apresentam laços de repetição ou chamam outras funções de maior ordem de complexidade, com exceção da função auxiliar. Assim, elas possuem ordem de complexidade __O(x)__.

- RemoverElemento
- RemoverUltimoElemento

Essas funções chamam a função _ObterAnterior_, de ordem de complexidade _O(n)_. Assim, considerando que a função auxiliar também é chamada na mesma série de procedimentos, é necessário somar as complexidades. Dessa maneira, a ordem de complexidade dessas funções é __O(n+x)__.

#### Funções de interface ####

- ObterPrimeiro
- ObterUltimo
- ObterCabeca
- ObterTamanho

As funções listadas tem o único propósito de adicionar uma camada de abstração ao programa, servindo como interface para dados já prontamente disponíveis na estrutura de dados. Por essa razão, a ordem de complexidade dessas funções é __O(1)__.

#### TrocarElementos ####

Essa função busca na lista pelo elemento anterior de cada um dos nodos a serem trocados de posição. Por isso, similarmente a _ObterAnterior_, essa função é, no pior caso, __O(n)__.

#### DeslocarElemento ####

Essa função, além de realizar algumas operações simples, faz uma chamada a _ObterAnterior_. Por isso, ela tem ordem de complexidade __O(n)__.

#### TrocarDados ####

Essa função não apresenta nenhum loop ou chamada recursiva, sendo independente do tamanho da lista. A ordem de complexidade dela é, por isso, __O(1)__.

#### ObterElementoPorIndice ####

Essa função realiza uma operação de busca, passando por vários elementos da lista até alcançar o índice indicado. No pior caso, é necessário passar por todos os elementos da lista. Assim, trata-se de uma função com complexidade de ordem __O(n)__.

#### Inicializar ####

A função realiza a alocação, inicialização da nova lista e adição do nodo cabeça (_Nodo\_Inicializar_), que são operações que não envolvem nenhum laço de repetição. É desconsiderado o comportamento da função _malloc_, cuja ordem de complexidade não é necessariamente constante, mas não é relativa ao critério utilizado nessa análise. Dessa forma, em relação ao tamanho da lista, a função tem ordem de complexidade __O(1)__.

#### Destruir ####

A função chama a função _Nodo\_Destruir_ para cada nodo da lista. _Nodo\_Destruir_ também é utilizada para liberar o nodo cabeça, mas ela é chamada com o parâmetro da função auxiliar como _NULL_, o que faz com que, nesse caso, ela assuma ordem de complexidade _O(1)_. Considerando que _Nodo\_Destruir_ tem ordem de complexidade _O(x)_ no resto das situações:

O(_Destruir_) = O(_Nodo\_Destruir_)*n + 1

O(_Destruir_) = O(x)*n

O(_Destruir_) = O(nx)

Assim, a complexidade da função é __O(nx)__.

#### Resumo (Lista.h) ####

| Função                   | Ordem  |
|--------------------------|--------|
| InicializarLdenc         | O(1)   |
| AdicionarElemento        | O(1)   |
| AdicionarAoInicio        | O(1)   |
| AdicionarAoFinal         | O(1)   |
| RemoverElemento*         | O(n+x) |
| RemoverElementoApos*     | O(x)   |
| RemoverPrimeiroElemento* | O(x)   |
| RemoverUltimoElemento*   | O(n+x) |
| DeslocarElemento         | O(n)   |
| TrocarElementos          | O(n)   |
| TrocarDados              | O(1)   |
| ObterPrimeiro            | O(1)   |
| ObterUltimo              | O(1)   |
| ObterCabeca              | O(1)   |
| ObterAnterior            | O(n)   |
| ObterTamanho             | O(1)   |
| ObterElementoPorIndice   | O(n)   |
| AtravessarLdenc* **      | O(nx)  |
| InsertionSort* **        | O(n²x) |
| DestruirLdenc            | O(nx)  |

*As funções marcadas recebem como parâmetro um ponteiro de função. __x__, no caso, é a ordem de complexidade da função chamada.

**As funções marcadas não são usadas em nenhum momento no trabalho. Elas pertencem à biblioteca por serem úteis em outras circunstâncias. No entanto, elas não foram analisadas em detalhe nessa documentação.

### ABNodo.h ###

#### Funções de interface ####

- ObterPai
- ObterEsq
- ObterDir
- ObterDados
- DefinirPai
- DefinirEsq
- DefinirDir
- DefinirDados

Essas funções são apenas formas de obter ou definir dados prontamente disponíveis na estrutura de dados e têm, portanto, ordem de complexidade __O(1)__.

#### Inicializar ####

Essa função apenas realiza uma série de procedimentos, sem laços de repetição ou chamadas a outras funções. Por isso, ela é __O(1)__.

#### Destruir ####

A função _Destruir_ realiza uma série de procedimentos e chama uma função auxiliar de ordem de complexidade desconhecida (_x_). Assim, ela tem ordem de complexidade __O(x)__.

#### Resumo (ABNodo.h) ####

| Função           | Ordem |
|------------------|-------|
| ObterPai         | O(1)  |
| ObterEsq         | O(1)  |
| ObterDir         | O(1)  |
| ObterDados       | O(1)  |
| DefinirPai       | O(1)  |
| DefinirEsq       | O(1)  |
| DefinirDir       | O(1)  |
| DefinirDados     | O(1)  |
| Inicializar      | O(1)  |
| Destruir*        | O(x)  |

*As funções marcadas recebem como parâmetro um ponteiro de função. __x__, no caso, é a ordem de complexidade da função chamada.

### ABBusca_m.h ###

_A análise de complexidade dessa biblioteca será realizada em função do número de elementos presentes na árvore, **n**. Além disso, há ponteiros para as funções de Comparação e Igualdade, que têm complexidade desconhecida para a biblioteca. Eles terão a ordem de complexidade representada por **c** e **i**, respectivamente._

_Obs.: O prefixo das funções dessa biblioteca não é ABBusca\_m, mas sim apenas **ABBusca**._

#### Inicializar ####

A função de inicialização apenas aloca o "esqueleto" da árvore e inicializa seus componentes. Por isso, sua ordem de complexidade é __O(1)__.

#### DestruirGalho ####

Essa função executa a função _ABNodo\_Destruir_ em todos os nodos da sub-árvore especificada. Ou seja, em cada um dos _n_ nodos, é executado um procedimento _O(x)_. Por isso, essa função tem ordem de complexidade __O(nx)__.

#### Destruir ####

A função _Destruir_ apenas libera a memória da árvore e chama o procedimento _DestruirGalho_ em sua raiz. Liberar a memória da árvore não tem impacto na ordem de complexidade e, por isso, a função também é __O(nx)__.

#### AdicionarElemento ####

O procedimento de inserção em uma árvore binária de busca envolve encontrar a lacuna na qual se deve inserir o novo elemento e inserí-lo. A inserção do novo nodo em si apenas inializa um novo nodo e atribui os endereços apropriados aos seus campos. No entanto, o procedimento de busca em uma árvore binária de busca é _O(n)_ no pior caso, já que o pior caso significa que a árvore assume estrutura similar à de uma lista encadeada. O caso médio para elementos aleatoriamente escolhidos, no entanto, para busca em árvore binária de busca, é _O(log n)_.

Para cada uma das comparações realizadas, contudo, é necessário chamar a função de comparação, que tem ordem de complexidade _O(c)_. Dessa forma, essa função tem ordem de complexidade __O(nc)__ no pior caso, mas __O(c log n)__ no caso médio.

#### Funções de caminhamento ####

- OrdemCentral
- PreOrdem
- PosOrdem

Essas funções envolvem passar por todos os elementos da árvore e aplicar uma determinada função de ordem de complexidade desconhecida _O(x)_. Assim, caminhamentos em árvore de busca binária têm ordem de complexidade __O(nx)__.

#### EncontrarElemento ####

Como determinado na análise de _AdicionarElemento_, busca em uma árvore binária de busca é _O(n)_ no pior caso, mas _O(log n)_ no caso médio. No entanto, essa função recebe duas funções desconhecidas como parâmetro: as funções de igualdade e comparação. Essas funções são executadas em cada iteração do procedimento de busca, e têm ordem de complexidade desconhecida _O(i)_ e _O(c)_. Dessa maneira, a ordem de complexidade desta função é __O(n*c*i)__ em pior caso e __O(c*i*log(n))__ em caso médio.

#### EncontrarMaximo e EncontrarMinimo ####

Essas funções realizam um procedimento mais simples, mas similar na sua complexidade ao procedimento de busca. No pior caso, em que a estrutura se assemelha a uma lista, esses procedimentos têm ordem de complexidade __O(n)__. No caso médio, como mencionado anteriormente, __O(log n)__.

#### EncontrarAntecessor e EncontrarSucessor ####

O pior caso dessas funções é um pouco mais complicado de se visualizar. Ele ocorre em duas situações distintas. Como exemplo, será utilizado o procedimento de encontrar sucessor, mas o mesmo é verdade para encontrar o antecessor, já que esses procedimentos são totalmente simétricos.

A primeira situação ocorre quanto o nodo à direita do nodo inicial existe, o nodo inicial é a raiz e todos os outros nodos estão ordenados como uma lista diagonal para o sudoeste na sub-árvore à direita da raiz, como na imagem abaixo:

![](http://a.pomf.se/sruosx.png)

Nessa situação, é preciso passar por todos os nodos da árvore. A outra possível situação acontece quando a árvore está ordenada como uma lista diagonal para o sudeste e o elemento inicial é a folha. Nesse caso, também é preciso atravessar a árvore, mas dessa vez isso é feito da folha até a raiz.

![](http://a.pomf.se/ykfojt.png)

Como se pode ver, também é preciso passar por todos os nodos da árvore. Assim, o pior caso desses procedimentos é __O(n)__. O caso médio também é __O(log n)__, como nos outros procedimentos de busca.

#### TransplantarElemento ####

Esse procedimento realiza apenas algumas operações em ponteiros, sem loops ou outras funções sendo chamadas. Assim, ele é __O(1)__.

#### RemoverElemento ####

O procedimento de remoção em uma árvore binária de busca envolve, na pior situação, buscar pelo elemento mínimo de uma sub-árvore. Como foi determinado anteriormente, em pior caso esse procedimento tem ordem de complexidade _O(n)_. Além disso, ao final é chamado _ABNodo\_Destruir_, que tem ordem de complexidade _O(x)_. Por essa razão, _RemoverElemento_ tem ordem de complexidade __O(n+x)__. Em caso médio, a ordem de complexidade muda para __O(log(n)+x)__

#### Funções de interface ####

- ObterRaiz
- DefinirRaiz

Essas funções apenas servem para definir e obter uma propriedade armazenada na estrutura da árvore e são, por isso, __O(1)__.

#### Resumo (ABBusca_m.h) ####

| Função               | Pior caso | Caso médio   |
|----------------------|-----------|--------------|
| Inicializar          | O(1)      | O(1)         |
| DestruirGalho*       | O(nx)     | O(nx)        |
| Destruir*            | O(nx)     | O(nx)        |
| AdicionarElemento    | O(cn)     | O(c log n)   |
| OrdemCentral*        | O(nx)     | O(nx)        |
| PreOrdem*            | O(nx)     | O(nx)        |
| PosOrdem*            | O(nx)     | O(nx)        |
| EncontrarElemento*   | O(n*c*i)  | O(ci*log(n)) |
| EncontrarMaximo      | O(n)      | O(log n)     |
| EncontrarMinimo      | O(n)      | O(log n)     |
| EncontrarSucessor    | O(n)      | O(log n)     |
| EncontrarAntecessor  | O(n)      | O(log n)     |
| TransplantarElemento | O(1)      | O(1)         |
| RemoverElemento*     | O(n+x)    | O(log(n)+x)  |
| ObterRaiz            | O(1)      | O(1)         |
| DefinirRaiz          | O(1)      | O(1)         |

*As funções marcadas recebem como parâmetro ponteiros de função. __x__ (e, possivelmente, __c__ ou __i__), no caso, é a ordem de complexidade da função chamada.

### HashTable_ABB.h ###

_As funções dessa biblioteca têm análise realizada com base no número de elementos presentes na hash table, **n** e no tamanho da hash table, **t**. Além disso, há ponteiros para as funções de Comparação, Igualdade, Hash e DestruirDados, que têm complexidade desconhecida para a biblioteca. Eles terão a ordem de complexidade representada por **c**, **i**, **h** e **d**, respectivamente._

#### Inicializar ####

A função de inicialização realiza alguns procedimentos simples, aloca a memória da hash table e das suas árvores binárias de busca. É preciso inicializar uma árvore para cada espaço da hash table, o que faz com que esse procedimento tome ordem de complexidade __O(t)__.

#### Destruir ####

Assim como o procedimento de inicialização, o procedimento responsável por finalizar a hash table também tem que destruir cada uma das árvores binárias de busca da tabela. O procedimento de destruir a árvore binária de busca recebe um ponteiro de função, cuja ordem de complexidade é desconhecida (__d__). Assim, esta função tem ordem de complexidade __O(td)__.

#### Buscar ####

A busca na hash table envolve computar a posição de uma chave na tabela com a função hash e buscar pelo elemento em questão na árvore binária de busca. A função hash tem ordem de complexidade _O(h)_, enquanto a busca na árvore binária de busca opera em ordem de complexidade __O(nci)__, como explicado em mais detalhes na seção sobre a biblioteca _ABBusca\_m.h_. . Assim, a busca na tabela hash tem ordem de complexidade __O(h+nci)__.

#### AdicionarElemento ####

Adicionar um elemento na tabela hash também significa computar a posição do elemento novo na tabela com a função hash. Além disso, é preciso adicionar o elemento na árvore binária de busca da posição determinada. Por isso, esse procedimento é __O(cn+h)__.

#### RemoverElemento ####

Para remover um elemento de uma hash table, é necessário descobrir sua posição na tabela hash através da função hash, realizar uma operação de busca na árvore binária e remover o elemento da árvore binária de busca se o elemento existe. Por essa razão, esta função tem ordem de complexidade em pior caso __O(h+nci+d)__.

#### Funções de interface ####

- ObterTamanho
- ObterComparacao
- ObterIgualdade
- ObterHash
- ObterABBusca

Essas funções são apenas formas de obter dados prontamente disponíveis na estrutura e têm, portanto, ordem de complexidade __O(1)__.

#### Resumo (HashTable_ABB.h) ####

| Função            | Ordem      |
|-------------------|------------|
| Inicializar       | O(t)       |
| Destruir          | O(td)      |
| Buscar            | O(h+nci)   |
| AdicionarElemento | O(cn+h)    |
| RemoverElemento   | O(h+nci+d) |
| ObterTamanho      | O(1)       |
| ObterComparacao   | O(1)       |
| ObterIgualdade    | O(1)       |
| ObterHash         | O(1)       |
| ObterABBusca      | O(1)       |

_A explicação do que significa cada variável desta análise foi feita logo após o título da análise de complexidade desta biblioteca._

### BitString.h ###

__n__: tamanho da bit string.

#### Inicializar e Destruir ####

As funções de inicialização e finalização desse tipo abstrato de dados apenas realizam uma série de procedimentos, sendo, ambos, __O(1)__.

#### Funções de interface ####

- ObterBit
- DefinirBit
- ObterTamanho

Essas funções apenas realizam um número constante de operações em informações já prontamente disponíveis na estrutura de dados. Por isso, todas são __O(1)__.

#### Operadores lógicos ####

- Not
- And
- Or
- Xor

Essas funções aplicam um operador lógico em bit strings. No entanto, como as bitstrings são divididas, é preciso realizar esse procedimento _n_/_t_ vezes, sendo _t_ o número de bits em cada bloco da bit string. _t_ é apenas um fator constante, o que faz com que esses procedimentos sejam __O(n)__.

#### Copiar ####

Da mesma forma que as funções de operadores lógicos, essa função copia a bitstring bloco a bloco, operando em ordem de complexidade __O(n)__.

#### Resumo (BitString.h) ####

| Função       | Ordem |
|--------------|-------|
| Inicializar  | O(1)  |
| Destruir     | O(1)  |
| ObterBit     | O(1)  |
| DefinirBit   | O(1)  |
| ObterTamanho | O(1)  |
| Not          | O(n)  |
| And          | O(n)  |
| Or           | O(n)  |
| Xor          | O(n)  |
| Copiar       | O(n)  |

### Racional.h ###

__n__: o menor valor entre o numerador e o denominador da razão.

_Funções estáticas não são utilizáveis fora do arquivo em que foram definidos. Por isso, elas não tem um prefixo e estão evidenciadas com static antes do nome da função._

#### static MDC ####

A complexidade do algoritmo de Euclides, utilizado para calcular o MDC, tem número de passos no pior caso proporcional ao número de dígitos do menor de seus números, necessitando sempre de um número de etapas menor do que cinco vezes esse valor[<sup>\[1\]</sup>][euclides]. O número de dígitos desse número corresponde ao seu _log_ base 10. Ou seja, esse procedimento é __O(log n)__, sendo _n_ o menor dos dois números.

[euclides]: http://www.wikiwand.com/en/Euclidean_algorithm#/Algorithmic_efficiency "Euclidean algorithm (Wikipedia)"

#### Inicializar e Definir ####

Essas funções realizam um número fixo de operações e, no pior caso, uma chamada a _MDC_. Por isso, ambas tem ordem de complexidade __O(log n)__.

#### Comparar ####

A função de comparação apenas realiza um número fixo de procedimentos aritméticos, sendo, por essa razão, __O(1)__.

#### Resumo (Racional.h) ####

| Função       | Ordem    |
|--------------|----------|
| Inicializar  | O(log n) |
| Definir      | O(log n) |
| Comparar     | O(1)     |
| static MDC   | O(log n) |

### Filme.h ###

- Inicializar
- Destruir
- DestruirAux
- ObterAno
- ObterTitulo
- ObterIMDBID
- ObterMovieID

Essa biblioteca implementa o tipo abstrato de dados `Filme`, que serve apenas como um registro. Por isso, ele implementa somente funções de interface, inicialização e finalização executáveis em tempo constante, __O(1)__.

### Usuario.h ###

- Inicializar
- Destruir
- DestruirAux
- ObterID
- ObterAssistidos

Similarmente à biblioteca _Filme.h_, essa biblioteca implementa os registros de usuário através do tipo `Usuario`. Novamente, todas as funções são executáveis em tempo constante, e não há nenhuma métrica evidente para medir a ordem de complexidade dessas funções. __O(1)__.

### Arquivo.h ###

#### LerListaDeUsuarios ####

A função itera pela lista de filmes assistidos de cada um dos usuários da base de dados. Por isso, há dois fatores a considerar: o número de filmes (__m__) e o número de usuários da base de dados (__n__).

Para cada usuário, a função define um dos bits da bit string de filmes assistidos para cada um dos seus filmes assistidos. `BitString_DefinirBit` é uma função que opera em tempo constante. Ou seja, a ordem de complexidade desta função é __O(m*n)__.

#### static QuicksortFilmeC ####

Essa função realiza o procedimento de Quicksort, que é, como muito bem documentado em várias obras, [__O(n²)__ em pior caso, mas __O(n log n)__ em caso médio][quicksort].

[quicksort]: http://www.wikiwand.com/en/Quicksort "Quicksort (Wikipedia)"

#### static OrdenarListaDeFilmes ####

Nessa função, os filmes da lista de filmes são passados para um vetor, ordenados usando _QuicksortFilmeC_ e adicionados novamente à lista. Os procedimentos de remover os elementos da lista e adicioná-los novamente à lista são _O(n)_ no pior caso, mas o Quicksort tem ordem de complexidade _O(n²)_ no seu pior caso, e _O(n²)_ + _O(n)_ = __O(n²)__.

#### LerListaDeFilmes ####

O procedimento itera pelas linhas da base de dados de filmes, adiciona os filmes a uma lista encadeada e ordena a lista utilizando `OrdenarListaDeFilmes`. Iterar pelas linhas tem complexidade _O(n)_, mas _OrdenarListaDeFilmes_ é __O(n²)__, que prevalece novamente, como mostrado no procedimento anterior.

#### Resumo (Arquivo.h) ####

| Função                      | Ordem  |
|-----------------------------|--------|
| LerListaDeUsuarios          | O(m*n) |
| static QuicksortFilmeC      | O(n²) |
| static OrdenarListaDeFilmes | O(n²) |
| LerListaDeFilmes            | O(n²) |

### Sugestoes.h ###

_Nessa biblioteca, há situações que lidam com parâmetros diferentes para realizar a análise de complexidade. Nas funções de ordenação, **n** se refere ao número de elementos do vetor. Na geração de sugestões e nas funções auxiliares desses procedimentos, **n** é o número de filmes do sistema e **m** é o número de usuários presentes na base de dados._

#### Wrappers e funções auxiliares ####

- Wrapper_Popularidade_Inicializar
- Wrapper_Similaridade_Inicializar
- PopularidadeComparacao
- PopularidadeIgualdade
- PopularidadeHash
- SimilaridadeComparacao
- SimilaridadeIgualdade
- SimilaridadeHash

Todas as funções acima apenas criam ou manipulam os invólucros dos tipos *Wrapper_Popularidade* e *Wrapper_Similaridade*, realizando procedimentos e comparações um número constante de vezes. Assim, esses procedimentos operam em tempo constante, __O(1)__.

#### Heapsort e funções auxiliares ####

- static int_minheap
- static racional_minheap

Essas funções corrigem, se necessário, o sub-heap indicado para que esse cumpra as propriedades de um min-heap. Essa operação tem ordem de complexidade __O(log n)__ no pior caso. No entanto, o procedimento implementado na função principal do Heapsort de transformar todo o vetor em um min-heap, que itera por aproximadamente metade dos elementos do vetor e aplica esse procedimento, opera em __O(n)__.

- static HeapsortIntD
- static HeapsortRacionalD

As funções principais do Heapsort operam em __O(n log n)__ em pior caso, como visto em sala de aula e documentado em diversas publicações. Mais detalhes sobre os procedimentos relacionados ao Heapsort e suas ordens de complexidade estão disponíveis nesse [material da Universidade Estadual do Texas][heapsort].

[heapsort]: http://cs.txstate.edu/~ch04/webtest/teaching/courses/5329/lectures/heap-comp.pdf "Complexity of Heapsort (Texas State University)"

#### GerarVetorDeVisualizacoes ####

A função itera pela lista de usuários, obtém a bitstring de filmes assistidos e checa cada elemento dessa bitstring. Por isso, sua complexidade depende do número de filmes __n__ e do número de usuários __m__, e sua ordem é __O(n*m)__. As funções chamadas dentro dos loops utilizados todas operam em tempo constante.

#### Popularidade ####

A complexidade da função que gera as sugestões por popularidade depende do número de filmes __n__ e do número de usuários __m__.

Inicialmente, é chamado o procedimento _GerarVetorDeVisualizacoes_, que é _O(n*m)_. Em seguida, itera-se pela lista de filmes e, para cada filme, é inserido um wrapper na hash table. A operação de inserção na hash table é _O(n)_ no pior caso, já que no final do procedimento a hash table tem _n_ registros. Ou seja, esse trecho do código opera em _O(n²)_. No final da função, é chamada a função _HeapsortIntD_ para ordenar o vetor de chaves, que tem tamanho _n_. Ou seja, a complexidade final da função é:

    O(n²) + O(n log n) + O(nm)

Levando em consideração ambos fatores, a ordem final de complexidade da geração de sugestões por popularidade é __O(n² + n*m)__.

_Observação: Na análise da biblioteca da tabela hash, concluiu-se que a inserção na tabela tinha ordem de complexidade O(cn+h). No entanto, as funções de comparação e hash já são conhecidas e operam em tempo constante._

#### Jaccard ####

Essa função chama os operadores *BitString_And* e *BitString_Or*, ambos _O(n)_. Além disso, para contar o número de filmes assistidos na interseção e na união, é preciso iterar pelos bits da bit string, operação que também é realizada em tempo linear. Ou seja, a função é __O(n)__, sendo __n__ o número de filmes da base de dados.

#### Similaridade ####

A função de geração de sugestões por similaridade é um procedimento que chama muitas funções relevantes para essa análise. Ela também depende tanto do número de usuários, __m__, quanto do número de filmes, __n__.

O maior laço de repetição do código dessa função itera por cada usuário da lista de usuários. Dentro desse procedimento, é calculado o _Jaccard_ entre o alvo e cada usuário, procedimento _O(n)_. Além disso, ainda dentro desse laço inicial, há outro loop no qual se itera pela lista de filmes assistidos do usuário. Dentro desse segundo loop, o programa adiciona elementos à hash table de sugestões.

Adicionar elementos à hash table é um procedimento executado em tempo linear, considerando funções hash e de comparação _O(1)_. No entanto, a execução é feita em tempo linear em relação ao __número de elementos da hash table__. No final da execução, a hash table terá adicionado cada filme uma vez para cada usuário com exceção do alvo. Ou seja, o tamanho final da tabela hash é proporcional a __n*m__. Por essa razão, o procedimento de adição de elementos à hash table é, no contexto desse programa, _O(nm)_.

Esse é, claramente, o procedimento mais computacionalmente caro de toda a função, já que ele é executado dentro de dois loops que são executados _m_ e _n_ vezes. Por isso, esta função tem ordem de complexidade em pior caso __O(n² * m²)__.

#### Resumo (Sugestoes.h) ####

| Função                             | Ordem        |
|------------------------------------|--------------|
| Wrapper\_Popularidade\_Inicializar | O(1)         |
| Wrapper\_Similaridade\_Inicializar | O(1)         |
| PopularidadeComparacao             | O(1)         |
| PopularidadeIgualdade              | O(1)         |
| PopularidadeHash                   | O(1)         |
| SimilaridadeComparacao             | O(1)         |
| SimilaridadeIgualdade              | O(1)         |
| SimilaridadeHash                   | O(1)         |
| ObterHash                          | O(1)         |
| ObterABBusca                       | O(1)         |
| static int_minheap                 | O(log n)     |
| static racional_minheap            | O(log n)     |
| static HeapsortIntD                | O(n log n)   |
| static HeapsortRacionalD           | O(n log n)   |
| GerarVetorDeVisualizacoes          | O(n*m)       |
| Popularidade                       | O(n² + n*m) |
| Jaccard                            | O(n)         |
| Similaridade                       | O(n² * m²) |

### Sugestoes_Impressao.h ###

_Para a análise de complexidade das funções dessa biblioteca, **n** é o número de filmes do sistema e **m** é o número de usuários presentes na base de dados._

#### static ImprimirFilme ####

Essa função apenas realiza um procedimento de impressão e é, por isso, __O(1)__.

#### static ImprimirABBuscaPopularidade ####

O procedimento em questão passa pelos nodos de uma árvore binária de busca da hash table e imprime os filmes. Nas sugestões por popularidade, o número de elementos da hash table é o número de filmes, _n_, e, no pior caso, todos os elementos da hash table estão na árvore que se quer imprimir. Como isso corresponde a um caminhamento em ordem central, a ordem de complexidade desse procedimento é __O(n)__.

#### ImprimirPopularidade ####

Apesar de _ImprimirPopularidade_ iterar pelas árvores da hash table e chamar o procedimento _ImprimirABBuscaPopularidade_, analisar a complexidade desse procedimento não é tão simples quanto multiplicar _O(n)_ pelo tamanho da hash table. O pior caso de _ImprimirABBuscaPopularidade_ leva em consideração que todos os elementos estão concentrados na árvore que está sendo imprimirda. _ImprimirPopularidade_ imprime apenas, no máximo, os mesmos _n_ elementos, a diferença sendo que eles podem estar dispersos entre as árvores. Por essa razão, este procedimento também tem ordem de complexidade em pior caso __O(n)__.

#### static ImprimirABBuscaSimilaridade ####

A análise desse procedimento é análoga ao que ocorre em `ImprimirABBuscaPopularidade`. A diferença é que, ao invés de _n_ elementos, o número de elementos da hash table de sugestões por similaridade contém um valor proporcional a _n_*_m_ elementos (precisamente, _n_*(_m_ - 1), já que o alvo em si não tem seus filmes adicionados à tabela). Por isso, o procedimento é __O(n*m)__.

#### ImprimirSimilaridade ####

Da mesma forma que _ImprimirPopularidade_, a ordem de complexidade desse procedimento é idêntica à de _ImprimirABBuscaSimilaridade_: __O(n*m)__.

#### Resumo (Sugestoes_Impressao.h) ####

| Função                             | Ordem  |
|------------------------------------|--------|
| ImprimirFilme                      | O(1)   |
| static ImprimirABBuscaPopularidade | O(n)   |
| ImprimirPopularidade               | O(n)   |
| ImprimirABBuscaSimilaridade        | O(n*m) |
| ImprimirSimilaridade               | O(n*m) |

Testes
------

Os testes desse programa se dividem em dois tipos de testes: testes da funcionalidade das bibliotecas e testes do programa em si, utilizando o arquivo de entrada para realizar os testes. Os testes das bibliotecas auxiliares foram escritos por mim, enquanto os testes do trabalho foram fornecidos juntamente com o enunciado, pela monitoria de Algoritmos e Estruturas de Dados II.

### Testes das bibliotecas ###

Os testes abaixo são programas simples escritos em C que testam a funcionalidade de cada biblioteca.

_Observação: vários testes usam sintaxe no padrão C99, ao contrário das bibliotecas e do trabalho em si._

#### Lista.h ####

##### Teste0.c #####

__Código fonte:__

```c
#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>

void ImprimirInteiro(void *dados){
    printf("Dados de endereco %p: %d\n", dados, *((int *)dados));
}

void ImprimirListaDeInteiros(Lista *lista){
    Lista_Atravessar(lista, ImprimirInteiro);
    printf("\n");
}

int MaiorQue(void *a, void *b){
    return *((int *)a) > *((int *)b);
}

int MenorQue(void *a, void *b){
    return *((int *)a) < *((int *)b);
}

int main(int argc, char const *argv[])
{
    Lista *lista = Lista_Inicializar();

    ImprimirListaDeInteiros(lista);
    
    int *temp = (int *)malloc(sizeof(int));
    *temp = 1;
    Lista_AdicionarAoInicio(lista, temp);
    
    temp = (int *)malloc(sizeof(int));
    *temp = 10;
    Lista_AdicionarAoFinal(lista, temp);

    temp = (int *)malloc(sizeof(int));
    *temp = 3;
    Nodo *nodotemp = Lista_AdicionarElemento(lista, Lista_ObterPrimeiro(lista), temp);

    ImprimirListaDeInteiros(lista);

    Lista_DeslocarElemento(lista, nodotemp, Lista_ObterCabeca(lista));
    Lista_DeslocarElemento(lista, nodotemp, Lista_ObterUltimo(lista));
    printf("Elemento central deslocado para a ultima posicao.\n");

    ImprimirListaDeInteiros(lista);    

    Lista_TrocarElementos(lista, nodotemp, Lista_ObterPrimeiro(lista));
    printf("Primeira e ultima posicoes trocadas.\n");
    ImprimirListaDeInteiros(lista);    

    Lista_RemoverElemento(lista, nodotemp, NULL);
    printf("Elemento central removido.\n");

    Lista_RemoverPrimeiroElemento(lista, NULL);
    printf("Primeiro elemento removido.\n");

    ImprimirListaDeInteiros(lista);

    Lista_RemoverUltimoElemento(lista, NULL);
    printf("Ultimo elemento removido.\n");

    ImprimirListaDeInteiros(lista);

    Lista_Destruir(lista, NULL);
    return 0;
}
```

__Saída esperada:__

```
Dados de endereco 006fcbd0: 1
Dados de endereco 006fcc10: 3
Dados de endereco 006fcbf0: 10

Elemento central deslocado para a ultima posicao.
Dados de endereco 006fcbd0: 1
Dados de endereco 006fcbf0: 10
Dados de endereco 006fcc10: 3

Primeira e ultima posicoes trocadas.
Dados de endereco 006fcc10: 3
Dados de endereco 006fcbf0: 10
Dados de endereco 006fcbd0: 1

Elemento central removido.
Primeiro elemento removido.
Dados de endereco 006fcbd0: 1

Ultimo elemento removido.
```

##### Teste1.c #####

__Código fonte:__

```c
#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

void ImprimirInteiro(void *dados){
    printf("Dados de endereco %p: %d\n", dados, *((int *)dados));
}

void ImprimirListaDeInteiros(Lista *lista){
    Lista_Atravessar(lista, ImprimirInteiro);
    printf("\n");
}

int MaiorQue(void *a, void *b){
    return *((int *)a) > *((int *)b);
}

int MenorQue(void *a, void *b){
    return *((int *)a) < *((int *)b);
}

int main(int argc, char const *argv[])
{
    Lista *teste = Lista_Inicializar();
    if (teste == NULL){
        printf("Falha na inicializacao.\n");
        exit(1);
    }
    printf("Lista inicializada com sucesso.\n");
    
    if (Lista_ObterTamanho(teste) == 0)
        printf("Tamanho de acordo com o esperado (0)\n");
    else
        printf("Tamanho inesperado: %d\n", Lista_ObterTamanho(teste));

    int inteiros[10] = {0,1,2,3,13,14,6,14,8,9}, i, *temp;
    for (i = 0; i < 10; i++){
        temp = (int *)malloc(sizeof(int));
        *temp = inteiros[i];
        Lista_AdicionarAoFinal(teste, (void *)temp);
        printf("Adicionado elemento #%d: %d\n", i, inteiros[i]);
    }

    if (Lista_ObterTamanho(teste) == 10)
        printf("Tamanho de acordo com o esperado (10)\n\n");
    else
        printf("Tamanho inesperado: %d\n", Lista_ObterTamanho(teste));

    Lista_TrocarElementos(teste, Lista_ObterElementoPorIndice(teste, 4), Lista_ObterElementoPorIndice(teste, 7));
    printf("Elementos de indice 4 e 7 trocados de posicao.\n");
    ImprimirListaDeInteiros(teste);

    Lista_DeslocarElemento(teste, Lista_ObterElementoPorIndice(teste,4), Lista_ObterCabeca(teste));
    printf("Elemento de indice 4 deslocado para a primeira posicao.\n");
    ImprimirListaDeInteiros(teste);

    Lista_RemoverUltimoElemento(teste, NULL);
    Lista_RemoverPrimeiroElemento(teste, NULL);
    printf("Removidos primeiro e ultimo elemento da lista.\n");
    ImprimirListaDeInteiros(teste);    

    Lista_InsertionSort(teste, MenorQue);
    printf("Lista ordenada com a < b\n");
    ImprimirListaDeInteiros(teste);

    Lista_InsertionSort(teste, MaiorQue);
    printf("Lista ordenada com a > b\n");
    ImprimirListaDeInteiros(teste);

    Lista_Destruir(teste, NULL);
    printf("Lista destruida com sucesso.\n");

    return 0;
}
```

__Saída esperada:__

```
Lista inicializada com sucesso.
Tamanho de acordo com o esperado (0)
Adicionado elemento #0: 0
Adicionado elemento #1: 1
Adicionado elemento #2: 2
Adicionado elemento #3: 3
Adicionado elemento #4: 13
Adicionado elemento #5: 14
Adicionado elemento #6: 6
Adicionado elemento #7: 14
Adicionado elemento #8: 8
Adicionado elemento #9: 9
Tamanho de acordo com o esperado (10)

Elementos de indice 4 e 7 trocados de posicao.
Dados de endereco 00702370: 0
Dados de endereco 00702390: 1
Dados de endereco 007023b0: 2
Dados de endereco 007023d0: 3
Dados de endereco 007004a0: 14
Dados de endereco 00702410: 14
Dados de endereco 00702430: 6
Dados de endereco 007023f0: 13
Dados de endereco 007024b8: 8
Dados de endereco 007025c8: 9

Elemento de indice 4 deslocado para a primeira posicao.
Dados de endereco 007004a0: 14
Dados de endereco 00702370: 0
Dados de endereco 00702390: 1
Dados de endereco 007023b0: 2
Dados de endereco 007023d0: 3
Dados de endereco 00702410: 14
Dados de endereco 00702430: 6
Dados de endereco 007023f0: 13
Dados de endereco 007024b8: 8
Dados de endereco 007025c8: 9

Removidos primeiro e ultimo elemento da lista.
Dados de endereco 00702370: 0
Dados de endereco 00702390: 1
Dados de endereco 007023b0: 2
Dados de endereco 007023d0: 3
Dados de endereco 00702410: 14
Dados de endereco 00702430: 6
Dados de endereco 007023f0: 13
Dados de endereco 007024b8: 8

Lista ordenada com a < b
Dados de endereco 00702370: 0
Dados de endereco 00702390: 1
Dados de endereco 007023b0: 2
Dados de endereco 007023d0: 3
Dados de endereco 00702430: 6
Dados de endereco 007024b8: 8
Dados de endereco 007023f0: 13
Dados de endereco 00702410: 14

Lista ordenada com a > b
Dados de endereco 00702410: 14
Dados de endereco 007023f0: 13
Dados de endereco 007024b8: 8
Dados de endereco 00702430: 6
Dados de endereco 007023d0: 3
Dados de endereco 007023b0: 2
Dados de endereco 00702390: 1
Dados de endereco 00702370: 0

Lista destruida com sucesso.
```

##### Teste2.c #####

__Código fonte:__

```c
#include "Lista.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void ImprimirString(void *dados){
    printf("%p: %s\n", dados, (char *)dados);
}

void ImprimirListaDeStrings(Lista *lista){
    Lista_Atravessar(lista, ImprimirString);
}

int StringMaiorQue(void *a, void *b){
    return strcmp(a,b) <= 0;
}

int main(int argc, char const *argv[])
{
    Lista *teste = Lista_Inicializar();
    printf("Lista inicializada.\n");
    char base[10][30] = {
        "Asdasdlkajsd",
        "Ojasodj",
        "sodij",
        "Asdljksdlaksdj",
        "uhmguixfm",
        "bbbb",
        "",
        "aosidajsod",
        "kkkkklksjdncm",
        "00001"
    }, *buffer;
    int i;
    for (i = 0; i < 10; i++){
        buffer = (char *)malloc(sizeof(char)*30);
        strcpy(buffer, base[i]);
        printf("Adicionando #%d: %s\n", i, buffer);
        Lista_AdicionarElemento(teste, Lista_ObterUltimo(teste), (void *)buffer);
    }
    if (Lista_ObterTamanho(teste) == 10)
        printf("Tamanho de acordo com o esperado.\n");
    else 
        printf("Tamanho inesperado.\n");

    ImprimirListaDeStrings(teste);

    Lista_InsertionSort(teste, StringMaiorQue);
    printf("Lista ordenada com sucesso.\n");    

    ImprimirListaDeStrings(teste);

    Lista_Destruir(teste, NULL);
    return 0;
}
```

__Saída esperada:__

```
Lista inicializada.
Adicionando #0: Asdasdlkajsd
Adicionando #1: Ojasodj
Adicionando #2: sodij
Adicionando #3: Asdljksdlaksdj
Adicionando #4: uhmguixfm
Adicionando #5: bbbb
Adicionando #6:
Adicionando #7: aosidajsod
Adicionando #8: kkkkklksjdncm
Adicionando #9: 00001
Tamanho de acordo com o esperado.
002dcb28: Asdasdlkajsd
002dcb60: Ojasodj
002dcb98: sodij
002dcbd0: Asdljksdlaksdj
002dcc08: uhmguixfm
002dcc40: bbbb
002dcc78:
002dccb0: aosidajsod
002dcce8: kkkkklksjdncm
002dcd20: 00001
Lista ordenada com sucesso.
002dcc78:
002dcd20: 00001
002dcb28: Asdasdlkajsd
002dcbd0: Asdljksdlaksdj
002dcb60: Ojasodj
002dccb0: aosidajsod
002dcc40: bbbb
002dcce8: kkkkklksjdncm
002dcb98: sodij
002dcc08: uhmguixfm
```

#### ABBusca_m.h ####

##### Teste0_m.c #####

__Código fonte:__

```c
#include "ABBusca_m.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool comp(void *a, void *b){
    return *((int *)a) > *((int *)b);
}

bool igual(void *a, void *b){
    return *((int *)a) == *((int *)b);
}

void ImprimirInteiro(void *dados){
    printf("%d\n", *((int *)dados));
}

ABNodo *AdicionarInteiro(ABBusca *arvore, int val, bool(*Comparacao)(void *a, void *b)){
    int *temp = (int *)malloc(sizeof(int));
    *temp = val;
    return ABBusca_AdicionarElemento(arvore, temp, Comparacao);
}

ABNodo *EncontrarInteiro(ABBusca *arvore, int val, bool(*Comparacao)(void *a, void *b), bool(*Igualdade)(void *a, void *b)){
    int *temp = (int *)malloc(sizeof(int));
    *temp = val;
    ABNodo *res = ABBusca_EncontrarElemento(arvore, temp, Comparacao, Igualdade);
    free(temp);
    return res;
}

int main(int argc, char const *argv[])
{
    ABBusca *a = ABBusca_Inicializar();
    if (a != NULL && a->raiz == NULL)
        printf("Arvore inicializada com sucesso.\n");
    else {
        printf("Problema na inicializacao da arvore.\n");
        exit(1);
    }

    AdicionarInteiro(a, 12, comp);
    AdicionarInteiro(a, 0, comp);
    AdicionarInteiro(a, 35, comp);
    AdicionarInteiro(a, 123, comp);
    AdicionarInteiro(a, 22, comp);
    AdicionarInteiro(a, -13, comp);
    AdicionarInteiro(a, -223, comp);
    
    printf("Elementos adicionados com sucesso (suponho)\n");

    printf("Imprimindo elementos em ordem central: \n");
    ABBusca_OrdemCentral(a->raiz, ImprimirInteiro);
    printf("Elementos impressos em ordem central.\n\n");

    printf("Imprimindo elementos em pre-ordem: \n");
    ABBusca_PreOrdem(a->raiz, ImprimirInteiro);
    printf("Elementos impressos em pre-ordem.\n\n");

    printf("Imprimindo elementos em pos-ordem: \n");
    ABBusca_PosOrdem(a->raiz, ImprimirInteiro);
    printf("Elementos impressos em pos-ordem.\n\n");

    printf("Procurando por elemento 300: ");
    ABNodo *busca = EncontrarInteiro(a, 300, comp, igual);
    if (busca != NULL)
        printf("Encontrado em %p\n", busca);
    else
        printf("Elemento nao foi encontrado :(\n");

    printf("Procurando por elemento 123: ");
    busca = EncontrarInteiro(a, 123, comp, igual);
    if (busca != NULL)
        printf("Encontrado em %p\n", busca);
    else
        printf("Elemento não foi encontrado :(\n");

    printf("Removendo elemento 123\n");
    ABBusca_RemoverElemento(a, busca, NULL);

    printf("Imprimindo elementos em ordem central: \n");
    ABBusca_OrdemCentral(a->raiz, ImprimirInteiro);
    printf("Elementos impressos em ordem central.\n\n");

    printf("Destruindo arvore\n");
    ABBusca_Destruir(a, NULL);
    printf("Arvore destruida com sucesso.\n");

    return 0;
}
```

__Saída esperada:__

```
Arvore inicializada com sucesso.
Elementos adicionados com sucesso (suponho)
Imprimindo elementos em ordem central:
-223
-13
0
12
22
35
123
Elementos impressos em ordem central.

Imprimindo elementos em pre-ordem:
12
0
-13
-223
35
22
123
Elementos impressos em pre-ordem.

Imprimindo elementos em pos-ordem:
-223
-13
0
22
123
35
12
Elementos impressos em pos-ordem.

Procurando por elemento 300: Elemento nao foi encontrado :(
Procurando por elemento 123: Encontrado em 007d23d8
Removendo elemento 123
Imprimindo elementos em ordem central:
-223
-13
0
12
22
35
Elementos impressos em ordem central.

Destruindo arvore
Arvore destruida com sucesso.
```

##### Teste1_m.c #####

__Código fonte:__

```c
#include "ABBusca_m.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool comp(void *a, void *b){
    return strcmp((char *)a, (char *)b) > 0;
}

bool igual(void *a, void *b){
    return strcmp((char *)a, (char *)b) == 0;
}

ABNodo *adic_str(ABBusca *arvore, char *str, bool(*comp)(void *a, void *b)){
    char *temp = (char *)malloc((strlen(str)+1)*sizeof(char));
    strcpy(temp, str);
    return ABBusca_AdicionarElemento(arvore, (void *)temp, comp);
}

ABNodo *enc_str(ABBusca *arvore, char *str, bool(*comp)(void *a, void *b), bool(*igual)(void *a, void *b)){
    return ABBusca_EncontrarElemento(arvore, (void *)str, comp, igual);
}

void print_str(void *dados){
    printf("%s\n", (char *)dados);
}

int main(int argc, char const *argv[])
{
    printf("Teste 01: Strings\n");
    ABBusca *a = ABBusca_Inicializar();
    if (a == NULL){
        printf("Falha na inicializacao da arvore.\n");
        exit(1);
    }
    printf("Arvore inicializada com sucesso.\n\n");

    printf("Adicionando varios elementos a lista.\n");
    adic_str(a, "Miguel", comp);
    adic_str(a, "Miguel", comp);
    adic_str(a, "Lucas", comp);
    adic_str(a, "Lana", comp);
    adic_str(a, "Rafael", comp);
    adic_str(a, "Joaquim", comp);
    adic_str(a, "zzz", comp);
    adic_str(a, "Names r us", comp);
    printf("Adicionados varios elementos a lista.\n");

    printf("Imprimindo elementos em ordem central: \n");
    ABBusca_OrdemCentral(a->raiz, print_str);
    printf("Elementos impressos em ordem central.\n\n");

    printf("Procurando pelo nodo \"Marcelo\": ");
    ABNodo *busca = enc_str(a, "Marcelo", comp, igual);
    if (busca == NULL)
        printf("Nao encontrado.\n");
    else
        printf("Encontrado no endereco %p\n", busca);

    printf("Procurando pelo nodo \"Rafael\": ");
    busca = enc_str(a, "Rafael", comp, igual);
    if (busca == NULL)
        printf("Nao encontrado.\n");
    else
        printf("Encontrado no endereco %p\n", busca);

    printf("Removendo o nodo \"Rafael\"\n");
    ABBusca_RemoverElemento(a, busca, NULL);
    printf("Nodo removido com sucesso, I guess.\n\n");

    printf("Imprimindo elementos em ordem central: \n");
    ABBusca_OrdemCentral(a->raiz, print_str);
    printf("Elementos impressos em ordem central.\n\n");

    printf("Destruindo arvore\n");
    ABBusca_Destruir(a, NULL);
    printf("Arvore destruida com sucesso.\n");
    
    return 0;
}
```

__Saída esperada:__

```
Teste 01: Strings
Arvore inicializada com sucesso.

Adicionando varios elementos a lista.
Adicionados varios elementos a lista.
Imprimindo elementos em ordem central:
Joaquim
Lana
Lucas
Miguel
Miguel
Names r us
Rafael
zzz
Elementos impressos em ordem central.

Procurando pelo nodo "Marcelo": Nao encontrado.
Procurando pelo nodo "Rafael": Encontrado no endereco 0081cce8
Removendo o nodo "Rafael"
Nodo removido com sucesso, I guess.

Imprimindo elementos em ordem central:
Joaquim
Lana
Lucas
Miguel
Miguel
Names r us
zzz
Elementos impressos em ordem central.

Destruindo arvore
Arvore destruida com sucesso.
```

#### ABNodo.h ####

##### TesteABNodo.c #####

__Código fonte:__

```c
#include "ABNodo.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int *temp = (int *)malloc(sizeof(int));
    *temp = 35;
    ABNodo *a = ABNodo_Inicializar(NULL, temp);
    temp = (int *)malloc(sizeof(int));
    *temp = 20;
    ABNodo *b = ABNodo_Inicializar(a, temp);
    temp = (int *)malloc(sizeof(int));
    *temp = 21;
    ABNodo *c = ABNodo_Inicializar(a, temp);
    if (a == NULL || b == NULL || c == NULL){
        printf("Falha na inicialização dos nodos\n");
        exit(1);
    }
    printf("Nodos inicializados com sucesso.\n");
    a->esq = b;
    a->dir = c;
    if (a->dir == c && a->esq == b){
        printf("Nodos posicionados corretamente.\n");
    } else {
        printf("Falha no posicionamento dos nodos.\n");
        exit(1);
    }
    ABNodo_Destruir(a, NULL);
    ABNodo_Destruir(b, NULL);
    ABNodo_Destruir(c, NULL);
    printf("Nodos destruidos com sucesso.\n");
    return 0;
}
```

__Saída esperada:__

```
Nodos inicializados com sucesso.
Nodos posicionados corretamente.
Nodos destruidos com sucesso.
```

#### BitString.h ####

##### Teste1.c #####

__Código fonte:__

```c
#include "BitString.h"
#include <stdio.h>
#include <stdlib.h>

#define TAM 8

void ImprimirBitString(BitString *bs){
    int tam = BitString_ObterTamanho(bs);
    for (int i = 0; i < tam; i++)
        printf("%d", BitString_ObterBit(bs, i));
    printf("\n");
}

int main(int argc, char const *argv[])
{
    BitString *a = BitString_Inicializar(TAM);
    BitString *b = BitString_Inicializar(TAM);

    BitString_DefinirBit(a, 0, 1);
    BitString_DefinirBit(a, 2, 1);
    BitString_DefinirBit(a, 4, 1);
    BitString_DefinirBit(a, 6, 1);

    printf("BitString A: ");
    ImprimirBitString(a);

    BitString_DefinirBit(b, 0, 1);
    BitString_DefinirBit(b, 3, 1);
    BitString_DefinirBit(b, 5, 1);
    BitString_DefinirBit(b, 6, 1);

    printf("BitString B: ");
    ImprimirBitString(b);

    BitString *buffer = BitString_Inicializar(TAM);

    BitString_And(a, b, buffer);
    printf("A&B: ");
    ImprimirBitString(buffer);

    BitString_Or(a, b, buffer);
    printf("A|B: ");
    ImprimirBitString(buffer);

    BitString_Xor(a, b, buffer);
    printf("A^B: ");
    ImprimirBitString(buffer);

    BitString_Not(a, buffer);
    printf("~A: ");
    ImprimirBitString(buffer);

    BitString_Not(b, buffer);
    printf("~B: ");
    ImprimirBitString(buffer);

    BitString_And(a, buffer, buffer);
    printf("A-B: ");
    ImprimirBitString(buffer);

    BitString_Destruir(a);
    BitString_Destruir(b);
    BitString_Destruir(buffer);

    return 0;
}
```

__Saída esperada:__

```
BitString A: 10101010
BitString B: 10010110
A&B: 10000010
A|B: 10111110
A^B: 00111100
~A: 01010101
~B: 01101001
A-B: 00101000
```

#### HashTable_ABB.h ####

##### Teste0.c #####

__Código fonte:__

```c
#include "HashTable_ABB.h"
#include <stdio.h>
#include <stdlib.h>

bool comp(void *a, void *b){
    return *((int *)a) > *((int *)b);
}

bool igual(void *a, void *b){
    return *((int *)a) == *((int *)b);
}

void ImprimirInteiro(void *dados){
    printf("%d ", *((int *)dados));
}

int hash(void *dados, int tam){
    return (*((int *)dados) % tam + tam) % tam;
}

ABNodo *AdicionarInteiro(HashTable_ABB *tabela, int val){
    int *temp = (int *)malloc(sizeof(int));
    *temp = val;
    return HashTable_ABB_AdicionarElemento(tabela, temp);
}

void RemoverInteiro(HashTable_ABB *tabela, int val){
    int *temp = (int *)malloc(sizeof(int));
    *temp = val;
    HashTable_ABB_RemoverElemento(tabela, temp, NULL);
    free(temp);
}

#define HT_TAM 23

int main(int argc, char const *argv[])
{
    printf("Inicializando hash table\n");
    HashTable_ABB *tabela = HashTable_ABB_Inicializar(HT_TAM, comp, igual, hash);
    if (tabela == NULL){
        printf("Falha na inicializacao.\n");
        exit(1);
    }
    printf("Inicializada com sucesso em %p.\n\n", tabela);

    printf("Adicionando alguns elementos.\n");
    int i;
    for (i = -1000; i < 1001; i++)
        AdicionarInteiro(tabela, i);
    printf("Elementos adicionados.\n");

    printf("Removendo os multiplos de cinco.\n");
    for (i = -1000; i < 1001; i += 5)
        RemoverInteiro(tabela, i);

    printf("Imprimindo os elementos, bucket por bucket.\n");
    for (i = 0; i < HT_TAM; i++){
        printf("\n\nBalde %d\n", i);
        ABBusca_OrdemCentral(ObterRaiz(HashTable_ABB_ObterABBusca(tabela, i)), ImprimirInteiro);
    }
    printf("\nImpressao finalizada.\n");

    printf("\nFinalizando hash table...\n");
    HashTable_ABB_Destruir(tabela, NULL);
    printf("Destruida com sucesso.\n");
    return 0;
}
```

__Saída esperada:__

```
Inicializando hash table
Inicializada com sucesso em 00552340.

Adicionando alguns elementos.
Elementos adicionados.
Removendo os multiplos de cinco.
Imprimindo os elementos, bucket por bucket.


Balde 0
-989 -966 -943 -897 -874 -851 -828 -782 -759 -736 -713 -667 -644 -621 -598 -552 -529 -506 -483 -437 -414 -391 -368 -322 -299 -276 -253 -207 -184 -161 -138 -92 -69 -46 -23 23 46 69 92 138 161 184 207 253 276 299 322 368 391 414 437 483 506 529 552 598 621 644 667 713 736 759 782 828 851 874 897 943 966 989

Balde 1
-988 -942 -919 -896 -873 -827 -804 -781 -758 -712 -689 -666 -643 -597 -574 -551 -528 -482 -459 -436 -413 -367 -344 -321 -298 -252 -229 -206 -183 -137 -114 -91 -68 -22 1 24 47 93 116 139 162 208 231 254 277 323 346 369 392 438 461 484 507 553 576 599 622 668 691 714 737 783 806 829 852 898 921
944 967

Balde 2
-987 -964 -941 -918 -872 -849 -826 -803 -757 -734 -711 -688 -642 -619 -596 -573 -527 -504 -481 -458 -412 -389 -366 -343 -297 -274 -251 -228 -182 -159 -136 -113 -67 -44 -21 2 48 71 94 117 163 186 209 232 278 301 324 347 393 416 439 462 508 531 554 577 623 646 669 692 738 761 784 807 853 876 899 922 968 991

Balde 3
-986 -963 -917 -894 -871 -848 -802 -779 -756 -733 -687 -664 -641 -618 -572 -549 -526 -503 -457 -434 -411 -388 -342 -319 -296 -273 -227 -204 -181 -158 -112 -89 -66 -43 3 26 49 72 118 141 164 187 233 256 279 302 348 371 394 417 463 486 509 532 578 601 624 647 693 716 739 762 808 831 854 877 923
946 969 992

Balde 4
-962 -939 -916 -893 -847 -824 -801 -778 -732 -709 -686 -663 -617 -594 -571 -548 -502 -479 -456 -433 -387 -364 -341 -318 -272 -249 -226 -203 -157 -134 -111 -88 -42 -19 4 27 73 96 119 142 188 211 234 257 303 326 349 372 418 441 464 487 533 556 579 602 648 671 694 717 763 786 809 832 878 901 924
947 993

Balde 5
-984 -961 -938 -892 -869 -846 -823 -777 -754 -731 -708 -662 -639 -616 -593 -547 -524 -501 -478 -432 -409 -386 -363 -317 -294 -271 -248 -202 -179 -156 -133 -87 -64 -41 -18 28 51 74 97 143 166 189 212 258 281 304 327 373 396 419 442 488 511 534 557 603 626 649 672 718 741 764 787 833 856 879 902 948 971 994

Balde 6
-983 -937 -914 -891 -868 -822 -799 -776 -753 -707 -684 -661 -638 -592 -569 -546 -523 -477 -454 -431 -408 -362 -339 -316 -293 -247 -224 -201 -178 -132 -109 -86 -63 -17 6 29 52 98 121 144 167 213 236 259 282 328 351 374 397 443 466 489 512 558 581 604 627 673 696 719 742 788 811 834 857 903 926
949 972

Balde 7
-982 -959 -936 -913 -867 -844 -821 -798 -752 -729 -706 -683 -637 -614 -591 -568 -522 -499 -476 -453 -407 -384 -361 -338 -292 -269 -246 -223 -177 -154 -131 -108 -62 -39 -16 7 53 76 99 122 168 191 214 237 283 306 329 352 398 421 444 467 513 536 559 582 628 651 674 697 743 766 789 812 858 881 904 927 973 996

Balde 8
-981 -958 -912 -889 -866 -843 -797 -774 -751 -728 -682 -659 -636 -613 -567 -544 -521 -498 -452 -429 -406 -383 -337 -314 -291 -268 -222 -199 -176 -153 -107 -84 -61 -38 8 31 54 77 123 146 169 192 238 261 284 307 353 376 399 422 468 491 514 537 583 606 629 652 698 721 744 767 813 836 859 882 928
951 974 997

Balde 9
-957 -934 -911 -888 -842 -819 -796 -773 -727 -704 -681 -658 -612 -589 -566 -543 -497 -474 -451 -428 -382 -359 -336 -313 -267 -244 -221 -198 -152 -129 -106 -83 -37 -14 9 32 78 101 124 147 193 216 239 262 308 331 354 377 423 446 469 492 538 561 584 607 653 676 699 722 768 791 814 837 883 906 929 952 998

Balde 10
-979 -956 -933 -887 -864 -841 -818 -772 -749 -726 -703 -657 -634 -611 -588 -542 -519 -496 -473 -427 -404 -381 -358 -312 -289 -266 -243 -197 -174 -151 -128 -82 -59 -36 -13 33 56 79 102 148 171 194 217 263 286 309 332 378 401 424 447 493 516 539 562 608 631 654 677 723 746 769 792 838 861 884 907 953 976 999

Balde 11
-978 -932 -909 -886 -863 -817 -794 -771 -748 -702 -679 -656 -633 -587 -564 -541 -518 -472 -449 -426 -403 -357 -334 -311 -288 -242 -219 -196 -173 -127 -104 -81 -58 -12 11 34 57 103 126 149 172 218 241 264 287 333 356 379 402 448 471 494 517 563 586 609 632 678 701 724 747 793 816 839 862 908 931 954 977

Balde 12
-977 -954 -931 -908 -862 -839 -816 -793 -747 -724 -701 -678 -632 -609 -586 -563 -517 -494 -471 -448 -402 -379 -356 -333 -287 -264 -241 -218 -172 -149 -126 -103 -57 -34 -11 12 58 81 104 127 173 196 219 242 288 311 334 357 403 426 449 472 518 541 564 587 633 656 679 702 748 771 794 817 863 886 909 932 978

Balde 13
-999 -976 -953 -907 -884 -861 -838 -792 -769 -746 -723 -677 -654 -631 -608 -562 -539 -516 -493 -447 -424 -401 -378 -332 -309 -286 -263 -217 -194 -171 -148 -102 -79 -56 -33 13 36 59 82 128 151 174 197 243 266 289 312 358 381 404 427 473 496 519 542 588 611 634 657 703 726 749 772 818 841 864 887 933 956 979

Balde 14
-998 -952 -929 -906 -883 -837 -814 -791 -768 -722 -699 -676 -653 -607 -584 -561 -538 -492 -469 -446 -423 -377 -354 -331 -308 -262 -239 -216 -193 -147 -124 -101 -78 -32 -9 14 37 83 106 129 152 198 221 244 267 313 336 359 382 428 451 474 497 543 566 589 612 658 681 704 727 773 796 819 842 888 911 934 957

Balde 15
-997 -974 -951 -928 -882 -859 -836 -813 -767 -744 -721 -698 -652 -629 -606 -583 -537 -514 -491 -468 -422 -399 -376 -353 -307 -284 -261 -238 -192 -169 -146 -123 -77 -54 -31 -8 38 61 84 107 153 176 199 222 268 291 314 337 383 406 429 452 498 521 544 567 613 636 659 682 728 751 774 797 843 866 889 912 958 981

Balde 16
-996 -973 -927 -904 -881 -858 -812 -789 -766 -743 -697 -674 -651 -628 -582 -559 -536 -513 -467 -444 -421 -398 -352 -329 -306 -283 -237 -214 -191 -168 -122 -99 -76 -53 -7 16 39 62 108 131 154 177 223 246 269 292 338 361 384 407 453 476 499 522 568 591 614 637 683 706 729 752 798 821 844 867 913 936 959 982

Balde 17
-972 -949 -926 -903 -857 -834 -811 -788 -742 -719 -696 -673 -627 -604 -581 -558 -512 -489 -466 -443 -397 -374 -351 -328 -282 -259 -236 -213 -167 -144 -121 -98 -52 -29 -6 17 63 86 109 132 178 201 224 247 293 316 339 362 408 431 454 477 523 546 569 592 638 661 684 707 753 776 799 822 868 891 914 937 983

Balde 18
-994 -971 -948 -902 -879 -856 -833 -787 -764 -741 -718 -672 -649 -626 -603 -557 -534 -511 -488 -442 -419 -396 -373 -327 -304 -281 -258 -212 -189 -166 -143 -97 -74 -51 -28 18 41 64 87 133 156 179 202 248 271 294 317 363 386 409 432 478 501 524 547 593 616 639 662 708 731 754 777 823 846 869 892 938 961 984

Balde 19
-993 -947 -924 -901 -878 -832 -809 -786 -763 -717 -694 -671 -648 -602 -579 -556 -533 -487 -464 -441 -418 -372 -349 -326 -303 -257 -234 -211 -188 -142 -119 -96 -73 -27 -4 19 42 88 111 134 157 203 226 249 272 318 341 364 387 433 456 479 502 548 571 594 617 663 686 709 732 778 801 824 847 893 916 939 962

Balde 20
-992 -969 -946 -923 -877 -854 -831 -808 -762 -739 -716 -693 -647 -624 -601 -578 -532 -509 -486 -463 -417 -394 -371 -348 -302 -279 -256 -233 -187 -164 -141 -118 -72 -49 -26 -3 43 66 89 112 158 181 204 227 273 296 319 342 388 411 434 457 503 526 549 572 618 641 664 687 733 756 779 802 848 871 894 917 963 986

Balde 21
-991 -968 -922 -899 -876 -853 -807 -784 -761 -738 -692 -669 -646 -623 -577 -554 -531 -508 -462 -439 -416 -393 -347 -324 -301 -278 -232 -209 -186 -163 -117 -94 -71 -48 -2 21 44 67 113 136 159 182 228 251 274 297 343 366 389 412 458 481 504 527 573 596 619 642 688 711 734 757 803 826 849 872 918 941 964 987

Balde 22
-967 -944 -921 -898 -852 -829 -806 -783 -737 -714 -691 -668 -622 -599 -576 -553 -507 -484 -461 -438 -392 -369 -346 -323 -277 -254 -231 -208 -162 -139 -116 -93 -47 -24 -1 22 68 91 114 137 183 206 229 252 298 321 344 367 413 436 459 482 528 551 574 597 643 666 689 712 758 781 804 827 873 896 919 942 988
Impressao finalizada.

Finalizando hash table...
Destruida com sucesso.
```

### Testes do trabalho ###

#### 1.tst.i ####

__Arquivo de entrada:__

```
50_users_100_items_metadata.txt 50_users_100_items_ratingsN.txt 3   6

17647
36559
6323
15853
22936

```

__Saída esperada:__

```
50_users_100_items_metadata.txt 50_users_100_items_ratingsN.txt 3   6

17647:
Most popular
Men in Black    Star Wars   Fight Club

Personalizada
Catch Me If You Can The Bourne Identity Minority Report

36559:
Most popular
The Usual Suspects  Eternal Sunshine of the Spotless Mind   Rain Man

Personalizada
Eternal Sunshine of the Spotless Mind   Lost in Translation Star Wars: Episode II - Attack of the Clones

6323:
Most popular
Raiders of the Lost Ark Kill Bill: Vol. 2   Minority Report

Personalizada
Kill Bill: Vol. 2   The Incredibles Kill Bill: Vol. 2

15853:
Most popular
Forrest Gump    Pirates of the Caribbean: The Curse of the Black Pearl  Jurassic Park

Personalizada
Terminator Salvation    V for Vendetta  Sin City

22936:
Most popular
American Beauty Independence Day    Fight Club

Personalizada
Batman Begins   Kill Bill: Vol. 2   Kill Bill: Vol. 2

```

_Os testes 2.tst.i a 10.tst.i não foram incluídos nessa documentação por serem demasiadamente extensos. A saída deles pode ser acessada nesse **[link](http://a.pomf.se/dazdnq.html)**_

Conclusão
---------

O trabalho pôde ser implementado dentro do prazo com toda a funcionalidade se comportando normalmente. Houve algumas dificuldades quanto a decisões de implementação das bibliotecas do programa, particularmente sobre como funcionariam as hash tables e como elas se relacionariam com a lógica geral do problema proposto.

O desafio também foi realizado com sucesso. Foi implementada uma interface web para o sistema, através das mesmas bibliotecas e com duas adaptações do programa principal. Isso é melhor descrito na documentação do desafio, que está disponível na página principal do website onde o sistema de recomendações está hospedado.

Anexos
------

### Listagem dos programas ###

- ABBusca_m.c
- ABBusca_m.h
- ABNodo.c
- ABNodo.h
- Arquivo.c
- Arquivo.h
- BitString.c
- BitString.h
- Filme.c
- Filme.h
- HashTable_ABB.c
- HashTable_ABB.h
- Lista.c
- Lista.h
- Main.c
- Nodo.c
- Nodo.h
- Racional.c
- Racional.h
- Sugestoes.c
- Sugestoes.h
- Sugestoes_Impressao.c
- Sugestoes_Impressao.h
- Usuario.c
- Usuario.h