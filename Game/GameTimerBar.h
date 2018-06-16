#pragma once
#include "GameObject.h"
#include "GameResource.h"
#include "GameTimer.h"

// 構造体の宣言 ============================================================

// <ゲームタイマーバー>>
typedef struct
{
	// タイマー
	GameTimer timer;
	// フィールド
	GameObject* field;
	// 旗スプライト
	GameSprite banner;
} GameTimerBar;

// 関数の宣言 ==============================================================

// <<タイマーバー>> ----------------------------------------------------

// <タイマーバー作成>
GameTimerBar GameTimerBar_Create(GameObject* field, GameSprite sprite);

// <タイマーバー描画>
void GameTimerBar_Render(GameTimerBar* bar);
