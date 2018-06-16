#pragma once
#include "GameObject.h"

// �\���̂̐錾 ============================================================

// <�Q�[���R���g���[���[>
typedef struct tag_GameController GameController;
struct tag_GameController
{
	GameObject* object;							// �R���g���[���I�u�W�F�N�g
	void(*Update)(GameController*);				// �R���g���[���X�V�֐�
	void(*UpdateControl)(GameController*);		// �R���g���[������֐�

	// �p�����ł��Ȃ��̂Ŏd���Ȃ�Player�p�̕ϐ�
	int player_key_up;							// ���L�[
	int player_key_down;						// ���L�[
};

// �֐��̐錾 ==============================================================

// <<�R���g���[���[>> --------------------------------------------------

// <�R���g���[���[�쐬>
GameController GameController_Create(GameObject* object, void(*updateFunc)(GameController*), void(*updateCtrlFunc)(GameController*));

// <�R���g���[���[�X�V>
void GameController_Update(GameController* ctrl);

// <�R���g���[���[����X�V>
void GameController_UpdateControl(GameController* ctrl);

// <<�f�t�H���g�R���g���[���[>> ----------------------------------------

// <�f�t�H���g�R���g���[���[�쐬>
GameController GameController_Default_Create(GameObject* object);

// <<�v���C���[�R���g���[���[>> ----------------------------------------

// <�v���C���[�R���g���[���[�쐬>
GameController GameController_Player_Create(GameObject* object, int key_up, int key_down);
