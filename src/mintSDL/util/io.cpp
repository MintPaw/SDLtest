#include <stdio.h>
#include <stdlib.h>

char* mint_IoAllText(char* fileName)
{
	char* buffer;
	FILE *pFile;
	long s;
	int i;
	int chars;

	pFile = fopen(fileName, "rb");

	if (pFile == NULL) {
		printf("Could not open the file");
		return 0;
	}

	fseek(pFile, 0, SEEK_END);
	s = ftell(pFile);
	chars = s / sizeof(char);
	rewind(pFile);

	buffer = (char*)malloc(s);

	fread(buffer, s, 1, pFile);

	fclose(pFile);

	return buffer;
}