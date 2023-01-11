#include <stdio.h>

void displayBits(int value);

int main()
{
	int x;

	printf("%s", "Inserisci un numero di 4 bit (tra 0 e 15): ");
	scanf("%d", &x);

	displayBits(x);
}

void displayBits(int value)
{
	int displayMask = 1 << 3;

	printf("\nprima  ");
	for (int i = 1; i <= 4; i++) {
		printf(value & displayMask ? "1" : "0");
	}

	printf("\ndopo   ");
	for (int i = 1; i <= 4; i++) {
		printf(value & displayMask ? "1" : "0");
		value <<= 1;
	}
}
