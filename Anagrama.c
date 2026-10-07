#include <stdio.h>
#include <stdlib.h>

int main(){
	char a[50];
	char b[50];

	scanf(" %[^\n]", a);
	scanf(" %[^\n]", b);

	while(a[0] != 'F' && a[1] != 'I' && a[2] != 'M'){
		int tamA = 0;
		int tamB = 0;
		int resp = 0;

		while(a[tamA] != '\0'){
			tamA++;
		}
		while(b[tamB] != '\0'){
			tamB++;
		}

		if(tamA != tamB) resp = 1;
		else{
			for(int i = 0; i < tamA; i++){
				int j = 0;
				int achou = 0;
				while(achou == 0 && j < tamB){
					if(a[i] == b[j]) achou = 1;
					else j++;	
				}
			if(achou == 0) resp = 1;
			}
		}

		if(resp == 0) printf("SIM\n");
		else printf("NAO\n");

		scanf(" %[^\n]", a);
		scanf(" %[^\n]", b);
	}

	return 0;
}
