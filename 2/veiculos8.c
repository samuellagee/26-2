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

int compararModelo(char *a, char *b){
    int i = 0;
    char ca, cb;

    while(a[i] != '\0' && b[i] != '\0'){
        ca = a[i];
        cb = b[i];

        if(ca >= 'A' && ca <= 'Z') ca = ca + 32;
        if(cb >= 'A' && cb <= 'Z') cb = cb + 32;

        if(ca != cb){
            return ca - cb;
        }
        i++;
    }

    return a[i] - b[i];
}

void selectionSort(Veiculo *v, int n){
    int i, j, menor;
    Veiculo tmp;

    for(i = 0; i < n - 1; i++){
        menor = i;

        for(j = i + 1; j < n; j++){
            if(compararModelo(v[j].modelo, v[menor].modelo) < 0){
                menor = j;
            }
        }

        if(menor != i){
            tmp = v[i];
            v[i] = v[menor];
            v[menor] = tmp;
        }
    }
}

int buscaBinaria(Veiculo *v, int n, char *chave){
    int inicio = 0;
    int fim = n - 1;
    int meio;
    int cmp;
    int achou = 0;

    while(inicio <= fim && achou == 0){
        meio = (inicio + fim) / 2;
        cmp = compararModelo(v[meio].modelo, chave);

        if(cmp == 0){
            achou = 1;
        }else if(cmp < 0){
            inicio = meio + 1;
        }else{
            fim = meio - 1;
        }
    }

    return achou;
}

int main(){
    int n;
    Veiculo *veiculos = lerCsv("/tmp/veiculos.csv", &n);

    Veiculo *selecionados = (Veiculo*) malloc(n * sizeof(Veiculo));
    int qtd = 0;

    int id;
    int i;
    char linha[MAX_STR];

    scanf("%d", &id);

    while(id != -1){
        int achouId = 0;
        i = 0;

        while(i < n && achouId == 0){
            if(veiculos[i].id == id){
                selecionados[qtd++] = veiculos[i];
                achouId = 1;
            }
            i++;
        }

        scanf("%d", &id);
    }

    selectionSort(selecionados, qtd);

    getchar(); /* consome o '\n' deixado pelo ultimo scanf antes do fgets */

    int fim = 0;
    while(fim == 0 && fgets(linha, MAX_STR, stdin) != NULL){
        int len = 0;
        while(linha[len] != '\0') len++;
        if(len > 0 && linha[len-1] == '\n'){
            linha[len-1] = '\0';
        }

        if(strcmp(linha, "FIM") == 0){
            fim = 1;
        }else{
            if(buscaBinaria(selecionados, qtd, linha)){
                printf("SIM\n");
            }else{
                printf("NAO\n");
            }
        }
    }

    free(selecionados);
    free(veiculos);
    return 0;
}
