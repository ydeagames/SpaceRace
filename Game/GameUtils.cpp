#include "GameUtils.h"
#include <math.h>

// 0.0≦x≦1.0 の小数ランダム生成
float GetRandomF(void)
{
	return (float)GetRand(RAND_MAX) / RAND_MAX;
}

// 0.0≦x≦max の小数ランダム生成
float GetRandF(float max)
{
	return GetRandomF() * max;
}

// min≦x≦max の整数ランダム生成
int GetRandRange(int min, int max)
{
	return GetRand(max - min) + min;
}

// min≦x≦max の小数ランダム生成
float GetRandRangeF(float min, float max)
{
	return GetRandF(max - min) + min;
}

// 0〜w の整数ループ
int GetLoop(int x, int w)
{
	return ((x % w) + w) % w;
}

// 0〜w の小数ループ
float GetLoopF(float x, float w)
{
	return fmodf((fmodf(x, w) + w), w);
}

// min〜max の整数ループ
int GetLoopRange(int x, int min, int max)
{
	return GetLoop(x - min, max - min) + min;
}

// min〜max の小数ループ
float GetLoopRangeF(float x, float min, float max)
{
	return GetLoopF(x - min, max - min) + min;
}

// 整数絶対値
int GetAbs(int a)
{
	return a > 0 ? a : -a;
}

// 小数絶対値
float GetAbsF(float a)
{
	return a > 0 ? a : -a;
}

// 整数最小値
int GetMin(int a, int b)
{
	return a < b ? a : b;
}

// 小数最小値
float GetMinF(float a, float b)
{
	return a < b ? a : b;
}

// 整数最大値
int GetMax(int a, int b)
{
	return a > b ? a : b;
}

// 整数最大値
float GetMaxF(float a, float b)
{
	return a > b ? a : b;
}

// 0〜maxの範囲でxは何%の位置にいるのか
// ※ 範囲外は範囲内に収められます
float GetPercentage(float x, float max)
{
	float n = ClampF(x, 0, max);
	return n / max;
}

// min〜maxの範囲でxは何%の位置にいるのか
// ※ 範囲外は範囲内に収められます
float GetPercentageRange(float x, float min, float max)
{
	return GetPercentage(x - min, max - min);
}

// 0〜maxの範囲でのpercent%の位置
float GetPercentValue(float percent, float max)
{
	return max * percent;
}

// min〜maxの範囲でのpercent%の位置
float GetPercentValueRange(float percent, float min, float max)
{
	return GetPercentValue(percent, max - min);
}
