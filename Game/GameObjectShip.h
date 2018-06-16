#pragma once
#include "GameObject.h"
#include "GameController.h"
#include "GameScore.h"

// �\���̂̐錾 ============================================================

// <�V�b�v�I�u�W�F�N�g>
typedef struct
{
	// <�t�B�[���h>
	GameObject* field;

	// <�V�b�v>
	GameObject ship;

	// <�R���g���[���[>
	GameController controller;

	// <���X�|�[���J�E���^�[>
	int counter;

	// <�`�[��>
	ObjectSide team;
} GameObjectShip;

// �֐��̐錾 ==============================================================

// <<�V�b�v�I�u�W�F�N�g>> ----------------------------------------------

// <�V�b�v�I�u�W�F�N�g�쐬>
GameObjectShip GameObjectShip_Create(ObjectSide team, GameObject* field, float offset);

// <�V�b�v�I�u�W�F�N�g������>
void GameObjectShip_Reset(GameObjectShip* ship);

// <�V�b�v�I�u�W�F�N�g���S>
void GameObjectShip_Kill(GameObjectShip* ship);

// <�V�b�v�I�u�W�F�N�g�X�V>
void GameObjectShip_Update(GameObjectShip* ship);

// <�V�b�v�I�u�W�F�N�g�L��>
BOOL GameObjectShip_IsAvailable(GameObjectShip* ship);

// <�V�b�v�I�u�W�F�N�g�����蔻��>
BOOL GameObjectShip_CollisionScore(GameObjectShip* ship, GameScore* score);

// <�V�b�v�I�u�W�F�N�g�`��>
void GameObjectShip_Render(GameObjectShip* ship, GameObject* field);
