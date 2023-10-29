//
// Created by Luís Fernando on 02/10/2023.
//

#include "proj.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void printMenu(){
    printf("Menu:\n");
    printf("1. Criar Cliente\n");
    printf("2. Apagar Cliente\n");
    printf("3. Listar Clientes\n");
    printf("4. Debitar Cliente\n");
    printf("5. Depositar Cliente\n");
    printf("6. Extrato Cliente\n");
    printf("7. Transferencia Cliente\n");}


int salvar_lista(lista_de_clientes lc, char nome[]){ // Abre arquivo no modo WB
    FILE *f= fopen("clientes", "wb");

    if(f==NULL){
        return 1;
    }
    // Escreve a lista atualizada no arquivo
    fwrite(&lc, sizeof(lista_de_clientes), 1, f);

    // Fecha arquivo
    fclose(f);

    // Indica sucesso
    return 0;
}

int carregar_lista(lista_de_clientes *lc,char nome[]){   // Abre arquivo como read
    FILE *f = fopen("clientes", "rb");
    
    if(f==NULL)
        return 1;

    //Comando para leitura de cadata tarefa dentro da lista de Tarefas no endereço de lt
    fread(lc,sizeof(lista_de_clientes),1,f);

    //Fecha arquivo
    fclose(f);

    // Indica sucesso
    return 0;
}

//1. Novo cliente
int criar_cliente(lista_de_clientes *lc){

    // Variáveis locais em formato struct
    char nome[20];
    char cpf[10];
    char tipodeconta[5];
    float valorinicial;
    char senha[10];

    // Abre arquivo
    FILE *f = fopen("arquivo.bin", "ab");

    // Se o arquivo não é encontrado retorna uma mensagem de erro
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    cliente novo_cliente;

    // Pede informações
    printf("Nome: \n");
    scanf("%s",novo_cliente.nome);

    printf("CPF: \n");
    scanf("%s",novo_cliente.cpf);

    printf("Tipo de conta (Comum ou Plus): \n");
    scanf("%s",novo_cliente.tipo);

    printf("Valor Inicial depositado: \n");
    scanf("%f",&novo_cliente.valor_inicial);

    printf("Senha: \n");
    scanf("%s",novo_cliente.senha);

    // Adiciona o cliente e aumenta a quantidade de clientes
    lc->clientes[lc->qtd] = novo_cliente;
    lc->qtd++;

    return 0;
}

//2. Apaga cliente
int apagar_cliente(lista_de_clientes *lc) {
    char cpf_input[12];
    char senha_input[11];
    int cliente_encontrado = 0; // Indica se o cliente foi encontrado

    printf("Digite o CPF: ");
    scanf("%s", cpf_input);
    printf("Digite a Senha: ");
    scanf("%s", senha_input);

    for (int i = 0; i < lc->qtd; i++) {
        if (strcmp(cpf_input, lc->clientes[i].cpf) == 0 && strcmp(senha_input, lc->clientes[i].senha) == 0) {
            // Se o CPF e a Senha baterem, apaga o cliente
            for (int j = i; j < lc->qtd - 1; j++) {
                lc->clientes[j] = lc->clientes[j + 1];
            }
            lc->qtd--;
            cliente_encontrado = 1;
            printf("Cliente apagado com sucesso!\n");
            break;
        }
    }
return 0;}

//3. Listar clientes
int listar_clientes(lista_de_clientes lc) {
    printf("Lista de Clientes: %d\n", lc.qtd);

    for (int i = 0; i < lc.qtd; i++) {
        printf("-----------------------\n");
        printf("Nome: %s\n", lc.clientes[i].nome);
        printf("CPF: %s\n", lc.clientes[i].cpf);
        printf("Tipo De Conta: %s\n", lc.clientes[i].tipo);
        printf("Valor: %.2f\n", lc.clientes[i].valor_inicial);
        printf("Senha: %s\n", lc.clientes[i].senha);
        printf("-----------------------\n");
    }
    return 0;
}

