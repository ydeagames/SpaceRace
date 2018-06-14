#include "GameUtils.h"
#include <math.h>

float GetRandomF(void)
{
	return (float)GetRand(RAND_MAX) / RAND_MAX;
}

float GetRandF(float max)
{
	return GetRandomF() * max;
}

int GetRandRange(int min, int max)
{
	return GetRand(max - min) + min;
}

float GetRandRangeF(float min, float max)
{
	return GetRandF(max - min) + min;
}

int GetLoop(int x, int w)
{
	return ((x % w) + w) % w;
}

float GetLoopF(float x, float w)
{
	return fmodf((fmodf(x, w) + w), w);
}

int GetLoopRange(int x, int min, int max)
{
	return GetLoop(x - min, max - min) + min;
}

float GetLoopRangeF(float x, float min, float max)
{
	return GetLoopF(x - min, max - min) + min;
}

int GetAbs(int a)
{
	return a > 0 ? a : -a;
}

float GetAbsF(float a)
{
	return a > 0 ? a : -a;
}