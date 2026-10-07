#include <stdlib.h>
#include <stdio.h>

typedef struct Aluno{
	char nome[51];
	float nota;
}Aluno;

void ordenar(Aluno vet[], int n){
	for(int i = 1; i < n; i++){
		int j = i - 1;
		Aluno tmp = vet[i];
		while(j >= 0 && vet[j].nota > tmp.nota){
			vet[j+1] = vet[j];
			j--;
		}
		if(vet[j].nota == tmp.nota){
			int tamN = tam(vet[j].nome);
			for(int k = 0; k < tamN; k++){
				if(vet[j].nome[k] < tmp.nome[k]){
					vet[j+1] = vet[j];
					j--;
				}
			}
		}

		vet[j+1] = tmp;
	}
}

int tam(char c[]){
	int n = 0;
	while(c[n] != '\0'){
		n++;
	}
return n;
}


int main(){
	int n;
	scanf("%d", &n);
	
	Aluno *vet = (Aluno*)malloc(n*sizeof(Aluno));
	for(int i = 0; i < n; i++){
		scanf("%f %[^\n]", &vet[i].nota, vet[i].nome);
	}

	ordenar(vet, n);

	for(int i = 0; i < n; i++){
		int pos = i + 1;
		printf("%d %.2f %s\n", pos, vet[i].nota, vet[i].nome);
	}

	free(vet);

	return 0;
}
