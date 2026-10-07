#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 50
#define MAX_COMBUSTIVEIS 5
#define MAX_COMB_STR 20
#define MAX_LINHA 300

typedef struct {
    int ano;
    int mes;
    int dia;
} Data;

Data parseData(char *s){
    Data d;
    sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);
    return d;
}

void formatData(Data d, char *buffer){
    sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

typedef struct {
    int id;
    char marca[MAX_STR];
    char modelo[MAX_STR];
    int ano;
    char categoria[MAX_STR];
    char combustivel[MAX_COMBUSTIVEIS][MAX_COMB_STR];
    int cilindros;
    double cilindrada;
    char transmissao[MAX_STR];
    char tracao[MAX_STR];
    double consumoCidade;
    double consumoEstrada;
    double co2;
    int turbo;
    Data dataRegistro;
} Veiculo;

static void copiarString(char *destino, char *origem){
    int i;
    for(i = 0; origem[i] != '\0'; i++){
        destino[i] = origem[i];
    }
    destino[i] = '\0';
}

static void separarCombustivel(char *str, char destino[MAX_COMBUSTIVEIS][MAX_COMB_STR]){
    int i = 0, j = 0, k = 0;

    for(k = 0; k < MAX_COMBUSTIVEIS; k++){
        destino[k][0] = '\0';
    }

    k = 0;
    while(str[i] != '\0'){
        if(str[i] == ';'){
            destino[k][j] = '\0';
            k++;
            j = 0;
        }else{
            destino[k][j++] = str[i];
        }
        i++;
    }
    destino[k][j] = '\0';
}

static void formatCombustivel(char combustivel[MAX_COMBUSTIVEIS][MAX_COMB_STR], char *buffer){
    int i, pos = 0;

    for(i = 0; i < MAX_COMBUSTIVEIS && combustivel[i][0] != '\0'; i++){
        pos += sprintf(buffer + pos, "%s", combustivel[i]);
        if(i < MAX_COMBUSTIVEIS - 1 && combustivel[i+1][0] != '\0'){
            pos += sprintf(buffer + pos, ",");
        }
    }
}

Veiculo* parseVeiculo(char *s){
    Veiculo *v = (Veiculo*) malloc(sizeof(Veiculo));
    char copia[MAX_LINHA];
    char *token;
    int i;

    for(i = 0; s[i] != '\0'; i++){
        copia[i] = s[i];
    }
    copia[i] = '\0';

    token = strtok(copia, ",");
    v->id = atoi(token);

    token = strtok(NULL, ",");
    copiarString(v->marca, token);

    token = strtok(NULL, ",");
    copiarString(v->modelo, token);

    token = strtok(NULL, ",");
    v->ano = atoi(token);

    token = strtok(NULL, ",");
    copiarString(v->categoria, token);

    token = strtok(NULL, ",");
    separarCombustivel(token, v->combustivel);

    token = strtok(NULL, ",");
    v->cilindros = atoi(token);

    token = strtok(NULL, ",");
    v->cilindrada = atof(token);

    token = strtok(NULL, ",");
    copiarString(v->transmissao, token);

    token = strtok(NULL, ",");
    copiarString(v->tracao, token);

    token = strtok(NULL, ",");
    v->consumoCidade = atof(token);

    token = strtok(NULL, ",");
    v->consumoEstrada = atof(token);

    token = strtok(NULL, ",");
    v->co2 = atof(token);

    token = strtok(NULL, ",");
    v->turbo = (token[0] == 't');

    token = strtok(NULL, ",");
    v->dataRegistro = parseData(token);

    return v;
}

void formatVeiculo(Veiculo v, char *buffer){
    char bufData[20];
    char bufComb[100];

    formatData(v.dataRegistro, bufData);
    formatCombustivel(v.combustivel, bufComb);

    sprintf(buffer,
            "[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %s ## %s]",
            v.id, v.marca, v.modelo, v.ano, v.categoria, bufComb,
            v.cilindros, v.cilindrada, v.transmissao, v.tracao,
            v.consumoCidade, v.consumoEstrada, v.co2,
            v.turbo ? "true" : "false", bufData);
}

Veiculo* lerCsv(char *caminhoArquivo, int *n){
    FILE *arquivo = fopen(caminhoArquivo, "r");
    char linha[MAX_LINHA];
    int total = 0;
    int i;
    Veiculo *veiculos;

    if(arquivo == NULL){
        printf("Erro ao ler arquivo\n");
        *n = 0;
        return NULL;
    }

    fgets(linha, MAX_LINHA, arquivo);
    while(fgets(linha, MAX_LINHA, arquivo) != NULL){
        total++;
    }

    veiculos = (Veiculo*) malloc(total * sizeof(Veiculo));

    rewind(arquivo);
    fgets(linha, MAX_LINHA, arquivo);

    i = 0;
    while(fgets(linha, MAX_LINHA, arquivo) != NULL){
        int len = 0;
        Veiculo *v;

        while(linha[len] != '\0') len++;
        if(len > 0 && linha[len-1] == '\n'){
            linha[len-1] = '\0';
        }

        v = parseVeiculo(linha);
        veiculos[i] = *v;
        free(v);
        i++;
    }

    fclose(arquivo);
    *n = total;
    return veiculos;
}

typedef struct No {
    Veiculo dado;
    struct No *proximo;
} No;

typedef struct {
    No *inicio;
    No *fim;
    int n;
} Lista;

void inicializarLista(Lista *l){
    l->inicio = NULL;
    l->fim = NULL;
    l->n = 0;
}

void inserirInicio(Lista *l, Veiculo v){
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = v;
    novo->proximo = l->inicio;

    l->inicio = novo;
    if(l->fim == NULL){
        l->fim = novo;
    }
    l->n++;
}

void inserirFim(Lista *l, Veiculo v){
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = v;
    novo->proximo = NULL;

    if(l->fim == NULL){
        l->inicio = novo;
        l->fim = novo;
    }else{
        l->fim->proximo = novo;
        l->fim = novo;
    }
    l->n++;
}

void inserir(Lista *l, Veiculo v, int posicao){
    No *atual;
    No *novo;
    int i;

    if(posicao == 0){
        inserirInicio(l, v);
        return;
    }
    if(posicao == l->n){
        inserirFim(l, v);
        return;
    }

    atual = l->inicio;
    for(i = 0; i < posicao - 1; i++){
        atual = atual->proximo;
    }

    novo = (No*) malloc(sizeof(No));
    novo->dado = v;
    novo->proximo = atual->proximo;
    atual->proximo = novo;
    l->n++;
}

Veiculo removerInicio(Lista *l){
    No *velho = l->inicio;
    Veiculo resp = velho->dado;

    l->inicio = velho->proximo;
    if(l->inicio == NULL){
        l->fim = NULL;
    }

    free(velho);
    l->n--;
    return resp;
}

Veiculo removerFim(Lista *l){
    No *atual;
    Veiculo resp;

    if(l->inicio == l->fim){
        return removerInicio(l);
    }

    atual = l->inicio;
    while(atual->proximo != l->fim){
        atual = atual->proximo;
    }

    resp = l->fim->dado;
    free(l->fim);
    atual->proximo = NULL;
    l->fim = atual;
    l->n--;
    return resp;
}

Veiculo remover(Lista *l, int posicao){
    No *atual;
    No *alvo;
    Veiculo resp;
    int i;

    if(posicao == 0){
        return removerInicio(l);
    }
    if(posicao == l->n - 1){
        return removerFim(l);
    }

    atual = l->inicio;
    for(i = 0; i < posicao - 1; i++){
        atual = atual->proximo;
    }

    alvo = atual->proximo;
    resp = alvo->dado;

    atual->proximo = alvo->proximo;
    free(alvo);
    l->n--;
    return resp;
}

void mostrar(Lista *l){
    No *atual = l->inicio;
    char buffer[300];

    while(atual != NULL){
        formatVeiculo(atual->dado, buffer);
        printf("%s\n", buffer);
        atual = atual->proximo;
    }
}

Veiculo buscar(Veiculo *veiculos, int n, int id){
    int i = 0;
    int achou = 0;
    Veiculo resp;

    while(i < n && achou == 0){
        if(veiculos[i].id == id){
            resp = veiculos[i];
            achou = 1;
        }
        i++;
    }

    return resp;
}

int main(){
    int n;
    Veiculo *veiculos = lerCsv("/tmp/veiculos.csv", &n);

    Lista lista;
    inicializarLista(&lista);

    int id;
    scanf("%d", &id);
    while(id != -1){
        Veiculo v = buscar(veiculos, n, id);
        inserirFim(&lista, v);
        scanf("%d", &id);
    }

    int qtd, i;
    scanf("%d", &qtd);

    for(i = 0; i < qtd; i++){
        char cmd[10];
        scanf("%s", cmd);

        if(strcmp(cmd, "II") == 0){
            int novoId;
            scanf("%d", &novoId);
            inserirInicio(&lista, buscar(veiculos, n, novoId));

        }else if(strcmp(cmd, "IF") == 0){
            int novoId;
            scanf("%d", &novoId);
            inserirFim(&lista, buscar(veiculos, n, novoId));

        }else if(strcmp(cmd, "I*") == 0){
            int posicao, novoId;
            scanf("%d", &posicao);
            scanf("%d", &novoId);
            inserir(&lista, buscar(veiculos, n, novoId), posicao);

        }else if(strcmp(cmd, "RI") == 0){
            Veiculo removido = removerInicio(&lista);
            printf("(R)%s %s\n", removido.marca, removido.modelo);

        }else if(strcmp(cmd, "RF") == 0){
            Veiculo removido = removerFim(&lista);
            printf("(R)%s %s\n", removido.marca, removido.modelo);

        }else if(strcmp(cmd, "R*") == 0){
            int posicao;
            scanf("%d", &posicao);
            Veiculo removido = remover(&lista, posicao);
            printf("(R)%s %s\n", removido.marca, removido.modelo);
        }
    }

    mostrar(&lista);

    free(veiculos);
    return 0;
}
