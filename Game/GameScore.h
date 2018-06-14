#pragma once
#include "GameObject.h"
#include "GameResource.h"

// 構造体の宣言 ============================================================

// <ゲームスコア>
typedef struct
{
	int score1;	// 1Pのスコア
	int score2;	// 2Pのスコア
} GameScore;

// 関数の宣言 ==============================================================

// <<スコア>> ----------------------------------------------------

// <スコア作成>
GameScore GameScore_Create(void);

// <スコア追加>
void GameScore_Add(GameScore* score, ObjectSide side);

// <スコアリセット>
void GameScore_Clear(GameScore* score);

// <スコア描画>
void GameScore_Render(GameScore* score, GameObject* field, GameResource* resources);
