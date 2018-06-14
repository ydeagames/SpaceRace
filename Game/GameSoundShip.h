#pragma once
#include "GameObject.h"
#include "GameResource.h"

// �\���̂̐錾 ============================================================

// <�Q�[���T�E���h>
typedef struct
{
	// <�V�[��>
	GameObject* field;

	// <�V�b�v>
	GameObject* ship;

	// <�v���C���t���O>
	BOOL playing;

	// <�T�E���h>
	HSND sound;

	// �T�E���h�̃��Y��
	int interval;
} GameSoundShip;

// �萔�̒�` ==============================================================

// <�T�E���h> ----------------------------------------------------------

#define SOUND_PITCH_MAX ((int) 44100*2.6f)
#define SOUND_PITCH_MIN ((int) 44100*1.0f)
#define SOUND_SHIP1_INTERVAL 67
#define SOUND_SHIP2_INTERVAL (67*2)

// �֐��̐錾 ==============================================================

// <<�T�E���h>> --------------------------------------------------

// <�T�E���h�쐬>
GameSoundShip GameSoundShip_Create(GameObject* field, GameObject* ship, HSND sound, int interval);

// <�T�E���h�X�V>
void GameSoundShip_Update(GameSoundShip* sound);

// <�T�E���h�Đ�>
void GameSoundShip_Start(GameSoundShip* sound);

// <�T�E���h��~>
void GameSoundShip_Stop(GameSoundShip* sound);
