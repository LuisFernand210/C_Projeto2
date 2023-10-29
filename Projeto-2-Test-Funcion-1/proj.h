//
// Created by Luís Fernando on 02/10/2023.
//

#ifndef PROJETO_2_PROJ_H
#define PROJETO_2_PROJ_H


typedef struct {
    char nome[20];
    char cpf[10];
    char tipo[5];
    float valor_inicial;
    char senha[10];
}cliente;
typedef struct {
    cliente clientes[1000];
    int qtd;
} lista_de_clientes;

int criar_cliente(lista_de_clientes *lc);
int apagar_cliente(lista_de_clientes *lc);
int listar_clientes(lista_de_clientes lc);
int debito(lista_de_clientes *lc);
int deposito(lista_de_clientes *lc);
int transferencia(lista_de_clientes *lc);
void printMenu();
int salvar_lista(lista_de_clientes lt,char nome[]);
int carregar_lista(lista_de_clientes *lt, char nome[]);

#endif //PROJETO_2_PROJ_H