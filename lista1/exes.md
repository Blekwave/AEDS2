1) ex1.c

2)
    a) Melhor caso: novo elemento > A[1]
       Pior caso: novo elemento < A[n]
    b) ex2.c

3)
    a) Calcula o somatório de 1 a A
    b) Complexidade em relação a somas: O(n)
    T(n) = T(n-1) + 1
    T(n-1) = T(n-2) + 1
    T(n) = somatório de 1 a n de 1: (1+1)/2 * n
    c) ex3.c
    d) A minha, pois ela é O(1), sendo da mesma complexidade independentemente do tamanho da entrada.

4)
    O algoritmo O(n³) é preferível para matrizes grandes. O algoritmo O(2^n) pode ser útil para matrizes de pequenas dimensões. No entanto, como só foram explicitadas as ordens de complexidade e não as funções, não é possível, por exemplo, determinar um valor de n máximo para o qual a função de O(2^n) é mais eficiente.

5)
    Melhor caso: o padrão P está nos primeiros m caracteres de T
    f(m,n) = m
    Exemplo:
        P = "OI"
        T = "OIADFHDKFH"
        O programa realiza apenas duas comparações de char e sai do for
    Pior caso: os primeiros caracteres de P estão presentes repetidamente em T
    f(m,n) = n
14)
    T(n) = 2T(n-1)
    T(0) = 1

    T(n) = 2^n