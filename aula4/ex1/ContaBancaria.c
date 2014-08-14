#include <stdio.h>
#include "ContaBancaria.h"

#ifndef CONTABANCARIA
#define CONTABANCARIA 1

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
	printf("Conta numero %d\nSaldo: %f\n", conta.numero, conta.saldo);
}

#endif