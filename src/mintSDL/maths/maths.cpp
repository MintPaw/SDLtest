#include <stdio.h>
#include <stdlib.h>
#include "mintSDL/maths/maths.h"

float mint_MathMin(float a, float b) { return a < b ? a : b; }
float mint_MathMax(float a, float b) { return a > b ? a : b; }

int mint_MathMin(int a, int b) { return a < b ? a : b; }
int mint_MathMax(int a, int b) { return a > b ? a : b; }

float mint_MathClamp(float a, float min, float max)
{
	if (a < min) return min;
	if (a > max) return max;
	return a;
}

char* itoa(int i) {
  char* res = (char*)malloc(8*sizeof(int));
  sprintf(res, "%d", i);
  return res;
}