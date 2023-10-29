#include <stdio.h>
#include "proj.h"


int main() {
    int opcao;
    char arquivo[] = "clientes.bin"; // Nome do arquivo para salvar e carregar os dados
    lista_de_clientes lc;
    int cod;

    cod = carregar_lista(&lc, arquivo);

    if (cod == 1) {
        lc.qtd = 0; // Inicializa a quantidade de clientes se houver um erro ao carregar
    }
    do {
        printMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                break;
            case 1:
                criar_cliente(&lc);
                break;
            case 2:
                apagar_cliente(&lc);
                break;
            case 3:
                listar_clientes(lc);
                break;
            case 4:
                debito(&lc);
                break;
            case 5:
                deposito(&lc);
                break;
            case 6:
                break;
            case 7:
                transferencia(&lc);
                break;
            default:
                printf("Opção não existe\n");
                break;
        }

    } while (opcao != 0);

    cod = salvar_lista(lc, arquivo);

    if (cod != 0) {
        printf("Erro ao salvar os dados dos clientes.\n");
    }

    return 0;
}