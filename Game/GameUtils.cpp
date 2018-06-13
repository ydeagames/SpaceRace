#include "GameUtils.h"
#include <math.h>

float GetRandRange(float min, float max)
{
	return GetRand(max - min) + min;
}

float GetLoop(float x, float w)
{
	return fmodf((fmod(x, w) + w), w);
}

float GetLoopRange(float x, float min, float max)
{
	return GetLoop(x, max - min) + min;
}

float GetAbs(float a)
{
	return a > 0 ? a : -a;
}