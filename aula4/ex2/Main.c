#include <stdio.h>
#include <stdlib.h>
#include "ContaBancaria.h"
#include "Contas.h"

int main(int argc, char const *argv[])
{
	Contas banco;
    InicializaContas(&banco);
    printf("%s\n", CriarNovasContas(&banco, 3) ? "Erro na criacao." : "Contas criadas com sucesso");
    ImprimirContas(&banco);
    int i;
    printf("Digite o numero da conta a ser zerada: ");
    scanf("%d", &i);
    ZerarSaldoConta(&banco, i);
    ImprimirContas(&banco);
	return 0;
}