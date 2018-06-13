#include "GameController.h"

// 関数の宣言 ==============================================================

void GameController_Player_Update(GameController* ctrl);
void GameController_Player_UpdateControl(GameController* ctrl);

// 関数の定義 ==============================================================

// <<コントローラー>> --------------------------------------------------

// <コントローラー作成>
GameController GameController_Create(GameObject* object, void(*updateFunc)(GameController*), void(*updateCtrlFunc)(GameController*), GameScene* scene, GameObject* enemy)
{
	return { object, updateFunc, updateCtrlFunc, scene };
}

// <コントローラー更新>
void GameController_Update(GameController* ctrl)
{
	ctrl->Update(ctrl);
}

// <コントローラー操作更新>
void GameController_UpdateControl(GameController* ctrl)
{
	ctrl->UpdateControl(ctrl);
}

// <<プレイヤーコントローラー>> ----------------------------------------

// <プレイヤーコントローラー作成>
GameController GameController_Player_Create(GameObject* object, GameScene* scene, GameObject* enemy, int key_up, int key_down)
{
	GameController ctrl = GameController_Create(object, GameController_Player_Update, GameController_Player_UpdateControl, scene, enemy);
	ctrl.player_key_up = key_up;
	ctrl.player_key_down = key_down;
	return ctrl;
}

void GameController_Player_Update(GameController* ctrl)
{
}

// キー入力でパドルを操作
void GameController_Player_UpdateControl(GameController* ctrl)
{
	ctrl->object->vel.y = 0.f;
	if (IsButtonDown(ctrl->player_key_up))
		ctrl->object->vel.y += -SHIP_VEL;
	if (IsButtonDown(ctrl->player_key_down))
		ctrl->object->vel.y += SHIP_VEL;
}