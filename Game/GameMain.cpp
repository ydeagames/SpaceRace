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
#include "GameScore.h"
#include "GameResource.h"
#include "GameScene.h"
#include "GameSoundShip.h"


// �O���[�o���ϐ��̐錾 ====================================================

// <�V�[��> ------------------------------------------------------------
GameScene g_scene;

// <���\�[�X> ----------------------------------------------------------
GameResource g_resources;

// <�T�E���h> ----------------------------------------------------------
GameSoundShip g_ship1_sound;
GameSoundShip g_ship2_sound;


// �֐��̐錾 ==============================================================

// <�Q�[���̍X�V����:�V�[��> -------------------------------------------
void UpdateGameSceneDemo(void);
void UpdateGameScenePlay(void);

// <�Q�[���̕`�揈��> --------------------------------------------------
void RenderGameSceneDemo(void);
void RenderGameScenePlay(void);


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

	// �e
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
		{
			g_scene.bullet[i] = GameObject_Bullet_Create();
			GameObject_Bullet_SetPosXDefault(&g_scene.bullet[i], &g_scene.field);
			GameObject_Bullet_SetPosYDefault(&g_scene.bullet[i], &g_scene.field);
			GameObject_Bullet_SetVelXDefault(&g_scene.bullet[i]);
		}
	}

	// �V�b�v1
	{
		GameObjectShip* ship = &g_scene.ship[0];
		*ship = GameObjectShip_Create(LEFT, &g_scene.field, 80);
		ship->controller = GameController_Player_Create(&ship->ship, PAD_INPUT_8, PAD_INPUT_5);
	}

	// �V�b�v2
	{
		GameObjectShip* ship = &g_scene.ship[1];
		*ship = GameObjectShip_Create(RIGHT, &g_scene.field, 80);
		ship->controller = GameController_Player_Create(&ship->ship, PAD_INPUT_UP, PAD_INPUT_DOWN);
	}

	// ���\�[�X
	g_resources = GameResource_Create();

	// �V�b�v�T�E���h
	g_ship1_sound = GameSoundShip_Create(&g_scene, LEFT, g_resources.sound_se02, SOUND_SHIP1_INTERVAL);
	g_ship2_sound = GameSoundShip_Create(&g_scene, RIGHT, g_resources.sound_se03, SOUND_SHIP2_INTERVAL);

	// �^�C�}�[
	g_scene.timer = GameTimer_Create();

	// ���_
	g_scene.score = GameScore_Create();
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
		if (IsButtonDown(PAD_INPUT_10))
		{
			// �^�C�}�[���J�n
			GameTimer_SetDefault(&g_scene.timer);

			// �_�����Z�b�g
			GameScore_Clear(&g_scene.score);

			// �V�b�v�������ʒu��
			{
				int i;
				for (i = 0; i < NUM_SHIP; i++)
					GameObjectShip_Reset(&g_scene.ship[i]);
			}

			// �T�E���h�Đ�
			GameSoundShip_Start(&g_ship1_sound);
			GameSoundShip_Start(&g_ship2_sound);

			// �V�[�����v���C�ɕύX
			g_scene.game_state = STATE_PLAY;
		}
	}

	// �R���g���[���[�X�V
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			GameController_Update(&g_scene.ship[i].controller);
	}

	// ���W�X�V
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
			GameObject_UpdatePosition(&g_scene.bullet[i]);
	}

	// �����蔻��
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
			GameObject_Field_CollisionHorizontal(&g_scene.field, &g_scene.bullet[i], CONNECTION_LOOP, EDGESIDE_OUTER);
	}
}

// <�Q�[���̍X�V����:�V�[��:�v���C> ------------------------------------
void UpdateGameScenePlay(void)
{
	// �R���g���[���[�X�V
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			GameController_Update(&g_scene.ship[i].controller);
	}

	// �V�b�v�X�V
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			GameObjectShip_Update(&g_scene.ship[i]);
	}

	// ����
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			if (GameObjectShip_IsAvailable(&g_scene.ship[i]))
				GameController_UpdateControl(&g_scene.ship[i].controller);
	}

	// ���W�X�V
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
			GameObject_UpdatePosition(&g_scene.bullet[i]);
	}
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			GameObject_UpdatePosition(&g_scene.ship[i].ship);
	}

	// �T�E���h�X�V
	GameSoundShip_Update(&g_ship1_sound);
	GameSoundShip_Update(&g_ship2_sound);

	// �����蔻��
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
		{
			GameObject_Field_CollisionHorizontal(&g_scene.field, &g_scene.bullet[i], CONNECTION_LOOP, EDGESIDE_OUTER);

			{
				int j;
				for (j = 0; j < NUM_SHIP; j++)
					if (GameObject_IsHit(&g_scene.ship[j].ship, &g_scene.bullet[i]))
					{
						GameObjectShip_Kill(&g_scene.ship[j]);
						PlaySoundMem(g_resources.sound_se01, DX_PLAYTYPE_BACK);
					}
			}
		}
	}
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			GameObjectShip_CollisionScore(&g_scene.ship[i], &g_scene.score);
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
	// �e�`��
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
			GameObject_Render(&g_scene.bullet[i], COLOR_WHITE);
	}
	// �X�R�A�`��
	GameScore_Render(&g_scene.score, &g_scene.field, &g_resources);
}

// <�Q�[���̕`�揈��:�V�[��:�v���C> -------------------------------------------
void RenderGameScenePlay(void)
{
	// <�I�u�W�F�N�g�`��>
	// �t�B�[���h�`��
	GameObject_Field_Render(&g_scene.field);
	// �^�C���`��
	GameTimer_Render(&g_scene.timer, &g_scene.field, &g_resources);
	// �X�R�A�`��
	GameScore_Render(&g_scene.score, &g_scene.field, &g_resources);
	// �V�b�v�`��
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			GameObjectShip_Render(&g_scene.ship[i], &g_scene.field);
	}
	// �e�`��
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
			GameObject_Render(&g_scene.bullet[i], COLOR_WHITE);
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
