#pragma once
#include "GameObject.h"
#include "GameScore.h"

// �񋓌^�̒�` ============================================================

// <�V�[�����> --------------------------------------------------------
enum GameState
{
	// �f��
	STATE_DEMO,

	// �v���C
	STATE_PLAY
};

// �萔�̒�` ==============================================================

// <�e��> --------------------------------------------------------------

#define NUM_BULLET 30

// �\���̂̐錾 ============================================================

// <���j���[>
typedef struct
{
	// <�V�[�����>
	int game_state;

	// <�t�B�[���h>
	GameObject field;

	// <�e>
	GameObject bullet[NUM_BULLET];

	// <�V�b�v1>
	GameObject ship1;

	// <�V�b�v2>
	GameObject ship2;

	// <���_>
	GameScore score;

	// <�T�[�u�ҋ@>
	int counter;
} GameScene;

