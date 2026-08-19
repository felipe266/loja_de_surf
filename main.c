#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct produtos {
    int codigo;
    char *nome;
    char *descricao;
    float preco;
    struct produtos *prox;
    struct produtos *ant;
}prod;

//lista de códigos dos produtos
typedef struct no_lista_cod{
    int codigo;
    struct no_lista_cod *prox_cod;
    struct no_lista_cod *ant_cod;
}nlc;

//caixas dos produtos
typedef struct caixa_de_produtos {
    nlc *inicio;
    int codigo; 
    int tam;
    struct caixa_de_produtos *prox_caixa;
}cdp;

//pilhas de caixas
typedef struct pilhas_de_caixas{
    cdp *topo;
    int quant;
}pdc;

//pilha auxiliar
typedef struct pilhas_auxiliar_de_caixas{
    cdp *topo;
    int quant;
}padc;

//lista de produtos comprados
typedef struct produtos_comprados{
    prod *dados_prod;
    char *nome_cliente;
    int cpf;
    int cep;
    char *nome_rua;
    int numero_casa;
    char *complemento;

    struct produtos_comprados *prox;
}prod_comp;

prod_comp *inicio_prod_comp = NULL;
prod_comp *fim_prod_comp = NULL;

//add pedidos na lista de entregas
void add_pedidos_entrega(prod *dados, char *nome_cliente, int cpf, int cep, char *nome_rua, int numero_casa, char *complemento){
    prod_comp *novo = malloc(sizeof(prod_comp));
    novo->dados_prod = dados;
    novo->nome_cliente = strdup(nome_cliente);
    novo->cpf = cpf;
    novo->cpf = cep;
    novo->nome_rua = strdup(nome_rua);
    novo->numero_casa = numero_casa;
    novo->complemento = strdup(complemento);
    novo->prox = NULL;

    if (inicio_prod_comp == NULL && fim_prod_comp == NULL){
        inicio_prod_comp = novo;
        fim_prod_comp = novo;
    }else{
        fim_prod_comp->prox = novo;
        fim_prod_comp = novo;
    }
}
// Lista principal
prod *inicio = NULL;
prod *fim = NULL;
int tamanho = 0;
//codigo caixa
int codigo_caixa = 1;

//limite da caixa de produtos
int limite(prod *cod){
    if (strcmp(cod->nome, "parafina") == 0){
        return 50;
    }else if (strcmp(cod->nome, "leash") == 0){
        return 25;
    }else if (strcmp(cod->nome, "quilha") == 0){
        return 10;
    }else if (strcmp(cod->nome, "deck") == 0){
        return 5;
    }else{
        return 1;
    }
    
}

// Adicionar produto
prod *add(int codigo, char *nome, char *descricao, float preco) {
    prod *novo_prod = malloc(sizeof(prod));
    novo_prod->codigo = codigo;
    novo_prod->nome = strdup(nome);
    novo_prod->descricao = strdup(descricao);
    novo_prod->preco = preco;
    novo_prod->prox = NULL;
    novo_prod->ant = NULL;

    // Inserção ordenada na lista principal
    if(inicio == NULL){ //lista vazia
        inicio = novo_prod;
        fim = novo_prod; 
    }else{//lista nao esta vazia
        if(inicio->preco > novo_prod->preco){//adicionar no inicio!
            novo_prod->prox = inicio;
            inicio->ant = novo_prod;
            inicio = novo_prod;
        }else if(novo_prod->preco >= fim->preco){//adicionar no fim!
            fim->prox = novo_prod;
            novo_prod->ant = fim;
            fim = novo_prod;
        }else{
            //adicionar no, "meio"
            prod *aux = inicio;
            while (aux != NULL && novo_prod->preco >= aux->preco){
                aux = aux->prox;
            }
            novo_prod->prox = aux;
            novo_prod->ant = aux->ant;
            aux->ant->prox = novo_prod;
            aux->ant = novo_prod;   
        }
    }
    tamanho++;
    return novo_prod;
}

//criar pilha de ciaxas
pdc* iniciliza_pilha(){
    pdc *p = malloc(sizeof(pdc));
    p->topo = NULL;
    p->quant = 0;
    return p;
}

//criar pilha auxiliar
padc* iniciliza_pilha_aux(){
    padc *p = malloc(sizeof(pdc));
    p->topo = NULL;
    p->quant = 0;

    return p;
}

//cria caixa de produtos
cdp *add_caixa(){
    cdp *caixa = malloc(sizeof(cdp));
    caixa->inicio = NULL;
    caixa->prox_caixa = NULL;
    caixa->codigo = 2;
    caixa->tam = 0;
    return caixa;
}

