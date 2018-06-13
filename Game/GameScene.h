#pragma once
#include "GameObject.h"
#include "GameScore.h"

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

#define NUM_BULLET 30

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

	// <シップ1>
	GameObject ship1;

	// <シップ2>
	GameObject ship2;

	// <得点>
	GameScore score;

	// <サーブ待機>
	int counter;
} GameScene;

