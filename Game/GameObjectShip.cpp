#include "GameObjectShip.h"

// 定数の定義 ==============================================================

// <リスポーン待機> ----------------------------------------------------
#define SHIP_WAIT_TIME 60

// 関数の定義 ==============================================================

// <<シップオブジェクト>> ----------------------------------------------

// <シップオブジェクト作成>
GameObjectShip GameObjectShip_Create(ObjectSide team, GameObject* field, float offset)
{
	GameObjectShip ship = { field, GameObject_Ship_Create(), 0, team };

	ship.ship.pos.x = GameObject_OffsetX(&ship.ship, ship.team, GameObject_GetX(ship.field, CENTER_X), 80);
	GameObjectShip_Reset(&ship);

	return ship;
}

// <シップオブジェクト初期化>
void GameObjectShip_Reset(GameObjectShip* ship)
{
	GameObject_Ship_SetPosYDefault(&ship->ship, ship->field);
	ship->counter = 0;
}

// <シップオブジェクト死亡>
void GameObjectShip_Kill(GameObjectShip* ship)
{
	GameObjectShip_Reset(ship);
	ship->counter = SHIP_WAIT_TIME;
}

// <シップオブジェクト更新>
void GameObjectShip_Update(GameObjectShip* ship)
{
	if (ship->counter > 0)
		ship->counter--;
}

// <シップオブジェクト有効>
BOOL GameObjectShip_IsAvailable(GameObjectShip* ship)
{
	return ship->counter <= 0;
}

// <シップオブジェクト当たり判定>
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

// <シップオブジェクト描画>
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
