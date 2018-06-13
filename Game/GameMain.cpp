//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  SpaceRace �m�[�}���ۑ�
//!
//! @date   2018/06/13
//!
//! @author GF1 26 �R������
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "GameObject.h"
#include "GameControllers.h"
#include "GameScore.h"
#include "GameResource.h"
#include "GameMenu.h"
#include "GameScene.h"


// �萔�̒�` ==============================================================

// <�T�[�u�ҋ@> --------------------------------------------------------
#define SERVE_WAIT_TIME 2*60


// �O���[�o���ϐ��̐錾 ====================================================

// <�V�[��> ------------------------------------------------------------
GameScene g_scene;

// <�R���g���[���[> ----------------------------------------------------
GameControllers g_controllers;

// <���\�[�X> ----------------------------------------------------------
GameResource g_resources;


// �֐��̐錾 ==============================================================

// <�Q�[���̍X�V����:�V�[��> -------------------------------------------
void UpdateGameSceneDemo(void);
void UpdateGameSceneServe(void);
void UpdateGameScenePlay(void);

// <�Q�[���̕`�揈��> --------------------------------------------------
void RenderGameSceneDemo(void);
void RenderGameSceneServe(void);
void RenderGameScenePlay(void);

void UpdateGameScore(ObjectSide side);

// �֐��̒�` ==============================================================

//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeGame(void)
{
	// �V�[�����
	g_scene.game_state = STATE_DEMO;

	// �t�B�[���h
	g_scene.field = GameObject_Field_Create();

	// �{�[��
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
		{
			g_scene.bullet[i] = GameObject_Bullet_Create();
			GameObject_Bullet_SetPosXDefault(&g_scene.bullet, &g_scene.field);
			GameObject_Bullet_SetPosYDefault(&g_scene.bullet, &g_scene.field);
			GameObject_Bullet_SetVelXDefault(&g_scene.bullet);
		}
	}

	// �p�h��1
	g_scene.ship1 = GameObject_Ship_Create();
	GameObject_SetX(&g_scene.ship1, RIGHT, SCREEN_LEFT, 64);
	GameObject_Ship_SetPosYDefault(&g_scene.ship1);
	g_controllers.paddle1 = GameController_Player_Create(&g_scene.ship1, &g_scene, &g_scene.ship2, PAD_INPUT_8, PAD_INPUT_5);

	// �p�h��2
	g_scene.ship2 = GameObject_Ship_Create();
	GameObject_SetX(&g_scene.ship2, LEFT, SCREEN_RIGHT, 64);
	GameObject_Ship_SetPosYDefault(&g_scene.ship2);
	g_controllers.paddle2 = GameController_Player_Create(&g_scene.ship2, &g_scene, &g_scene.ship1, PAD_INPUT_UP, PAD_INPUT_DOWN);
	//g_controllers.paddle2 = GameController_Bot_Create(&g_scene.paddle2, &g_scene, &g_scene.paddle1);

	// ���\�[�X
	g_resources = GameResource_Create();

	// ���_
	g_scene.score = GameScore_Create();

	// �T�[�u�ҋ@
	g_scene.counter = 0;
}


//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateGame(void)
{
	switch (g_scene.game_state)
	{
	case STATE_DEMO:
		UpdateGameSceneDemo();
		break;
	case STATE_PLAY:
		UpdateGameScenePlay();
		break;
	}
}

// <�Q�[���̍X�V����:�V�[��:�f��> --------------------------------------
void UpdateGameSceneDemo(void)
{
	// �ҋ@&������
	{
		// ���͂��ꂽ��
		if (IsButtonDown(PAD_INPUT_10) && GameMenu_OnPressed(&g_menu))
		{
			// �_�����Z�b�g
			GameScore_Clear(&g_scene.score);

			// X���W����ʒ����֖߂�
			GameObject_Ball_SetPosXDefault(&g_scene.bullet, &g_scene.field);

			// �p�h���������ʒu��
			GameObject_Paddle_SetPosYDefault(&g_scene.ship1);
			GameObject_Paddle_SetPosYDefault(&g_scene.ship2);

			// �V�[�����v���C�ɕύX
			g_scene.game_state = STATE_PLAY;
			g_scene.packet = PACKET_START;
		}
	}

	// �R���g���[���[�X�V
	GameController_Update(&g_controllers.paddle1);
	GameController_Update(&g_controllers.paddle2);

	// ���W�X�V
	GameObject_UpdatePosition(&g_scene.bullet);

	// �����蔻��
	GameObject_Field_CollisionVertical(&g_scene.field, &g_scene.bullet, TRUE);
	GameObject_Field_CollisionHorizontal(&g_scene.field, &g_scene.bullet, TRUE);

	// ���j���[�X�V
	GameMenu_Update(&g_menu);
}