//criando lista de códigos
nlc *add_cod_caixa(){
    nlc *n = malloc(sizeof(nlc));
    n->codigo = 0;
    n->prox_cod = NULL;
    n->ant_cod = NULL;
    
    return n;
}

//criando pilhas de caixa pra cada categoria de produtos
void add_pilha(pdc *p, prod *produto){
    cdp *caixa;
    //verificando se não tem nem uma caixa no topo ou se passou do limite
    if (p->topo == NULL || p->topo->tam >= limite(produto)){
        //ao adicionar mais uma caixa o topo passa a ser essa nova caixa criada
        caixa = add_caixa();
        caixa->codigo = codigo_caixa++;
        caixa->prox_caixa = p->topo;
        p->topo = caixa;
        p->quant++;
    }else{
        caixa = p->topo;
    }
    //Adicionando codigos dos produtos nas caixas
    nlc *n = add_cod_caixa();
    n->codigo = produto->codigo;
    n->prox_cod = caixa->inicio;
    if (caixa->inicio != NULL){
        caixa->inicio->ant_cod = n;
    }
    caixa->inicio = n;
    caixa->tam++;
}


void imprimir_pilha(pdc *p, char *nome_produto) {
    printf("Pilha de caixas do produto: %s\n", nome_produto);
    cdp *caixa = p->topo;
    while (caixa != NULL) {
        printf("Caixa codigo %d (quantidade: %d) endereco caixa:%p\n", caixa->codigo, caixa->tam, caixa);
        nlc *codigo = caixa->inicio;
        while (codigo != NULL) {
            printf("Produto codigo: %d\n", codigo->codigo);
            codigo = codigo->prox_cod;
        }
        caixa = caixa->prox_caixa;
    }
    printf("\n");
}

void info_prod(prod *aux){
    printf("=-=-=-==---=-=--=-=-=-=--=-=\n");
    printf("Pedido do(a) %s:\n", aux->nome);
    printf("o codigo do produto: %d\n", aux->codigo);
    printf("a descricao: %s\n", aux->descricao);
    printf("TOTAL: R$%.2f\n", aux->preco);
}

void imprimir_lista_produtos(){
    prod *aux = inicio;
    while(aux != NULL){
        info_prod(aux);
        aux = aux->prox;
    }
}

void ver_produtos(int opcao, char *nome, int preco_inicial, int preco_final){
    prod *aux = inicio;
    while(aux != NULL){
        if (opcao == 0){
            if (aux->nome == nome){
                info_prod(aux);
                aux = aux->prox;
            }
        }else{
            if (aux->preco >= preco_inicial && aux->preco<=preco_final){
                info_prod(aux);
                aux = aux->prox;
            }
        }
    }
}

void imprimir_lista_produtos_comprados(){
    prod_comp *aux = inicio_prod_comp;
    while(aux != NULL){
        printf("=-=-=-==---=-=--=-=-=-=--=-=\n");
        printf("Pedido do(a) %s:\n", aux->dados_prod->nome);
        printf("o codigo do produto: %d\n", aux->dados_prod->codigo);
        printf("nome cliente: %s\n", aux->nome_cliente);
        printf("CPF: %d\n", aux->cpf);
        printf("CEP: %d\n", aux->cep);
        printf("Nome da rua: %s\n", aux->nome_rua);
        printf("numero da casa: %d\n", aux->numero_casa);
        printf("complemento: %s\n", aux->complemento);
        aux = aux->prox;
    }
}

