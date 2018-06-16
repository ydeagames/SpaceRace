#include "GameController.h"

// 関数の宣言 ==============================================================

void GameController_Default_Update(GameController* ctrl);
void GameController_Default_UpdateControl(GameController* ctrl);
void GameController_Player_UpdateControl(GameController* ctrl);

// 関数の定義 ==============================================================

// <<コントローラー>> --------------------------------------------------

// <コントローラー作成>
GameController GameController_Create(GameObject* object, void(*updateFunc)(GameController*), void(*updateCtrlFunc)(GameController*))
{
	return { object, updateFunc, updateCtrlFunc };
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

// <<デフォルトコントローラー>> ----------------------------------------

// <デフォルトコントローラー作成>
GameController GameController_Default_Create(GameObject* object)
{
	return GameController_Create(object, GameController_Default_Update, GameController_Default_UpdateControl);
}

void GameController_Default_Update(GameController* ctrl)
{
	ctrl->object->vel.y = 0.f;
}

void GameController_Default_UpdateControl(GameController* ctrl)
{
}

// <<プレイヤーコントローラー>> ----------------------------------------

// <プレイヤーコントローラー作成>
GameController GameController_Player_Create(GameObject* object, int key_up, int key_down)
{
	GameController ctrl = GameController_Create(object, GameController_Default_Update, GameController_Player_UpdateControl);
	ctrl.player_key_up = key_up;
	ctrl.player_key_down = key_down;
	return ctrl;
}

// キー入力でパドルを操作
void GameController_Player_UpdateControl(GameController* ctrl)
{
	if (IsButtonDown(ctrl->player_key_up))
		ctrl->object->vel.y += -SHIP_VEL;
	if (IsButtonDown(ctrl->player_key_down))
		ctrl->object->vel.y += SHIP_VEL;
}