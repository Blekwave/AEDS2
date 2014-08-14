#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Contas.h"

void InicializaContas (Contas *cnt){
    cnt->numcontas = 0;
}
int CriarNovasContas (Contas *cnt, int n){
    double saldo;
    int key;
    if (n+cnt->numcontas > CONTAS_MAX)
        return 1;
    srand(time(NULL));
    for (int i = 0; i < n; i++){
        key = rand();
        printf("Digite o saldo da conta de numero %d: ", key);
        scanf("%f", &saldo);
        printf("Saldo: %d\n", saldo);
        Inicializa(&(cnt->contas[i]), key, saldo);
        (cnt->numcontas)++;
    }
    return 0;
}
void ImprimirContas (Contas *cnt){
    for (int i = 0; i < cnt->numcontas; i++){
        Imprime(cnt->contas[i]);
    }
}
int ZerarSaldoConta (Contas *cnt, int num){
    int contakey = -1;
    for(int i = 0; contakey == -1 && i < cnt->numcontas; i++)
        if (VerificaNum(cnt->contas[i], num))
            contakey = i;
    if (contakey == -1)
        return 1;
    Saque(&(cnt->contas[contakey]), ConsultaSaldo(cnt->contas[contakey]));
    return 0;
}