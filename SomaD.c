#include <stdio.h>
#include <stdlib.h>

int main(){
	int num;

	while(scanf("%d", &num) != EOF){
		int soma = 0;
		while(num != 0){
			soma = soma + (num%10);
			num = num / 10;
		}

		printf("%d\n", soma);
	}
	

	return 0;
}
