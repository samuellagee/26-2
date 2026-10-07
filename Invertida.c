#include <stdio.h>

int main() {
	char p[1000];

	scanf(" %[^\n]", p);
	while (p[0] != 'F' && p[1] != 'I' && p[2] != 'M') {

		int i = 0;

		while (p[i] != '\0') {
			i++;
		}

		for (i = i - 1; i >= 0; i--) {
			printf("%c", p[i]);
		}

		printf("\n");
		scanf(" %[^\n]", p);
	}

	return 0;
}
