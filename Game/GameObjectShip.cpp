#include "GameObjectShip.h"

// 定数の定義 ==============================================================

// <リスポーン待機>
#define SHIP_WAIT_TIME 60

// 関数の定義 ==============================================================

// <<シップオブジェクト>> ----------------------------------------------

// <シップオブジェクト作成>
GameObjectShip GameObjectShip_Create(ObjectSide team, GameObject* field, float offset)
{
	GameObject shipobj = GameObject_Ship_Create();
	GameObjectShip ship = { field, shipobj, GameController_Default_Create(&shipobj), 0, team };
	ship.ship.pos.x = GameObject_OffsetX(&ship.ship, ship.team, GameObject_GetX(ship.field, CENTER_X), offset);
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

// <シップオブジェクト生きている>
BOOL GameObjectShip_IsAlive(GameObjectShip* ship)
{
	return ship->counter <= 0;
}

// <シップオブジェクト当たり判定>
BOOL GameObjectShip_CollisionScore(GameObjectShip* ship, GameScore* score)
{
	// 外側の上にあたっていたら
	if (GameObject_Field_CollisionVertical(ship->field, &ship->ship, CONNECTION_NONE, EDGESIDE_OUTER) == TOP)
	{
		// 中側のフィールドでループ
		GameObject_Field_CollisionVertical(ship->field, &ship->ship, CONNECTION_LOOP, EDGESIDE_CENTER);
		// スコアを加算
		GameScore_Add(score, ship->team);

		return TRUE;
	}
	// 内側の下に当たっていたら
	else if (GameObject_Field_CollisionVertical(ship->field, &ship->ship, CONNECTION_NONE, EDGESIDE_INNER) == BOTTOM)
		// 内側のフィールドでブロック
		GameObject_Field_CollisionVertical(ship->field, &ship->ship, CONNECTION_BARRIER, EDGESIDE_INNER);

	return FALSE;
}

// <シップオブジェクト描画>
void GameObjectShip_Render(GameObjectShip* ship, GameObject* field)
{
	// 生きていたら
	if (GameObjectShip_IsAlive(ship))
	{
		// 上端の半分にシップがめり込んだとき下から半分出てくるように表示
		// 内側の上に当たっていたら
		if (GameObject_Field_CollisionVertical(field, &ship->ship, CONNECTION_NONE, EDGESIDE_INNER) == TOP)
		{
			// 1ループした下側のシップの描画
			GameObject obj = ship->ship;
			obj.pos.y -= obj.size.y;
			GameObject_Field_CollisionVertical(field, &obj, CONNECTION_LOOP, EDGESIDE_CENTER);
			obj.pos.y += obj.size.y;
			GameObject_Render(&obj);
		}
		// シップ描画
		GameObject_Render(&ship->ship);
	}
}
