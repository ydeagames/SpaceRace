#pragma once
#include "GameObject.h"
#include "GameController.h"
#include "GameScore.h"

// 構造体の宣言 ============================================================

// <シップオブジェクト>
typedef struct
{
	// <フィールド>
	GameObject* field;

	// <シップ>
	GameObject ship;

	// <コントローラー>
	GameController controller;

	// <リスポーンカウンター>
	int counter;

	// <チーム>
	ObjectSide team;
} GameObjectShip;

// 関数の宣言 ==============================================================

// <<シップオブジェクト>> ----------------------------------------------

// <シップオブジェクト作成>
GameObjectShip GameObjectShip_Create(ObjectSide team, GameObject* field, float offset);

// <シップオブジェクト初期化>
void GameObjectShip_Reset(GameObjectShip* ship);

// <シップオブジェクト死亡>
void GameObjectShip_Kill(GameObjectShip* ship);

// <シップオブジェクト更新>
void GameObjectShip_Update(GameObjectShip* ship);

// <シップオブジェクト有効>
BOOL GameObjectShip_IsAvailable(GameObjectShip* ship);

// <シップオブジェクト当たり判定>
BOOL GameObjectShip_CollisionScore(GameObjectShip* ship, GameScore* score);

// <シップオブジェクト描画>
void GameObjectShip_Render(GameObjectShip* ship, GameObject* field);
