#include "GameObject.h"
#include "GameMain.h"
#include "GameUtils.h"

// �萔�̒�` ==============================================================

// <�e>
#define BULLET_WIDTH 8
#define BULLET_HEIGHT 8

// <�V�b�v>
#define ship_WIDTH  8
#define ship_HEIGHT 28

// �֐��̒�` ==============================================================

// <<�I�u�W�F�N�g>> ----------------------------------------------------

// <�I�u�W�F�N�g�쐬>
GameObject GameObject_Create(Vec2 pos, Vec2 vel, Vec2 size)
{
	return{ pos, vel, size };
}

// <�I�u�W�F�N�g���W�X�V>
void GameObject_UpdatePosition(GameObject* obj)
{
	obj->pos.x += obj->vel.x;
	obj->pos.y += obj->vel.y;
}

// <�I�u�W�F�N�gX�I�t�Z�b�g>
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

// <�I�u�W�F�N�gX�I�t�Z�b�g>
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

// <�I�u�W�F�N�gX�ʒu�Z�b�g>
void GameObject_SetX(GameObject* obj, ObjectSide side, float pos, float padding)
{
	obj->pos.x = GameObject_OffsetX(obj, side, pos, padding);
}

// <�I�u�W�F�N�gY�ʒu�Z�b�g>
void GameObject_SetY(GameObject* obj, ObjectSide side, float pos, float padding)
{
	obj->pos.y = GameObject_OffsetY(obj, side, pos, padding);
}

// <�I�u�W�F�N�gX�ʒu�Q�b�g>
float GameObject_GetX(GameObject* obj, ObjectSide side, float padding)
{
	return GameObject_OffsetX(obj, side, obj->pos.x, padding);
}

// <�I�u�W�F�N�gY�ʒu�Q�b�g>
float GameObject_GetY(GameObject* obj, ObjectSide side, float padding)
{
	return GameObject_OffsetY(obj, side, obj->pos.y, padding);
}

// <�I�u�W�F�N�g�����蔻��>
BOOL GameObject_IsHit(GameObject* obj1, GameObject* obj2)
{
	return (
		GameObject_GetX(obj2, LEFT) < GameObject_GetX(obj1, RIGHT) &&
		GameObject_GetX(obj1, LEFT) < GameObject_GetX(obj2, RIGHT) &&
		GameObject_GetY(obj2, TOP) < GameObject_GetY(obj1, BOTTOM) &&
		GameObject_GetY(obj1, TOP) < GameObject_GetY(obj2, BOTTOM)
		);
}

// <�I�u�W�F�N�g�`��>
void GameObject_Render(GameObject* obj, unsigned int color)
{
	DrawBoxAA(GameObject_GetX(obj, LEFT), GameObject_GetY(obj, TOP), GameObject_GetX(obj, RIGHT), GameObject_GetY(obj, BOTTOM), color, TRUE);
}

// <<�e�I�u�W�F�N�g>> ----------------------------------------------

// <�e�I�u�W�F�N�g�쐬>
GameObject GameObject_Bullet_Create(void)
{
	return GameObject_Create(Vec2_Create(), Vec2_Create(), Vec2_Create(BULLET_WIDTH, BULLET_HEIGHT));
}

// <�e�I�u�W�F�N�g���WX�f�t�H���g>
void GameObject_Bullet_SetPosXDefault(GameObject* obj, GameObject* field)
{
	obj->pos.x = GetRandRangeF(GameObject_GetX(field, LEFT), GameObject_GetX(field, RIGHT));
}

// <�e�I�u�W�F�N�g���WY�f�t�H���g>
void GameObject_Bullet_SetPosYDefault(GameObject* obj, GameObject* field)
{
	obj->pos.y = GetRandRangeF(GameObject_GetY(field, TOP), GameObject_GetY(field, BOTTOM, -85));
}

// <�e�I�u�W�F�N�g�ړ�X�f�t�H���g>
void GameObject_Bullet_SetVelXDefault(GameObject* obj)
{
	obj->vel.x = (float)(GetRand(1) * 2 - 1)*BULLET_VEL;
}

// <<�V�b�v�I�u�W�F�N�g>> ----------------------------------------------

// <�V�b�v�I�u�W�F�N�g�쐬>
GameObject GameObject_Ship_Create(void)
{
	return GameObject_Create(Vec2_Create(), Vec2_Create(), Vec2_Create(ship_WIDTH, ship_HEIGHT));
}

// <�V�b�v�I�u�W�F�N�g���WY�f�t�H���g>
void GameObject_Ship_SetPosYDefault(GameObject* obj, GameObject* field)
{
	GameObject_SetY(obj, TOP, GameObject_GetY(field, BOTTOM), 16);
}

// <�V�b�v�I�u�W�F�N�g�e�Փˏ���>
BOOL GameObject_Ship_CollisionBullet(GameObject* ship, GameObject* bullet)
{
	if (GameObject_IsHit(bullet, ship))
	{

		return TRUE;
	}

	return FALSE;
}

// <<�t�B�[���h�I�u�W�F�N�g>> ------------------------------------------

// <�e�I�u�W�F�N�g�쐬>
GameObject GameObject_Field_Create(void)
{
	return GameObject_Create(Vec2_Create(SCREEN_CENTER_X, SCREEN_CENTER_Y), Vec2_Create(), Vec2_Create(SCREEN_WIDTH, SCREEN_HEIGHT));
}

// <�t�B�[���h�㉺�Փˏ���>
ObjectSide GameObject_Field_CollisionVertical(GameObject* field, GameObject* obj)
{
	// �q�b�g�T�C�h
	ObjectSide side_hit = NONE;

	// �e�E�㉺�Ǔ����蔻��
	{
		float padding_top = GameObject_OffsetY(obj, TOP, GameObject_GetY(field, TOP));
		float padding_bottom = GameObject_OffsetY(obj, BOTTOM, GameObject_GetY(field, BOTTOM));

		if (obj->pos.y < padding_top)
			side_hit = TOP;
		else if (padding_bottom <= obj->pos.y)
			side_hit = BOTTOM;

		// �ǂɂ��������烋�[�v
		obj->pos.y = GetLoopRangeF(obj->pos.y, padding_top, padding_bottom);
	}

	return side_hit;
}

// <�t�B�[���h���E�Փˏ���>
ObjectSide GameObject_Field_CollisionHorizontal(GameObject* field, GameObject* obj)
{
	// �q�b�g�T�C�h
	ObjectSide side_hit = NONE;

	// �e�E���E�Ǔ����蔻��
	{
		float padding_left = GameObject_OffsetX(obj, LEFT, GameObject_GetX(field, LEFT));
		float padding_right = GameObject_OffsetX(obj, RIGHT, GameObject_GetX(field, RIGHT));

		if (obj->pos.x < padding_left)
			side_hit = LEFT;
		else if (padding_right <= obj->pos.x)
			side_hit = RIGHT;

		// �ǂɂ��������烋�[�v
		obj->pos.x = GetLoopRangeF(obj->pos.x, padding_left, padding_right);
	}

	return side_hit;
}

// <�t�B�[���h�`��>
void GameObject_Field_Render(GameObject* field)
{
}

