#include <stdio.h>
#include <stdlib.h>
#include "ContaBancaria.h"

int main(int argc, char const *argv[])
{
	ContaBancaria conta1;
	Inicializa(&conta1, 123123, 350.00);
	Imprime(conta1);
	Deposito(&conta1, 50.00);
	Imprime(conta1);
	Saque(&conta1, 30.00);
	Imprime(conta1);
	return 0;
}