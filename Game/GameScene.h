#pragma once
#include "GameObject.h"
#include "GameTimer.h"
#include "GameScore.h"
#include "GameObjectShip.h"

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

#define NUM_BULLET 40
#define NUM_SHIP 2

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

	// <�V�b�v>
	GameObjectShip ship[NUM_SHIP];

	// <���_>
	GameTimer timer;

	// <���_>
	GameScore score;
} GameScene;

