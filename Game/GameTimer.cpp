#include "GameTimer.h"
#include "GameUtils.h"

// �萔�̒�` ==============================================================

#define RESOLUTION 1000

// �֐��̒�` ==============================================================

// <<�^�C�}�[>> --------------------------------------------------

// <�^�C�}�[�쐬>
GameTimer GameTimer_Create(void)
{
	return { -1, -1, TRUE };
}

// <�^�C�}�[����>
float GameTimer_GetTime(GameTimer* timer)
{
	if (!timer->paused)
		timer->last_time = GetNowCount() - timer->start_time;
	return (float)timer->last_time / RESOLUTION;
}

// <�^�C�}�[�ꎞ��~��>
BOOL GameTimer_IsPaused(GameTimer* timer)
{
	return timer->paused;
}

// <�^�C�}�[��~>
void GameTimer_Pause(GameTimer* timer)
{
	if (!timer->paused)
		timer->last_time = GetNowCount() - timer->start_time;
	timer->paused = TRUE;
}

// <�^�C�}�[���Z�b�g>
void GameTimer_Reset(GameTimer* timer)
{
	GameTimer_Set(timer, 0);
}

// <�^�C�}�[�ĊJ>
void GameTimer_Resume(GameTimer* timer)
{
	timer->paused = FALSE;
	timer->start_time = GetNowCount() - timer->last_time;
}

// <�^�C�}�[�Z�b�g>
void GameTimer_Set(GameTimer* timer, float new_time)
{
	int new_time_in_ticks = (int)(new_time * RESOLUTION);
	timer->start_time = GetNowCount() - new_time_in_ticks;
	timer->last_time = new_time_in_ticks;
}

// <�^�C�}�[�J�E���g�_�E���J�n>
void GameTimer_Start(GameTimer* timer, float remaining)
{
	GameTimer_Resume(timer);
	GameTimer_Set(timer, -remaining);
}

// <�Q�[�����Ԑ����Ń^�C�}�[�J�E���g�_�E���J�n>
void GameTimer_SetDefault(GameTimer* timer)
{
	GameTimer_Start(timer, GAME_DURATION_SECONDS);
}

// <�^�C�}�[�c�莞��>
float GameTimer_GetTimeRemaining(GameTimer* timer)
{
	return -GameTimer_GetTime(timer);
}

// <�^�C�}�[�I������>
BOOL GameTimer_IsFinished(GameTimer* timer)
{
	return GameTimer_GetTime(timer) >= 0;
}

// <�^�C�}�[�`��>
void GameTimer_Render(GameTimer* timer, GameObject* field, GameResource* resources)
{
	float length = GetPercentValueRange(GetPercentage(GameTimer_GetTimeRemaining(timer), GAME_DURATION_SECONDS), GameObject_GetY(field, TOP), GameObject_GetY(field, BOTTOM));
	GameObject timebar = *field;
	timebar.size.x = 6;
	timebar.size.y = length;
	timebar.pos.y = field->pos.y + (field->size.y - length) / 2;

	GameObject_Render(&timebar, COLOR_WHITE);
}
