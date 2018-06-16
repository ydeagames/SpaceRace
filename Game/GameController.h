#pragma once
#include "GameScene.h"

// 構造体の宣言 ============================================================

// <ゲームコントローラー>
typedef struct tag_GameController GameController;
struct tag_GameController
{
	GameObject* object;
	void(*Update)(GameController*);
	void(*UpdateControl)(GameController*);

	GameScene* scene;

	// 継承ができないので仕方なくPlayer用の変数
	int player_key_up;
	int player_key_down;
};

// 関数の宣言 ==============================================================

// <<コントローラー>> --------------------------------------------------

// <コントローラー作成>
GameController GameController_Create(GameObject* object, void(*updateFunc)(GameController*), void(*updateCtrlFunc)(GameController*), GameScene* scene);

// <コントローラー更新>
void GameController_Update(GameController* ctrl);

// <コントローラー操作更新>
void GameController_UpdateControl(GameController* ctrl);

// <<プレイヤーコントローラー>> ----------------------------------------

// <プレイヤーコントローラー作成>
GameController GameController_Player_Create(GameObject* object, GameScene* scene, int key_up, int key_down);
