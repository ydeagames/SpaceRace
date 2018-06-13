#include "GameController.h"

// �֐��̐錾 ==============================================================

void GameController_Player_Update(GameController* ctrl);
void GameController_Player_UpdateControl(GameController* ctrl);

// �֐��̒�` ==============================================================

// <<�R���g���[���[>> --------------------------------------------------

// <�R���g���[���[�쐬>
GameController GameController_Create(GameObject* object, void(*updateFunc)(GameController*), void(*updateCtrlFunc)(GameController*), GameScene* scene, GameObject* enemy)
{
	return { object, updateFunc, updateCtrlFunc, scene };
}

// <�R���g���[���[�X�V>
void GameController_Update(GameController* ctrl)
{
	ctrl->Update(ctrl);
}

// <�R���g���[���[����X�V>
void GameController_UpdateControl(GameController* ctrl)
{
	ctrl->UpdateControl(ctrl);
}

// <<�v���C���[�R���g���[���[>> ----------------------------------------

// <�v���C���[�R���g���[���[�쐬>
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

// �L�[���͂Ńp�h���𑀍�
void GameController_Player_UpdateControl(GameController* ctrl)
{
	ctrl->object->vel.y = 0.f;
	if (IsButtonDown(ctrl->player_key_up))
		ctrl->object->vel.y += -SHIP_VEL;
	if (IsButtonDown(ctrl->player_key_down))
		ctrl->object->vel.y += SHIP_VEL;
}