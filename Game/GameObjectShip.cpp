#include "GameObjectShip.h"

// �萔�̒�` ==============================================================

// <���X�|�[���ҋ@>
#define SHIP_WAIT_TIME 60

// �֐��̒�` ==============================================================

// <<�V�b�v�I�u�W�F�N�g>> ----------------------------------------------

// <�V�b�v�I�u�W�F�N�g�쐬>
GameObjectShip GameObjectShip_Create(ObjectSide team, GameObject* field, float offset)
{
	GameObject shipobj = GameObject_Ship_Create();
	GameObjectShip ship = { field, shipobj, GameController_Default_Create(&shipobj), 0, team };
	ship.ship.pos.x = GameObject_OffsetX(&ship.ship, ship.team, GameObject_GetX(ship.field, CENTER_X), offset);
	GameObjectShip_Reset(&ship);
	return ship;
}

// <�V�b�v�I�u�W�F�N�g������>
void GameObjectShip_Reset(GameObjectShip* ship)
{
	GameObject_Ship_SetPosYDefault(&ship->ship, ship->field);
	ship->counter = 0;
}

// <�V�b�v�I�u�W�F�N�g���S>
void GameObjectShip_Kill(GameObjectShip* ship)
{
	GameObjectShip_Reset(ship);
	ship->counter = SHIP_WAIT_TIME;
}

// <�V�b�v�I�u�W�F�N�g�X�V>
void GameObjectShip_Update(GameObjectShip* ship)
{
	if (ship->counter > 0)
		ship->counter--;
}

// <�V�b�v�I�u�W�F�N�g�����Ă���>
BOOL GameObjectShip_IsAlive(GameObjectShip* ship)
{
	return ship->counter <= 0;
}

// <�V�b�v�I�u�W�F�N�g�����蔻��>
BOOL GameObjectShip_CollisionScore(GameObjectShip* ship, GameScore* score)
{
	// �O���̏�ɂ������Ă�����
	if (GameObject_Field_CollisionVertical(ship->field, &ship->ship, CONNECTION_NONE, EDGESIDE_OUTER) == TOP)
	{
		// �����̃t�B�[���h�Ń��[�v
		GameObject_Field_CollisionVertical(ship->field, &ship->ship, CONNECTION_LOOP, EDGESIDE_CENTER);
		// �X�R�A�����Z
		GameScore_Add(score, ship->team);

		return TRUE;
	}
	// �����̉��ɓ������Ă�����
	else if (GameObject_Field_CollisionVertical(ship->field, &ship->ship, CONNECTION_NONE, EDGESIDE_INNER) == BOTTOM)
		// �����̃t�B�[���h�Ńu���b�N
		GameObject_Field_CollisionVertical(ship->field, &ship->ship, CONNECTION_BARRIER, EDGESIDE_INNER);

	return FALSE;
}

// <�V�b�v�I�u�W�F�N�g�`��>
void GameObjectShip_Render(GameObjectShip* ship, GameObject* field)
{
	// �����Ă�����
	if (GameObjectShip_IsAlive(ship))
	{
		// ��[�̔����ɃV�b�v���߂荞�񂾂Ƃ������甼���o�Ă���悤�ɕ\��
		// �����̏�ɓ������Ă�����
		if (GameObject_Field_CollisionVertical(field, &ship->ship, CONNECTION_NONE, EDGESIDE_INNER) == TOP)
		{
			// 1���[�v���������̃V�b�v�̕`��
			GameObject obj = ship->ship;
			obj.pos.y -= obj.size.y;
			GameObject_Field_CollisionVertical(field, &obj, CONNECTION_LOOP, EDGESIDE_CENTER);
			obj.pos.y += obj.size.y;
			GameObject_Render(&obj);
		}
		// �V�b�v�`��
		GameObject_Render(&ship->ship);
	}
}
