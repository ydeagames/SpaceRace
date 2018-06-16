#pragma once

// 0.0��x��1.0 �̏��������_������
float GetRandomF(void);

// 0.0��x��max �̏��������_������
float GetRandF(float max);

// min��x��max �̐��������_������
int GetRandRange(int min, int max);

// min��x��max �̏��������_������
float GetRandRangeF(float min, float max);

// 0�`w �̐������[�v
int GetLoop(int x, int w);

// 0�`w �̏������[�v
float GetLoopF(float x, float w);

// min�`max �̐������[�v
int GetLoopRange(int x, int min, int max);

// min�`max �̏������[�v
float GetLoopRangeF(float x, float min, float max);

// ������Βl
int GetAbs(int a);

// ������Βl
float GetAbsF(float a);

// �����ŏ��l
int GetMin(int a, int b);

// �����ŏ��l
float GetMinF(float a, float b);

// �����ő�l
int GetMax(int a, int b);

// �����ő�l
float GetMaxF(float a, float b);

// 0�`max�͈̔͂�x�͉�%�̈ʒu�ɂ���̂�
// �� �͈͊O�͔͈͓��Ɏ��߂��܂�
float GetPercentage(float x, float max);

// min�`max�͈̔͂�x�͉�%�̈ʒu�ɂ���̂�
// �� �͈͊O�͔͈͓��Ɏ��߂��܂�
float GetPercentageRange(float x, float min, float max);

// 0�`max�͈̔͂ł�percent%�̈ʒu
float GetPercentValue(float percent, float max);

// min�`max�͈̔͂ł�percent%�̈ʒu
float GetPercentValueRange(float percent, float min, float max);
