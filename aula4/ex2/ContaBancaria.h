#ifndef _CONTABANCARIA_H_
#define _CONTABANCARIA_H_

typedef struct {
	int numero;
	double saldo;
} ContaBancaria;

void Inicializa (ContaBancaria *, int, double);
void Deposito (ContaBancaria *, double);
void Saque (ContaBancaria *, double);
void Imprime (ContaBancaria);
int VerificaNum (ContaBancaria, int);
double ConsultaSaldo (ContaBancaria);

#endif