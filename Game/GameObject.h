#pragma once
#include "Vec2.h"

// 列挙型の定義 ============================================================

// <シーン状態> --------------------------------------------------------
enum ObjectSide
{
	NONE = 0,
	CENTER_X = 1,	// X中央
	LEFT = -2,		// 左
	RIGHT = 2,		// 右
	CENTER_Y = -1,	// Y中央
	TOP = -3,		// 上
	BOTTOM = 3		// 下
};

// 構造体の宣言 ============================================================

// <ゲームオブジェクト>
typedef struct
{
	Vec2 pos;	// <位置>
	Vec2 vel;	// <速度>
	Vec2 size;	// <大きさ>
} GameObject;

// 定数の定義 ==============================================================

// <パドル>
#define SHIP_VEL 8		// パドルの速度

// 関数の宣言 ==============================================================

// <<オブジェクト>> ----------------------------------------------------

// <オブジェクト作成>
GameObject GameObject_Create(Vec2 pos, Vec2 vel, Vec2 size);

// <オブジェクト座標更新>
void GameObject_UpdatePosition(GameObject* obj);

// <オブジェクトXオフセット>
float GameObject_OffsetX(GameObject* obj, ObjectSide side, float pos = 0.f, float padding = 0.f);

// <オブジェクトXオフセット>
float GameObject_OffsetY(GameObject* obj, ObjectSide side, float pos = 0.f, float padding = 0.f);

// <オブジェクトX位置セット>
void GameObject_SetX(GameObject* obj, ObjectSide side, float pos = 0.f, float padding = 0.f);

// <オブジェクトY位置セット>
void GameObject_SetY(GameObject* obj, ObjectSide side, float pos = 0.f, float padding = 0.f);

// <オブジェクトX位置ゲット>
float GameObject_GetX(GameObject* obj, ObjectSide side, float padding = 0.f);

// <オブジェクトY位置ゲット>
float GameObject_GetY(GameObject* obj, ObjectSide side, float padding = 0.f);

// <オブジェクト当たり判定>
BOOL GameObject_IsHit(GameObject* obj1, GameObject* obj2);

// <オブジェクト描画>
void GameObject_Render(GameObject* obj, unsigned int color);

// <<ボールオブジェクト>> ----------------------------------------------

// <ボールオブジェクト作成>
GameObject GameObject_Bullet_Create(void);

// <ボールオブジェクト座標Xデフォルト>
void GameObject_Bullet_SetPosXDefault(GameObject* obj, GameObject* field);

// <ボールオブジェクト座標Yデフォルト>
void GameObject_Bullet_SetPosYDefault(GameObject* obj, GameObject* field);

// <ボールオブジェクト移動Xデフォルト>
void GameObject_Bullet_SetVelXDefault(GameObject* obj);

// <<パドルオブジェクト>> ----------------------------------------------

// <パドルオブジェクト作成>
GameObject GameObject_Ship_Create(void);

// <パドルオブジェクト座標Yデフォルト>
void GameObject_Ship_SetPosYDefault(GameObject* obj);

// <パドルオブジェクトボール衝突処理>
BOOL GameObject_Ship_CollisionBullet(GameObject* ship, GameObject* bullet);

// <<フィールドオブジェクト>> ------------------------------------------

// <ボールオブジェクト作成>
GameObject GameObject_Field_Create(void);

// <フィールド上下衝突処理>
ObjectSide GameObject_Field_CollisionVertical(GameObject* field, GameObject* obj);

// <フィールド左右衝突処理>
ObjectSide GameObject_Field_CollisionHorizontal(GameObject* field, GameObject* obj);

// <フィールド描画>
void GameObject_Field_Render(GameObject* field);