void comprar(pdc *p, int cod){
    cdp *caixa = p->topo;
    nlc *cod_compra = NULL;
    padc *pilha_aux = iniciliza_pilha_aux();
    while (caixa != NULL) {
        //aqui é pra pecorre
        nlc *codigo = caixa->inicio;
        //tirando a caixa que tava no topo
        p->topo = caixa->prox_caixa;
        while (codigo != NULL) {
            //pega o endereço do codigo e tira ele da lista
            if (codigo->codigo == cod){
                cod_compra = codigo;
                if (codigo->ant_cod != NULL){
                    codigo->ant_cod->prox_cod = codigo->prox_cod;
                }
                if (codigo->prox_cod != NULL){
                    codigo->prox_cod->ant_cod = codigo->ant_cod;
                }else{
                    codigo->ant_cod->prox_cod = codigo->prox_cod;
                }
                if (caixa->inicio->codigo == cod){
                    caixa->inicio = codigo->prox_cod;
                }
                
                caixa->tam--; 
                break;
            }
            codigo = codigo->prox_cod;
        }
        //aqui vai empilhanddo as caixas na pilha auxiliar
        if (pilha_aux->topo == NULL){
            pilha_aux->topo = caixa;
            pilha_aux->topo->prox_caixa = NULL;
            printf("codigo caixa: %d\n", pilha_aux->topo->codigo);
        }else{
            caixa->prox_caixa = pilha_aux->topo;
            pilha_aux->topo = caixa;
            printf("codigo caixa: %d\n", pilha_aux->topo->codigo);
        }
        if(cod_compra != NULL){
            break;
        }
        caixa = p->topo;
    }
    //aqui vai desempilhar as caixas da pilha auxiliar
    cdp *caixa_aux = pilha_aux->topo;
    printf("end caixa_aux: %p\n", caixa_aux->prox_caixa);
    while (caixa_aux->prox_caixa != NULL){
        pilha_aux->topo = caixa_aux->prox_caixa;
        if (p->topo == NULL){
            p->topo = caixa_aux;
            p->topo->prox_caixa = NULL;
        }else{
            caixa_aux->prox_caixa = p->topo;
            p->topo = caixa_aux;
        }
        caixa_aux = pilha_aux->topo;
    }
    //aqui vai pegando o primeiro produtos da ultima caixa da pilha auxiliar
    nlc * produto;
    if (caixa != caixa_aux){
        produto = pilha_aux->topo->inicio;
        pilha_aux->topo->inicio = produto->prox_cod;
        produto->prox_cod = caixa->inicio;
        caixa->inicio = produto;
        caixa->tam++;
        pilha_aux->topo->tam--;
    }
    caixa_aux->prox_caixa = p->topo;
    p->topo = caixa_aux;
    //aqui verifica se a caixa está vazia 
    cdp *lixo;
        if (p->topo->tam == 0){
            lixo = p->topo;
            p->topo = p->topo->prox_caixa;
            free(lixo);
        }
}

prod* RemoverProdLis(prod *produto, int codigo) {
    if (produto == NULL) return NULL;
    /*verificamos onde possivelmente poderia estar o produto analisando do inicio , meio , ou fim*/
    if (produto->codigo == codigo) {
        if (produto->ant != NULL)
            produto->ant->prox = produto->prox;
        else
            inicio = produto->prox;

        if (produto->prox != NULL)
            produto->prox->ant = produto->ant;
        else
            fim = produto->ant;

        produto->prox = NULL;
        produto->ant = NULL;
        tamanho--;

        return produto;
    }

    return RemoverProdLis(produto->prox, codigo);
}

int main(){
    // adicionando pilhas de caixas
    pdc *leash = iniciliza_pilha();
    pdc *quilha = iniciliza_pilha();
    pdc *deck = iniciliza_pilha();
    pdc *parafina = iniciliza_pilha();
    prod *produto;
    int cod_prod = 1;
    adicionado produtos
    for (int i = 0; i < 27; i++){
        produto = add(cod_prod++,"leash", "...", 1.1+i);
        //adicionando as caixas nas pilhas
        add_pilha(leash, produto);
    }
    imprimir_pilha(leash, "leash");
    for (int i = 0; i < 53; i++){
        produto = add(cod_prod++,"parafina", "...", 1.1+i);
        //adicionando as caixas nas pilhas
        add_pilha(parafina, produto);
    }
    imprimir_pilha(parafina, "parafina");
    for (int i = 0; i < 13; i++){
        produto = add(cod_prod++,"quilha", "...", 1.1+i);
        //adicionando as caixas nas pilhas
        add_pilha(quilha, produto);
    }
    imprimir_pilha(quilha, "quilha");
    for (int i = 0; i < 8; i++){
        produto = add(cod_prod++,"deck", "...", 1.1+i);
        //adicionando as caixas nas pilhas
        add_pilha(deck, produto);
    }
    imprimir_pilha(deck, "deck");
    imprimir_lista_produtos();
    comprar(deck, 8);
    imprimir_pilha(deck, "deck");
    prod *produto_comprado = RemoverProdLis(inicio, 8);
    
    char nome_cliente[100];
    printf("nome do cliente: ");
    scanf("%s", nome_cliente);
    int cpf;
    printf("CPF: ");
    scanf("%d", &cpf);
    int cep;
    printf("CEP: ");
    scanf("%d", &cep);
    char nome_rua[100];
    printf("Rua: ");
    scanf("%s", nome_rua);
    int numero_casa;
    printf("numero casa: ");
    scanf("%d", &numero_casa);
    char complemento[100];
    printf("complemento: ");
    scanf("%s", complemento);

    add_pedidos_entrega(produto_comprado, nome_cliente, cpf,cep,nome_rua, numero_casa, complemento);
    add_pedidos_entrega(produto_comprado, nome_cliente, cpf+2, cep+1, nome_rua, numero_casa+1, complemento);
    imprimir_lista_produtos_comprados();
    // comprar(leash, 123);
    // comprar(parafina, 123);
    // comprar(quilha, 123);
    return 0;
}   
