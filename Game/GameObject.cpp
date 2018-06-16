#include "GameObject.h"
#include "GameMain.h"
#include "GameUtils.h"

// 定数の定義 ==============================================================

// <弾>
#define BULLET_WIDTH 8
#define BULLET_HEIGHT 8

// <シップ>
#define ship_WIDTH  8
#define ship_HEIGHT 28

// 関数の定義 ==============================================================

// <<オブジェクト>> ----------------------------------------------------

// <オブジェクト作成>
GameObject GameObject_Create(Vec2 pos, Vec2 vel, Vec2 size)
{
	return{ pos, vel, size };
}

// <オブジェクト座標更新>
void GameObject_UpdatePosition(GameObject* obj)
{
	obj->pos.x += obj->vel.x;
	obj->pos.y += obj->vel.y;
}

// <オブジェクトXオフセット>
float GameObject_OffsetX(GameObject* obj, ObjectSide side, float pos, float padding)
{
	float offset = 0;
	switch (side)
	{
	case LEFT:
		offset = -(padding + obj->size.x / 2.f);
		break;
	case RIGHT:
		offset = (padding + obj->size.x / 2.f);
		break;
	}
	return pos + offset;
}

// <オブジェクトXオフセット>
float GameObject_OffsetY(GameObject* obj, ObjectSide side, float pos, float padding)
{
	float offset = 0;
	switch (side)
	{
	case TOP:
		offset = -(padding + obj->size.y / 2.f);
		break;
	case BOTTOM:
		offset = (padding + obj->size.y / 2.f);
		break;
	}
	return pos + offset;
}

// <オブジェクトX位置ゲット>
float GameObject_GetX(GameObject* obj, ObjectSide side, float padding)
{
	return GameObject_OffsetX(obj, side, obj->pos.x, padding);
}

// <オブジェクトY位置ゲット>
float GameObject_GetY(GameObject* obj, ObjectSide side, float padding)
{
	return GameObject_OffsetY(obj, side, obj->pos.y, padding);
}

// <オブジェクト当たり判定>
BOOL GameObject_IsHit(GameObject* obj1, GameObject* obj2)
{
	return (
		GameObject_GetX(obj2, LEFT) < GameObject_GetX(obj1, RIGHT) &&
		GameObject_GetX(obj1, LEFT) < GameObject_GetX(obj2, RIGHT) &&
		GameObject_GetY(obj2, TOP) < GameObject_GetY(obj1, BOTTOM) &&
		GameObject_GetY(obj1, TOP) < GameObject_GetY(obj2, BOTTOM)
		);
}

// <オブジェクト描画>
void GameObject_Render(GameObject* obj, unsigned int color)
{
	DrawBoxAA(GameObject_GetX(obj, LEFT), GameObject_GetY(obj, TOP), GameObject_GetX(obj, RIGHT), GameObject_GetY(obj, BOTTOM), color, TRUE);
}

// <<弾オブジェクト>> ----------------------------------------------

// <弾オブジェクト作成>
GameObject GameObject_Bullet_Create(void)
{
	return GameObject_Create(Vec2_Create(), Vec2_Create(), Vec2_Create(BULLET_WIDTH, BULLET_HEIGHT));
}

// <弾オブジェクト座標Xデフォルト>
void GameObject_Bullet_SetPosXDefault(GameObject* obj, GameObject* field)
{
	obj->pos.x = GetRandRangeF(GameObject_GetX(field, LEFT), GameObject_GetX(field, RIGHT));
}

// <弾オブジェクト座標Yデフォルト>
void GameObject_Bullet_SetPosYDefault(GameObject* obj, GameObject* field)
{
	obj->pos.y = GetRandRangeF(GameObject_GetY(field, TOP), GameObject_GetY(field, BOTTOM, -85));
}

// <弾オブジェクト移動Xデフォルト>
void GameObject_Bullet_SetVelXDefault(GameObject* obj)
{
	obj->vel.x = (float)(GetRand(1) * 2 - 1)*BULLET_VEL;
}

