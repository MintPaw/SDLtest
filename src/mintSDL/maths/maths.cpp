#include "mintSDL/maths/maths.h"

float mint_MathMin(float a, float b)
{
	return a < b ? a : b;
}

float mint_MathMax(float a, float b)
{
	return a > b ? a : b;
}

float mint_MathClamp(float a, float min, float max)
{
	if (a < min) return min;
	if (a > max) return max;
	return a;
}