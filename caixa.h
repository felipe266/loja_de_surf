#ifndef CAIXA_H
#define CAIXA_H

#include<stdlib.h>
#include<string.h>

typedef struct produtos{
    int codigo;
    char nome[100];
    char descricao[100];
    float preco;
    struct produtos *prox;
    struct prudutos *ant;
}prod;

typedef struct lista_codigos{
    int codigo;
    struct lista_codigos *prox_cod;
    struct lista_codigos *ant_cod;
}lc;

typedef struct caixa_de_produtos{
    lc* inicio;
    int codigo;
    int tam;
    struct caixa_de_produtos *prox_caixa;
}cdp;

typedef struct pilhas_de_caixas{
    cdp* topo;
    int quant;
}pdc;

typedef struct pilha_auxiliar_de_caixas{
    cdp* topo;
    int quant;
}padc;

typedef struct produtos_comprados{
    prod* dados_prod;
    char *nome_cliente;
    int cpf;
    int cep;
    char nome_rua[100];
    int numero_casa;
    char complemento[100];
    struct produtos_comprados *prox;
}prod_comp;

extern prod_comp *inicio_prod_comp = NULL;
extern prod_comp *fim_prod_comp = NULL;
extern prod *inicio = NULL;
extern prod *fim = NULL;
extern int tamanho = 0;
extern codigo_caixa = 1;

prod *add(int codigo, char nome[100], char descricao[100], float preco);
void imprimir_pilha(pdc *p, char *nome_produto);
void comprar(pdc *p, int cod);
prod *removerprodlis(prod *produto, int codigo);
void add_pedidos_entrega(prod *dados, char *nome_cliente, int cpf, int cep, char *nome_rua, int numero_casa, char *complemento);
void realizar_entrega();
void imprimir_lista_produtos_comprados();
pdc *iniciliza_pilha();
void add_pilha(pdc *p, prod *produto);

#endif