#pragma once
#include "GameScene.h"
#include "GameResource.h"

// �\���̂̐錾 ============================================================

// <�Q�[���T�E���h>
typedef struct
{
	// <�t�B�[���h>
	GameScene* scene;

	// <�`�[��>
	ObjectSide team;

	// <�v���C���t���O>
	BOOL playing;

	// <�T�E���h>
	HSND sound;

	// �T�E���h�̃��Y��
	int interval;
} GameSoundShip;

// �萔�̒�` ==============================================================

// <�T�E���h> ----------------------------------------------------------

#define SOUND_PITCH_MAX ((int) 44100*2.6f)		// �V�b�v�̉��s�b�`�ő�
#define SOUND_PITCH_MIN ((int) 44100*1.0f)		// �V�b�v�̉��s�b�`�ŏ�
#define SOUND_SHIP1_INTERVAL 67					// �V�b�v1�̉����Y��
#define SOUND_SHIP2_INTERVAL (67*2)				// �V�b�v2�̉����Y��

// �֐��̐錾 ==============================================================

// <<�T�E���h>> --------------------------------------------------

// <�T�E���h�쐬>
GameSoundShip GameSoundShip_Create(GameScene* scene, ObjectSide team, HSND sound, int interval);

// <�T�E���h�X�V>
void GameSoundShip_Update(GameSoundShip* sound);

// <�T�E���h�Đ�>
void GameSoundShip_Start(GameSoundShip* sound);

// <�T�E���h��~>
void GameSoundShip_Stop(GameSoundShip* sound);
