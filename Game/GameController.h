#pragma once
#include "GameObject.h"

// 構造体の宣言 ============================================================

// <ゲームコントローラー>
typedef struct tag_GameController GameController;
struct tag_GameController
{
	GameObject* object;
	void(*Update)(GameController*);
	void(*UpdateControl)(GameController*);

	// 継承ができないので仕方なくPlayer用の変数
	int player_key_up;
	int player_key_down;
};

// 関数の宣言 ==============================================================

// <<コントローラー>> --------------------------------------------------

// <コントローラー作成>
GameController GameController_Create(GameObject* object, void(*updateFunc)(GameController*), void(*updateCtrlFunc)(GameController*));

// <コントローラー更新>
void GameController_Update(GameController* ctrl);

// <コントローラー操作更新>
void GameController_UpdateControl(GameController* ctrl);

// <<デフォルトコントローラー>> ----------------------------------------

// <デフォルトコントローラー作成>
GameController GameController_Default_Create(GameObject* object);

// <<プレイヤーコントローラー>> ----------------------------------------

// <プレイヤーコントローラー作成>
GameController GameController_Player_Create(GameObject* object, int key_up, int key_down);
