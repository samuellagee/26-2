#include <stdlib.h>
#include <stdio.h>

typedef struct Predio{
	char nome[31];
	int num;
}Predio;

int comparar2(char p1[], char p2[]){
	int resp = 1;
	int n1 = 0;
	int n2 = 0;
	
	while(p1[n1] != '\0') n1++;
	while(p2[n2] != '\0') n2++;

	if(n1 == n2){
		int sim = 0;
		int i = 0;
		while(i < n1 && sim >= 0){
			if(p1[i] == p2[i]) sim++;
			else sim = -1;
		}
		if(sim == n1) resp = 0;
	}

	return resp;
}

int comparar(char p1[], char p2[]){
    int i = 0;

    while(p1[i] != '\0' && p2[i] != '\0'){
        if(p1[i] < p2[i]) return 1;
        if(p1[i] > p2[i]) return 0;
        i++;
    }

    return p1[i] == '\0';
}

void ordenar(Predio vet[], int n){
	for(int i = 1; i < n; i++){
		int j = i - 1;
		Predio tmp = vet[i];
		while(j >= 0 && comparar(vet[j].nome, tmp.nome) == 0){
			vet[j+1] = vet[j];
			j--;
		}

		vet[j+1] = tmp;
	}
}

int main(){
	int n;
	while(scanf("%d", &n) != EOF){
		Predio *vet = (Predio*)malloc(n*sizeof(Predio));

		for(int i = 0; i < n; i++){
			scanf("%d %s", &vet[i].num, vet[i].nome);
		}

		ordenar(vet, n);
		for(int i = 0; i < n; i++){
			printf("%s %d\n", vet[i].nome, vet[i].num);
		}
		int p;
		scanf("%d", &p);
		char pNomes[p][31];
		for(int i = 0; i < p; i++){
			scanf("%s", pNomes[i]);
		}
		
		for(int i = 0; i < p; i++){
			for(int j = 0; j < n; j++){
				if(comparar2(pNomes[i], vet[j].nome) == 0){
					printf("%s %d\n", vet[j].nome, vet[j].num);
				}
			}
		}	
	
		free(vet);

	}




	return 0;
}
