#pragma once
#include "GameScene.h"

// �\���̂̐錾 ============================================================

// <�Q�[���R���g���[���[>
typedef struct tag_GameController GameController;
struct tag_GameController
{
	GameObject* object;
	void(*Update)(GameController*);
	void(*UpdateControl)(GameController*);

	GameScene* scene;

	// �p�����ł��Ȃ��̂Ŏd���Ȃ�Player�p�̕ϐ�
	int player_key_up;
	int player_key_down;
};

// �֐��̐錾 ==============================================================

// <<�R���g���[���[>> --------------------------------------------------

// <�R���g���[���[�쐬>
GameController GameController_Create(GameObject* object, void(*updateFunc)(GameController*), void(*updateCtrlFunc)(GameController*), GameScene* scene);

// <�R���g���[���[�X�V>
void GameController_Update(GameController* ctrl);

// <�R���g���[���[����X�V>
void GameController_UpdateControl(GameController* ctrl);

// <<�v���C���[�R���g���[���[>> ----------------------------------------

// <�v���C���[�R���g���[���[�쐬>
GameController GameController_Player_Create(GameObject* object, GameScene* scene, int key_up, int key_down);
