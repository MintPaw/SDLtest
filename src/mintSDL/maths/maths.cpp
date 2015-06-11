#include "mintSDL/maths/maths.h"

double mint_MathMin(double a, double b)
{
	return a < b ? a : b;
}

double mint_MathMax(double a, double b)
{
	return a > b ? a : b;
}

double mint_MathClamp(double a, double min, double max)
{
	if (a < min) return min;
	if (a > max) return max;
	return a;
}