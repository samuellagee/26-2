#include <stdlib.h>
#include <stdio.h>

typedef struct Pessoa{
	char nome[51];
	float altura;
}Pessoa;

void sort(Pessoa p[], int n){
	for(int i = 1; i < n; i++){
		Pessoa tmp = p[i];
		int j = i - 1;
		while(j >= 0 && p[j].altura > tmp.altura){
			p[j+1] = p[j];
			j--;
		}
	
		p[j+1] = tmp;
	}
}

int main(){
	int f, a;
	scanf("%d %d", &f, &a);
	int n = f*a;

	Pessoa* p = (Pessoa*)malloc(n*sizeof(Pessoa));

	for(int i = 0; i < n; i++){
		Pessoa aux;
		scanf("%f %[^\n]", &aux.altura, aux.nome);
		p[i] = aux;
	}

	sort(p, n);

	int num = 0;
	int numFil = 1;

	while(num < n){
		for(int i = 0; i < a && num < n; i++){
			printf("%d %.2f %s \n", numFil, p[num].altura, p[num].nome);
			num++;
		}
		numFil++;
	}
}