// <�Q�[���̍X�V����:�V�[��:�v���C> ------------------------------------
void UpdateGameScenePlay(void)
{
	// �R���g���[���[�X�V
	GameController_Update(&g_controllers.paddle1);
	GameController_Update(&g_controllers.paddle2);

	// ����
	GameController_UpdateControl(&g_controllers.paddle1);
	GameController_UpdateControl(&g_controllers.paddle2);

	// ���W�X�V
	GameObject_UpdatePosition(&g_scene.bullet);
	GameObject_UpdatePosition(&g_scene.ship1);
	GameObject_UpdatePosition(&g_scene.ship2);

	// �����蔻��
	if (GameObject_Field_CollisionVertical(&g_scene.field, &g_scene.bullet, TRUE))
		PlaySoundMem(g_resources.sound_se02, DX_PLAYTYPE_BACK);
	{
		ObjectSide side = GameObject_Field_CollisionHorizontal(&g_scene.field, &g_scene.bullet, FALSE);
		if (side)
		{
			UpdateGameScore(side);
			PlaySoundMem(g_resources.sound_se03, DX_PLAYTYPE_BACK);
		}
	}
	if (GameObject_Paddle_CollisionBall(&g_scene.ship1, &g_scene.bullet) || GameObject_Paddle_CollisionBall(&g_scene.ship2, &g_scene.bullet))
		PlaySoundMem(g_resources.sound_se01, DX_PLAYTYPE_BACK);
	GameObject_Field_CollisionVertical(&g_scene.field, &g_scene.ship1, FALSE);
	GameObject_Field_CollisionVertical(&g_scene.field, &g_scene.ship2, FALSE);
}

// <�Q�[���̍X�V����:�X�R�A���Z>
void UpdateGameScore(ObjectSide side)
{
	// ���_����
	GameScore_Add(&g_scene.score, side);

	if (GameScore_IsFinished(&g_scene.score))
	{
		GameObject_Ball_SetPosXDefault(&g_scene.bullet, &g_scene.field);
		GameObject_Ball_SetVelXDefault(&g_scene.bullet);
		GameObject_Ball_SetVelYDefault(&g_scene.bullet);

		// �V�[�����f���ɕύX
		g_scene.game_state = STATE_DEMO;
		g_scene.packet = PACKET_END;
	}
	else
	{
		// �V�[�����T�[�u�ɕύX
		g_scene.game_state = STATE_SERVE;
		g_scene.packet = PACKET_SCORE;
	}
}

//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderGame(void)
{
	switch (g_scene.game_state)
	{
	case STATE_DEMO:
		RenderGameSceneDemo();
		break;
	case STATE_PLAY:
		RenderGameScenePlay();
		break;
	}
}

// <�Q�[���̕`�揈��:�V�[��:�f��> ---------------------------------------------
void RenderGameSceneDemo(void)
{
	// <�I�u�W�F�N�g�`��>
	// �t�B�[���h�`��
	GameObject_Field_Render(&g_scene.field);
	// �{�[���`��
	GameObject_Render(&g_scene.bullet, COLOR_WHITE);
	// �X�R�A�`��
	GameScore_Render(&g_scene.score, &g_scene.field, g_resources.font_pong);
}

// <�Q�[���̕`�揈��:�V�[��:�v���C> -------------------------------------------
void RenderGameScenePlay(void)
{
	// <�I�u�W�F�N�g�`��>
	// �t�B�[���h�`��
	GameObject_Field_Render(&g_scene.field);
	// �X�R�A�`��
	GameScore_Render(&g_scene.score, &g_scene.field, g_resources.font_pong);
	// �K�C�h�`��
	if (g_scene.score.score2 - g_scene.score.score1 >= SCORE_TO_GUID)
		GameController_RenderGuide(&g_controllers.paddle1);
	if (g_scene.score.score1 - g_scene.score.score2 >= SCORE_TO_GUID)
		GameController_RenderGuide(&g_controllers.paddle2);
	// �p�h���`��
	GameObject_Render(&g_scene.ship1, COLOR_WHITE);
	GameObject_Render(&g_scene.ship2, COLOR_WHITE);
	// �{�[���`��
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
			GameObject_Render(&g_scene.bullet, COLOR_WHITE);
	}
}

//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeGame(void)
{
	GameResource_Delete(&g_resources);
}
