#include "GameTimer.h"
#include "GameUtils.h"

// 定数の定義 ==============================================================

#define RESOLUTION 1000

// 関数の定義 ==============================================================

// <<タイマー>> --------------------------------------------------

// <タイマー作成>
GameTimer GameTimer_Create(void)
{
	GameTimer timer = { -1, -1, TRUE };
	GameTimer_Reset(&timer);
	return timer;
}

// <タイマー時間>
float GameTimer_GetTime(GameTimer* timer)
{
	if (!timer->paused)
		timer->last_time = GetNowCount() - timer->start_time;
	return (float)timer->last_time / RESOLUTION;
}

// <タイマー一時停止中>
BOOL GameTimer_IsPaused(GameTimer* timer)
{
	return timer->paused;
}

// <タイマー停止>
void GameTimer_Pause(GameTimer* timer)
{
	if (!timer->paused)
		timer->last_time = GetNowCount() - timer->start_time;
	timer->paused = TRUE;
}

// <タイマーリセット>
void GameTimer_Reset(GameTimer* timer)
{
	GameTimer_Set(timer, 0);
}

// <タイマー再開>
void GameTimer_Resume(GameTimer* timer)
{
	if (timer->paused)
		timer->start_time = GetNowCount() - timer->last_time;
	timer->paused = FALSE;
}

// <タイマーセット>
void GameTimer_Set(GameTimer* timer, float new_time)
{
	int new_time_in_ticks = (int)(new_time * RESOLUTION);
	timer->start_time = GetNowCount() - new_time_in_ticks;
	timer->last_time = new_time_in_ticks;
}

// <タイマー残り時間セット>
void GameTimer_SetRemaining(GameTimer* timer, float remaining)
{
	GameTimer_Set(timer, -remaining);
}

// <ゲーム時間制限でタイマー残り時間セット>
void GameTimer_SetRemainingDefault(GameTimer* timer)
{
	GameTimer_SetRemaining(timer, GAME_DURATION_SECONDS);
}

// <タイマー残り時間>
float GameTimer_GetTimeRemaining(GameTimer* timer)
{
	return -GameTimer_GetTime(timer);
}

// <タイマー終了判定>
BOOL GameTimer_IsFinished(GameTimer* timer)
{
	return GameTimer_GetTime(timer) >= 0;
}

// <タイマー描画>
void GameTimer_Render(GameTimer* timer, GameObject* field, GameResource* resources)
{
	float length = GetPercentValueRange(GetPercentage(GameTimer_GetTimeRemaining(timer), GAME_DURATION_SECONDS), GameObject_GetY(field, TOP), GameObject_GetY(field, BOTTOM));
	GameObject timebar = *field;
	timebar.size.x = 6;
	timebar.size.y = length;
	timebar.pos.y = field->pos.y + (field->size.y - length) / 2;

	GameObject_Render(&timebar, COLOR_WHITE);
}
