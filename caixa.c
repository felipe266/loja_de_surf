#include "caixa.h"

void add_pedidos_entrega(prod *dados, char nome_cliente[100], int cpf, int cep, char nome_rua[100], int numero_casa, char *complemento){
    prod_comp *novo = malloc(sizeof(prod_comp));
    novo->dados_prod = dados;
    novo->nome_cliente = strdup(nome_cliente);
    novo->cpf = cpf;
    novo->cep = cep;
    novo->nome_rua = st
}