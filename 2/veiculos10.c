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

typedef struct {
    Veiculo dados[5];
    int inicio;
    int quantidade;
} Fila;

void inicializarFila(Fila *f){
    f->inicio = 0;
    f->quantidade = 0;
}

int filaCheia(Fila *f){
    return f->quantidade == 5;
}

Veiculo desenfileirar(Fila *f){
    Veiculo resp = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % 5;
    f->quantidade--;
    return resp;
}

void enfileirar(Fila *f, Veiculo v){
    int pos = (f->inicio + f->quantidade) % 5;
    f->dados[pos] = v;
    f->quantidade++;
}

void inserirNaFila(Fila *f, Veiculo v){
    Veiculo removido;

    if(filaCheia(f)){
        removido = desenfileirar(f);
        printf("(R)%s %s\n", removido.marca, removido.modelo);
    }

    enfileirar(f, v);
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

    Fila fila;
    inicializarFila(&fila);

    int id;
    int i;
    char buffer[300];

    scanf("%d", &id);
    while(id != -1){
        Veiculo v = buscar(veiculos, n, id);
        inserirNaFila(&fila, v);
        scanf("%d", &id);
    }

    int qtd;
    scanf("%d", &qtd);

    for(i = 0; i < qtd; i++){
        char cmd[10];
        Veiculo removido;

        scanf("%s", cmd);

        if(strcmp(cmd, "I") == 0){
            int novoId;
            scanf("%d", &novoId);
            Veiculo v = buscar(veiculos, n, novoId);
            inserirNaFila(&fila, v);

        }else if(strcmp(cmd, "R") == 0){
            removido = desenfileirar(&fila);
            printf("(R)%s %s\n", removido.marca, removido.modelo);
        }
    }

    for(i = 0; i < fila.quantidade; i++){
        int pos = (fila.inicio + i) % 5;
        formatVeiculo(fila.dados[pos], buffer);
        printf("%s\n", buffer);
    }

    free(veiculos);
    return 0;
}
