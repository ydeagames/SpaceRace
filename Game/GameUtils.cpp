#include "GameUtils.h"
#include <math.h>

// 0.0��x��1.0 �̏��������_������
float GetRandomF(void)
{
	return (float)GetRand(RAND_MAX) / RAND_MAX;
}

// 0.0��x��max �̏��������_������
float GetRandF(float max)
{
	return GetRandomF() * max;
}

// min��x��max �̐��������_������
int GetRandRange(int min, int max)
{
	return GetRand(max - min) + min;
}

// min��x��max �̏��������_������
float GetRandRangeF(float min, float max)
{
	return GetRandF(max - min) + min;
}

// 0�`w �̐������[�v
int GetLoop(int x, int w)
{
	return ((x % w) + w) % w;
}

// 0�`w �̏������[�v
float GetLoopF(float x, float w)
{
	return fmodf((fmodf(x, w) + w), w);
}

// min�`max �̐������[�v
int GetLoopRange(int x, int min, int max)
{
	return GetLoop(x - min, max - min) + min;
}

// min�`max �̏������[�v
float GetLoopRangeF(float x, float min, float max)
{
	return GetLoopF(x - min, max - min) + min;
}

// ������Βl
int GetAbs(int a)
{
	return a > 0 ? a : -a;
}

// ������Βl
float GetAbsF(float a)
{
	return a > 0 ? a : -a;
}

// �����ŏ��l
int GetMin(int a, int b)
{
	return a < b ? a : b;
}

// �����ŏ��l
float GetMinF(float a, float b)
{
	return a < b ? a : b;
}

// �����ő�l
int GetMax(int a, int b)
{
	return a > b ? a : b;
}

// �����ő�l
float GetMaxF(float a, float b)
{
	return a > b ? a : b;
}

// 0�`max�͈̔͂�x�͉�%�̈ʒu�ɂ���̂�
// �� �͈͊O�͔͈͓��Ɏ��߂��܂�
float GetPercentage(float x, float max)
{
	float n = ClampF(x, 0, max);
	return n / max;
}

// min�`max�͈̔͂�x�͉�%�̈ʒu�ɂ���̂�
// �� �͈͊O�͔͈͓��Ɏ��߂��܂�
float GetPercentageRange(float x, float min, float max)
{
	return GetPercentage(x - min, max - min);
}

// 0�`max�͈̔͂ł�percent%�̈ʒu
float GetPercentValue(float percent, float max)
{
	return max * percent;
}

// min�`max�͈̔͂ł�percent%�̈ʒu
float GetPercentValueRange(float percent, float min, float max)
{
	return GetPercentValue(percent, max - min);
}
