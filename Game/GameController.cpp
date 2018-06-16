#include "GameController.h"

// �֐��̐錾 ==============================================================

void GameController_Default_Update(GameController* ctrl);
void GameController_Default_UpdateControl(GameController* ctrl);
void GameController_Player_UpdateControl(GameController* ctrl);

// �֐��̒�` ==============================================================

// <<�R���g���[���[>> --------------------------------------------------

// <�R���g���[���[�쐬>
GameController GameController_Create(GameObject* object, void(*updateFunc)(GameController*), void(*updateCtrlFunc)(GameController*))
{
	return { object, updateFunc, updateCtrlFunc };
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

// <<�f�t�H���g�R���g���[���[>> ----------------------------------------

// <�f�t�H���g�R���g���[���[�쐬>
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

// <<�v���C���[�R���g���[���[>> ----------------------------------------

// <�v���C���[�R���g���[���[�쐬>
GameController GameController_Player_Create(GameObject* object, int key_up, int key_down)
{
	GameController ctrl = GameController_Create(object, GameController_Default_Update, GameController_Player_UpdateControl);
	ctrl.player_key_up = key_up;
	ctrl.player_key_down = key_down;
	return ctrl;
}

// �L�[���͂Ńp�h���𑀍�
void GameController_Player_UpdateControl(GameController* ctrl)
{
	if (IsButtonDown(ctrl->player_key_up))
		ctrl->object->vel.y += -SHIP_VEL;
	if (IsButtonDown(ctrl->player_key_down))
		ctrl->object->vel.y += SHIP_VEL;
}