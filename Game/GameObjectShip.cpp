#include "GameObjectShip.h"

// �萔�̒�` ==============================================================

// <���X�|�[���ҋ@> ----------------------------------------------------
#define SHIP_WAIT_TIME 60

// �֐��̒�` ==============================================================

// <<�V�b�v�I�u�W�F�N�g>> ----------------------------------------------

// <�V�b�v�I�u�W�F�N�g�쐬>
GameObjectShip GameObjectShip_Create(ObjectSide team, GameObject* field, float offset)
{
	GameObjectShip ship = { field, GameObject_Ship_Create(), 0, team };

	ship.ship.pos.x = GameObject_OffsetX(&ship.ship, ship.team, GameObject_GetX(ship.field, CENTER_X), 80);
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

// <�V�b�v�I�u�W�F�N�g�L��>
BOOL GameObjectShip_IsAvailable(GameObjectShip* ship)
{
	return ship->counter <= 0;
}

// <�V�b�v�I�u�W�F�N�g�����蔻��>
BOOL GameObjectShip_CollisionScore(GameObjectShip* ship, GameScore* score)
{
	if (GameObject_Field_CollisionVertical(ship->field, &ship->ship, CONNECTION_NONE, EDGESIDE_OUTER) == TOP)
	{
		GameObject_Field_CollisionVertical(ship->field, &ship->ship, CONNECTION_LOOP, EDGESIDE_CENTER);
		GameScore_Add(score, ship->team);

		return TRUE;
	}
	else if (GameObject_Field_CollisionVertical(ship->field, &ship->ship, CONNECTION_NONE, EDGESIDE_INNER) == BOTTOM)
		GameObject_Field_CollisionVertical(ship->field, &ship->ship, CONNECTION_BARRIER, EDGESIDE_INNER);

	return FALSE;
}

// <�V�b�v�I�u�W�F�N�g�`��>
void GameObjectShip_Render(GameObjectShip* ship, GameObject* field)
{
	if (GameObjectShip_IsAvailable(ship))
	{
		if (GameObject_Field_CollisionVertical(field, &ship->ship, CONNECTION_NONE, EDGESIDE_INNER) == TOP)
		{
			GameObject lower = ship->ship;
			lower.pos.y -= lower.size.y;
			GameObject_Field_CollisionVertical(field, &lower, CONNECTION_LOOP, EDGESIDE_CENTER);
			lower.pos.y += lower.size.y;
			GameObject_Render(&lower, COLOR_WHITE);
		}
		GameObject_Render(&ship->ship, COLOR_WHITE);
	}
}
