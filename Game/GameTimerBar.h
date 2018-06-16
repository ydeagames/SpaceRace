#pragma once
#include "GameObject.h"
#include "GameResource.h"
#include "GameTimer.h"

// �\���̂̐錾 ============================================================

// <�Q�[���^�C�}�[�o�[>>
typedef struct
{
	// �^�C�}�[
	GameTimer timer;
	// �t�B�[���h
	GameObject* field;
	// ���X�v���C�g
	GameSprite banner;
} GameTimerBar;

// �֐��̐錾 ==============================================================

// <<�^�C�}�[�o�[>> ----------------------------------------------------

// <�^�C�}�[�o�[�쐬>
GameTimerBar GameTimerBar_Create(GameObject* field, GameSprite sprite);

// <�^�C�}�[�o�[�`��>
void GameTimerBar_Render(GameTimerBar* bar);
