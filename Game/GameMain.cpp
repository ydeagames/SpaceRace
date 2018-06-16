//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  SpaceRace �m�[�}���ۑ�
//!
//! @date   2018/06/17
//!
//! @author GF1 26 �R������
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "GameResource.h"
#include "GameSoundShip.h"
#include "GameScene.h"


// �O���[�o���ϐ��̐錾 ====================================================

// <���\�[�X> ----------------------------------------------------------
GameResource g_resources;

// <�T�E���h> ----------------------------------------------------------
GameSoundShip g_ship1_sound;
GameSoundShip g_ship2_sound;

// <�V�[��> ------------------------------------------------------------
GameScene g_scene;


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
	// ���\�[�X
	g_resources = GameResource_Create();

	// �V�b�v�T�E���h
	g_ship1_sound = GameSoundShip_Create(&g_scene, LEFT, g_resources.sound_ship1, SOUND_SHIP1_INTERVAL);
	g_ship2_sound = GameSoundShip_Create(&g_scene, RIGHT, g_resources.sound_ship2, SOUND_SHIP2_INTERVAL);

	// �V�[���Z�b�g�A�b�v
	{
		// �V�[�����
		g_scene.game_state = STATE_DEMO;

		// �t�B�[���h
		g_scene.field = GameObject_Field_Create();

		// �e
		{
			// �e�X�v���C�g
			GameSprite sprite = GameSprite_Create(GameTexture_Create(g_resources.texture_spacerace, Vec2_Create(139, 1), Vec2_Create(2, 6)));
			sprite.angle = ToRadians(-90);

			{
				int i;
				for (i = 0; i < NUM_BULLET; i++)
				{
					g_scene.bullet[i] = GameObject_Bullet_Create();
					g_scene.bullet[i].sprite = sprite;
					GameObject_Bullet_SetPosXDefault(&g_scene.bullet[i], &g_scene.field);
					GameObject_Bullet_SetPosYDefault(&g_scene.bullet[i], &g_scene.field);
					GameObject_Bullet_SetVelXDefault(&g_scene.bullet[i]);
				}
			}
		}

		// �V�b�v
		{
			// �V�b�v�X�v���C�g
			GameSprite sprite = GameSprite_Create(GameTexture_Create(g_resources.texture_spacerace, Vec2_Create(16, 13), Vec2_Create(32, 38)));

			// �V�b�v1 [��:W, ��:S]
			{
				g_scene.ship[0] = GameObjectShip_Create(LEFT, &g_scene.field, 80);
				g_scene.ship[0].ship.sprite = sprite;
				g_scene.ship[0].controller = GameController_Player_Create(&g_scene.ship[0].ship, PAD_INPUT_8, PAD_INPUT_5);
			}

			// �V�b�v2 [��:��, ��:��]
			{
				GameObjectShip* ship = &g_scene.ship[1];
				*ship = GameObjectShip_Create(RIGHT, &g_scene.field, 80);
				ship->ship.sprite = sprite;
				ship->controller = GameController_Player_Create(&ship->ship, PAD_INPUT_UP, PAD_INPUT_DOWN);
			}

			/*
			// �V�b�v3 [��:A, ��:Z] (�ǉ��V�b�v) ��GameScene.h->NUM_SHIP��ύX����K�v����
			{
				GameObjectShip* ship = &g_scene.ship[2];
				*ship = GameObjectShip_Create(LEFT, &g_scene.field, 120);
				ship->controller = GameController_Player_Create(&ship->ship, PAD_INPUT_4, PAD_INPUT_1);
			}
			/**/
		}

		// �^�C�}�[
		{
			// ���X�v���C�g
			GameSprite sprite = GameSprite_Create(GameTexture_Create(g_resources.texture_spacerace, Vec2_Create(143, 10), Vec2_Create(16, 26)));
			sprite.scale = 1.25f;
			sprite.texture.center.x = 1;
			sprite.texture.center.y = sprite.texture.size.y;

			g_scene.timerbar = GameTimerBar_Create(&g_scene.field, sprite);
			GameTimer_SetRemainingDefault(&g_scene.timerbar.timer);
		}

		// ���_
		g_scene.score = GameScore_Create();
	}
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
	// �Q�[���V�[��
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
			GameTimer_Resume(&g_scene.timerbar.timer);

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
			if (GameObjectShip_IsAlive(&g_scene.ship[i]))
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
			// �t�B�[���h�̍��E�Œe���[�v
			GameObject_Field_CollisionHorizontal(&g_scene.field, &g_scene.bullet[i], CONNECTION_LOOP, EDGESIDE_OUTER);

			{
				int j;
				for (j = 0; j < NUM_SHIP; j++)
					// �V�b�v�Ƃ���������
					if (GameObject_IsHit(&g_scene.ship[j].ship, &g_scene.bullet[i]))
					{
						// �V�b�v���S
						GameObjectShip_Kill(&g_scene.ship[j]);
						// �V�b�v���S��
						PlaySoundMem(g_resources.sound_dead, DX_PLAYTYPE_BACK);
					}
			}
		}
	}
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			// ��܂ōs������X�R�A���Z
			GameObjectShip_CollisionScore(&g_scene.ship[i], &g_scene.score);
	}

	// �I������
	if (GameTimer_IsFinished(&g_scene.timerbar.timer))
	{
		// �^�C�}�[��~������
		GameTimer_Pause(&g_scene.timerbar.timer);
		GameTimer_SetRemainingDefault(&g_scene.timerbar.timer);

		// �T�E���h��~
		GameSoundShip_Stop(&g_ship1_sound);
		GameSoundShip_Stop(&g_ship2_sound);

		// �V�[�����f���ɕύX
		g_scene.game_state = STATE_DEMO;
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
	// �Q�[���V�[��
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
			GameObject_Render(&g_scene.bullet[i]);
	}
	// �^�C���`��
	GameTimerBar_Render(&g_scene.timerbar);
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
	GameTimerBar_Render(&g_scene.timerbar);
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
			GameObject_Render(&g_scene.bullet[i]);
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