// <<シップオブジェクト>> ----------------------------------------------

// <シップオブジェクト作成>
GameObject GameObject_Ship_Create(void)
{
	return GameObject_Create(Vec2_Create(), Vec2_Create(), Vec2_Create(ship_WIDTH, ship_HEIGHT));
}

// <シップオブジェクト座標Yデフォルト>
void GameObject_Ship_SetPosYDefault(GameObject* obj, GameObject* field)
{
	obj->pos.y = GameObject_OffsetY(obj, TOP, GameObject_GetY(field, BOTTOM), 16);
}

// <<フィールドオブジェクト>> ------------------------------------------

// <フィールドオブジェクト作成>
GameObject GameObject_Field_Create(void)
{
	return GameObject_Create(Vec2_Create(SCREEN_CENTER_X, SCREEN_CENTER_Y), Vec2_Create(), Vec2_Create(SCREEN_WIDTH, SCREEN_HEIGHT));
}

// <フィールド上下衝突処理>
ObjectSide GameObject_Field_CollisionVertical(GameObject* field, GameObject* obj, ObjectConnection connection, ObjectEdgeSide edge)
{
	// ヒットサイド
	ObjectSide side_hit = NONE;

	// 弾・上下壁当たり判定
	{
		float padding_top = GameObject_GetY(field, TOP);
		float padding_bottom = GameObject_GetY(field, BOTTOM);
		switch (edge)
		{
		case EDGESIDE_INNER:
			padding_top = GameObject_OffsetY(obj, BOTTOM, padding_top);
			padding_bottom = GameObject_OffsetY(obj, TOP, padding_bottom);
			break;
		case EDGESIDE_OUTER:
			padding_top = GameObject_OffsetY(obj, TOP, padding_top);
			padding_bottom = GameObject_OffsetY(obj, BOTTOM, padding_bottom);
			break;
		}

		if (obj->pos.y < padding_top)
			side_hit = TOP;
		else if (padding_bottom <= obj->pos.y)
			side_hit = BOTTOM;

		switch (connection)
		{
		case CONNECTION_BARRIER:
			// 壁にあたったら調整
			obj->pos.y = ClampF(obj->pos.y, padding_top, padding_bottom);
			break;
		case CONNECTION_LOOP:
			// 壁にあたったらループ
			obj->pos.y = GetLoopRangeF(obj->pos.y, padding_top, padding_bottom);
			break;
		}
	}

	return side_hit;
}

// <フィールド左右衝突処理>
ObjectSide GameObject_Field_CollisionHorizontal(GameObject* field, GameObject* obj, ObjectConnection connection, ObjectEdgeSide edge)
{
	// ヒットサイド
	ObjectSide side_hit = NONE;

	// 弾・左右壁当たり判定
	{
		float padding_left = GameObject_GetX(field, LEFT);
		float padding_right = GameObject_GetX(field, RIGHT);
		switch (edge)
		{
		case EDGESIDE_INNER:
			padding_left = GameObject_OffsetX(obj, RIGHT, padding_left);
			padding_right = GameObject_OffsetX(obj, LEFT, padding_right);
			break;
		case EDGESIDE_OUTER:
			padding_left = GameObject_OffsetX(obj, LEFT, padding_left);
			padding_right = GameObject_OffsetX(obj, RIGHT, padding_right);
			break;
		}

		if (obj->pos.x < padding_left)
			side_hit = LEFT;
		else if (padding_right <= obj->pos.x)
			side_hit = RIGHT;

		switch (connection)
		{
		case CONNECTION_BARRIER:
			// 壁にあたったら調整
			obj->pos.x = ClampF(obj->pos.x, padding_left, padding_right);
			break;
		case CONNECTION_LOOP:
			// 壁にあたったらループ
			obj->pos.x = GetLoopRangeF(obj->pos.x, padding_left, padding_right);
			break;
		}
	}

	return side_hit;
}

// <フィールド描画>
void GameObject_Field_Render(GameObject* field)
{
}

