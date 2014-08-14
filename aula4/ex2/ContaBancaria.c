#include <stdio.h>
#include "ContaBancaria.h"

void Inicializa (ContaBancaria *conta, int numero, double saldo){
	conta->numero = numero;
	conta->saldo = saldo;
}

void Deposito (ContaBancaria *conta, double valor){
	if (valor >= 0)
		conta->saldo += valor;
}

void Saque (ContaBancaria *conta, double valor){
	if (valor >= 0 && conta->saldo >= valor)
		conta->saldo -= valor;
}

void Imprime (ContaBancaria conta){
	printf("Conta numero %d\nSaldo: %.2f\n", conta.numero, conta.saldo);
}

int VerificaNum (ContaBancaria conta, int num){
    return conta.numero == num;
}

double ConsultaSaldo (ContaBancaria conta){
    return conta.saldo;
}

#endif