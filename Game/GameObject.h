#pragma once
#include "Vec2.h"

// �񋓌^�̒�` ============================================================

// <�ʒu�֌W> ----------------------------------------------------------
enum ObjectSide
{
	NONE = 0,
	CENTER_X = 1,				// X����
	LEFT = -2,					// ��
	RIGHT = 2,					// �E
	CENTER_Y = -1,				// Y����
	TOP = -3,					// ��
	BOTTOM = 3					// ��
};

// <���̈ʒu> ----------------------------------------------------------
enum ObjectEdgeSide
{
	EDGESIDE_CENTER = 0,		// ���̏�
	EDGESIDE_OUTER = -1,		// ���̊O��
	EDGESIDE_INNER = 1			// ���̓���
};

// <���[���h�̂Ȃ���> ------------------------------------------------
enum ObjectConnection
{
	CONNECTION_NONE = 0,		// �q����Ȃ��A�����Ȃ���ԂɈړ�
	CONNECTION_BARRIER,			// �ǂ�����A�i�߂Ȃ�
	CONNECTION_LOOP				// ���Α�����o�Ă���
};

// �\���̂̐錾 ============================================================

// <�e�N�X�`��>
typedef struct
{
	HGRP texture;				// <�e�N�X�`��>
	Vec2 anchor;				// <�e�N�X�`����_>
	Vec2 size;					// <�e�N�X�`���T�C�Y>
	Vec2 center;				// <�e�N�X�`�����S>
} GameTexture;

// <�X�v���C�g�I�u�W�F�N�g>
typedef struct
{
	unsigned int color;			// <�F>
	GameTexture texture;		// <�e�N�X�`��>
	Vec2 offset;				// <�I�t�Z�b�g>
	float scale;				// <�X�P�[��>
	float angle;				// <��]>
} GameSprite;

// <�Q�[���I�u�W�F�N�g>
typedef struct
{
	Vec2 pos;					// <�ʒu>
	Vec2 vel;					// <���x>
	Vec2 size;					// <�傫��>
	GameSprite sprite;			// <�X�v���C�g>
} GameObject;

// �萔�̒�` ==============================================================

// <�e�N�X�`��>
#define TEXTURE_MISSING -1		// �e�N�X�`����������܂���
#define TEXTURE_NONE -2			// �e�N�X�`���Ȃ�
// <�V�b�v>
#define SHIP_VEL 2.3f			// �V�b�v�̑��x
// <�e>
#define BULLET_VEL 2			// �e�̑��x

// �֐��̐錾 ==============================================================

// <<�e�N�X�`��>> ------------------------------------------------------

// <�e�N�X�`���쐬>
GameTexture GameTexture_Create(HGRP texture, Vec2 anchor, Vec2 size);

// <�e�N�X�`���Ȃ�>
GameTexture GameTexture_CreateNone();

// <<�X�v���C�g>> ------------------------------------------------------

// <�X�v���C�g�쐬>
GameSprite GameSprite_Create(GameTexture texture, float scale = 1, float angle = 0);

// <�X�v���C�g�Ȃ�>
GameSprite GameSprite_CreateNone();

// <<�I�u�W�F�N�g>> ----------------------------------------------------

// <�I�u�W�F�N�g�쐬>
GameObject GameObject_Create(Vec2 pos, Vec2 vel, Vec2 size);

// <�I�u�W�F�N�g���W�X�V>
void GameObject_UpdatePosition(GameObject* obj);

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject_OffsetX(GameObject* obj, ObjectSide side, float pos = 0.f, float margin = 0.f);

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject_OffsetY(GameObject* obj, ObjectSide side, float pos = 0.f, float margin = 0.f);

// <�I�u�W�F�N�gX�ʒu�Q�b�g>
float GameObject_GetX(GameObject* obj, ObjectSide side, float margin = 0.f);

// <�I�u�W�F�N�gY�ʒu�Q�b�g>
float GameObject_GetY(GameObject* obj, ObjectSide side, float margin = 0.f);

// <�I�u�W�F�N�g�����蔻��>
BOOL GameObject_IsHit(GameObject* obj1, GameObject* obj2);

// <�I�u�W�F�N�g�`��>
void GameObject_Render(GameObject* obj);

// <<�e�I�u�W�F�N�g>> ----------------------------------------------

// <�e�I�u�W�F�N�g�쐬>
GameObject GameObject_Bullet_Create(void);

// <�e�I�u�W�F�N�g���WX�f�t�H���g>
void GameObject_Bullet_SetPosXDefault(GameObject* obj, GameObject* field);

// <�e�I�u�W�F�N�g���WY�f�t�H���g>
void GameObject_Bullet_SetPosYDefault(GameObject* obj, GameObject* field);

// <�e�I�u�W�F�N�g�ړ�X�f�t�H���g>
void GameObject_Bullet_SetVelXDefault(GameObject* obj);

// <<�V�b�v�I�u�W�F�N�g>> ----------------------------------------------

// <�V�b�v�I�u�W�F�N�g�쐬>
GameObject GameObject_Ship_Create(void);

// <�V�b�v�I�u�W�F�N�g���WY�f�t�H���g>
void GameObject_Ship_SetPosYDefault(GameObject* obj, GameObject* field);

// <<�t�B�[���h�I�u�W�F�N�g>> ------------------------------------------

// <�t�B�[���h�I�u�W�F�N�g�쐬>
GameObject GameObject_Field_Create(void);

// <�t�B�[���h�㉺�Փˏ���>
ObjectSide GameObject_Field_CollisionVertical(GameObject* field, GameObject* obj, ObjectConnection connection, ObjectEdgeSide edge);

// <�t�B�[���h���E�Փˏ���>
ObjectSide GameObject_Field_CollisionHorizontal(GameObject* field, GameObject* obj, ObjectConnection connection, ObjectEdgeSide edge);

// <�t�B�[���h�`��>
void GameObject_Field_Render(GameObject* field);
