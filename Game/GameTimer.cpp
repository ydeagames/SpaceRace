#include "GameTimer.h"
#include "GameUtils.h"

// 定数の定義 ==============================================================

#define RESOLUTION 1000

// 関数の定義 ==============================================================

// <<タイマー>> --------------------------------------------------

// <タイマー作成>
GameTimer GameTimer_Create(void)
{
	return { -1, -1, TRUE };
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
	timer->paused = FALSE;
	timer->start_time = GetNowCount() - timer->last_time;
}

// <タイマーセット>
void GameTimer_Set(GameTimer* timer, float new_time)
{
	int new_time_in_ticks = (int)(new_time * RESOLUTION);
	timer->start_time = GetNowCount() - new_time_in_ticks;
	timer->last_time = new_time_in_ticks;
}

// <タイマーカウントダウン開始>
void GameTimer_Start(GameTimer* timer, float remaining)
{
	GameTimer_Resume(timer);
	GameTimer_Set(timer, -remaining);
}

// <ゲーム時間制限でタイマーカウントダウン開始>
void GameTimer_SetDefault(GameTimer* timer)
{
	GameTimer_Start(timer, GAME_DURATION_SECONDS);
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