//4. Débito
int debito(lista_de_clientes *lc) {
    char cpf_input[12];
    char senha_input[11];
    float valor_debito,taxa;
    printf("Digite o CPF: ");
    scanf("%s", cpf_input);
    printf("Digite a Senha: ");
    scanf("%s", senha_input);
    printf("Digite o valor a ser debitado: ");
    scanf("%lf", &valor_debito);

    int cliente_encontrado = 0;

    for (int i = 0; i < lc->qtd; i++) {
        if (strcmp(cpf_input, lc->clientes[i].cpf) == 0 && strcmp(senha_input, lc->clientes[i].senha) == 0) {
            // Se o CPF e a Senha estiverem corretos, debite do cliente
            if (strcmp("comum",lc->clientes[i].tipo) == 0){
                taxa = 0.05* valor_debito;
                if(lc->clientes[i].valor_inicial + taxa - valor_debito >=-1000){
                    lc->clientes[i].valor_inicial -= valor_debito + taxa;

                }
            }
            if(strcmp("plus", lc->clientes[i].tipo) == 0){
                taxa = 0.03* valor_debito;
                printf("%d", taxa);
                if(lc->clientes[i].valor_inicial + taxa - valor_debito >=-5000){
                    lc->clientes[i].valor_inicial -= valor_debito + taxa;
                    lc->clientes[i].valor_inicial -= (valor_debito + taxa);
                    printf("Debitou, %f, da sua conta com sucesso \n", valor_debito);
                }
            }
            else {
                printf("Saldo insuficiente para debitar este valor.\n");
            }
            cliente_encontrado = 1;
            break;
        }
    }

    if (!cliente_encontrado) {
        printf("Cliente não encontrado ou CPF/Senha incorretos.\n");
    }

    return 0;
}

//5. Depósito
int deposito(lista_de_clientes *lc) {
    char cpf_input[12];
    char senha_input[20];
    float valor_deposito;

    printf("Digite o CPF: ");
    scanf("%s", cpf_input);

    printf("Digite a Senha: ");
    scanf("%s", senha_input);


    int cliente_encontrado = 0;

    for (int i = 0; i < lc->qtd; i++) {
        if (strcmp(cpf_input, lc->clientes[i].cpf ) == 0&& strcmp(senha_input, lc->clientes[i].senha ) ==0) {
            printf("Conta validada \n");
            printf("Digite o valor a ser depositado: ");
            scanf("%f", &valor_deposito);
            // Se o CPF e a senha estiverem baterem, deposita na conta do cliente
            lc->clientes[i].valor_inicial += valor_deposito;
            printf("Valor depositado com sucesso!\n");
            cliente_encontrado = 1;
            break;
        }
    }

    if (!cliente_encontrado) {
        printf("Cliente não encontrado ou CPF incorreto.\n");
    }

    return 0;
}


//7. Transferência Entre Contas

int transferencia(lista_de_clientes *lc){
    char cpf_input[12];
    char senha_input[11];
    char cpf_destino[12];
    float valor_debito;

    printf("Digite o CPF: ");
    scanf("%s", cpf_input);
    printf("Digite a Senha: ");
    scanf("%s", senha_input);
    //Checkagem de senha e cpf
    for (int i = 0; i < lc->qtd; i++) {
        if (strcmp(cpf_input, lc->clientes[i].cpf ) == 0&& strcmp(senha_input, lc->clientes[i].senha ) ==0){
            printf("Digite o CPF da conta destino: ");
            scanf("%s", cpf_input);
            for(int j =0; j<lc->qtd; j++){
                //Checkagem do destinatario
                if (strcmp(cpf_input, lc->clientes[j].cpf) == 0){
                    printf("Destinatario encontrado com sucesso.\n Digite o valor a ser depositado na conta destino: ");
                    scanf("%f", &valor_debito);
                    //Processa a transacao
                    if(strcmp("plus", lc->clientes[i].tipo) == 0){
                        if(lc->clientes[i].valor_inicial - valor_debito>=-5000){
                            lc->clientes[i].valor_inicial = lc->clientes[i].valor_inicial - valor_debito;
                            lc->clientes[j].valor_inicial += valor_debito;
                            printf("Operacao concluida com sucesso");
                        }
                        else{
                            printf("Saldo Insuficiente");
                        }

                    }
                    //Processa a transacao
                    else if(strcmp("comum", lc->clientes[i].tipo) == 0){
                        if(lc->clientes[i].valor_inicial - valor_debito>= -1000){
                            lc->clientes[i].valor_inicial -= valor_debito;
                            lc->clientes[j].valor_inicial += valor_debito;
                            printf("Operacao concluida com sucesso");
                        }
                        else{
                            printf("Saldo insuficiente");
                        }
                    }

                }
                //Mensagem de erro caso nao encontre o CPF
                else{
                    printf("CPF nao encontrado.");
                }
            }
        }
    }

    };