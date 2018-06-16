#pragma once
#include "GameObject.h"
#include "GameTimer.h"
#include "GameScore.h"
#include "GameObjectShip.h"

// 列挙型の定義 ============================================================

// <シーン状態> --------------------------------------------------------
enum GameState
{
	// デモ
	STATE_DEMO,

	// プレイ
	STATE_PLAY
};

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

	// <得点>
	GameTimer timer;

	// <得点>
	GameScore score;
} GameScene;

