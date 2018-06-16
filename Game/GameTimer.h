#pragma once
#include "GameObject.h"
#include "GameResource.h"

// 構造体の宣言 ============================================================

// <ゲームタイマー>>
typedef struct
{
	int start_time;	// 開始時間
	int last_time;	// 終了時間
	BOOL paused;	// 一時停止
} GameTimer;

// 関数の宣言 ==============================================================

// <<タイマー>> --------------------------------------------------

// <タイマー作成>
GameTimer GameTimer_Create(void);

// <タイマー時間>
float GameTimer_GetTime(GameTimer* timer);

// <タイマー一時停止中>
BOOL GameTimer_IsPaused(GameTimer* timer);

// <タイマー停止>
void GameTimer_Pause(GameTimer* timer);

// <タイマーリセット>
void GameTimer_Reset(GameTimer* timer);

// <タイマー再開>
void GameTimer_Resume(GameTimer* timer);

// <タイマーセット>
void GameTimer_Set(GameTimer* timer, float new_time);


// <タイマー残り時間セット>
void GameTimer_SetRemaining(GameTimer* timer, float remaining);

// <ゲーム時間制限でタイマー残り時間セット>
void GameTimer_SetRemainingDefault(GameTimer* timer);

// <タイマー残り時間>
float GameTimer_GetTimeRemaining(GameTimer* timer);

// <タイマー終了判定>
BOOL GameTimer_IsFinished(GameTimer* timer);

// <タイマー描画>
void GameTimer_Render(GameTimer* timer, GameObject* field, GameResource* resources);
