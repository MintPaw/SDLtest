#include <stdio.h>

void mint_ArrayPrint(int* array, unsigned int length)
{
	unsigned int i;
	for (i = 0; i < length; i++) printf("%d,", array[i]);
	printf("\n");
}

void mint_ArrayPrint(char* array, unsigned int length)
{
	unsigned int i;
	for (i = 0; i < length; i++) printf("%d,", array[i]);
	printf("\n");
}