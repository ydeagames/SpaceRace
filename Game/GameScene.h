#pragma once
#include "GameObject.h"
#include "GameTimerBar.h"
#include "GameScore.h"
#include "GameObjectShip.h"

// 列挙型の定義 ============================================================

// <シーン状態> --------------------------------------------------------
typedef enum
{
	// デモ
	STATE_DEMO,

	// プレイ
	STATE_PLAY
} GameState;

// 定数の定義 ==============================================================

// <弾数> --------------------------------------------------------------

#define NUM_BULLET 40
#define NUM_SHIP 2

// 構造体の宣言 ============================================================

// <メニュー>
typedef struct
{
	// <シーン状態>
	int game_state;

	// <フィールド>
	GameObject field;

	// <弾>
	GameObject bullet[NUM_BULLET];

	// <シップ>
	GameObjectShip ship[NUM_SHIP];

	// <残り時間>
	GameTimerBar timerbar;

	// <得点>
	GameScore score;
} GameScene;

