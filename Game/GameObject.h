#pragma once
#include "Vec2.h"

// �񋓌^�̒�` ============================================================

// <�V�[�����> --------------------------------------------------------
enum ObjectSide
{
	NONE = 0,
	CENTER_X = 1,	// X����
	LEFT = -2,		// ��
	RIGHT = 2,		// �E
	CENTER_Y = -1,	// Y����
	TOP = -3,		// ��
	BOTTOM = 3		// ��
};

// �\���̂̐錾 ============================================================

// <�Q�[���I�u�W�F�N�g>
typedef struct
{
	Vec2 pos;	// <�ʒu>
	Vec2 vel;	// <���x>
	Vec2 size;	// <�傫��>
} GameObject;

// �萔�̒�` ==============================================================

// <�p�h��>
#define SHIP_VEL 4		// �p�h���̑��x
#define BULLET_VEL 2	// �e�̑��x

// �֐��̐錾 ==============================================================

// <<�I�u�W�F�N�g>> ----------------------------------------------------

// <�I�u�W�F�N�g�쐬>
GameObject GameObject_Create(Vec2 pos, Vec2 vel, Vec2 size);

// <�I�u�W�F�N�g���W�X�V>
void GameObject_UpdatePosition(GameObject* obj);

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject_OffsetX(GameObject* obj, ObjectSide side, float pos = 0.f, float padding = 0.f);

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject_OffsetY(GameObject* obj, ObjectSide side, float pos = 0.f, float padding = 0.f);

// <�I�u�W�F�N�gX�ʒu�Q�b�g>
float GameObject_GetX(GameObject* obj, ObjectSide side, float padding = 0.f);

// <�I�u�W�F�N�gY�ʒu�Q�b�g>
float GameObject_GetY(GameObject* obj, ObjectSide side, float padding = 0.f);

// <�I�u�W�F�N�g�����蔻��>
BOOL GameObject_IsHit(GameObject* obj1, GameObject* obj2);

// <�I�u�W�F�N�g�`��>
void GameObject_Render(GameObject* obj, unsigned int color);

// <<�{�[���I�u�W�F�N�g>> ----------------------------------------------

// <�{�[���I�u�W�F�N�g�쐬>
GameObject GameObject_Bullet_Create(void);

// <�{�[���I�u�W�F�N�g���WX�f�t�H���g>
void GameObject_Bullet_SetPosXDefault(GameObject* obj, GameObject* field);

// <�{�[���I�u�W�F�N�g���WY�f�t�H���g>
void GameObject_Bullet_SetPosYDefault(GameObject* obj, GameObject* field);

// <�{�[���I�u�W�F�N�g�ړ�X�f�t�H���g>
void GameObject_Bullet_SetVelXDefault(GameObject* obj);

// <<�p�h���I�u�W�F�N�g>> ----------------------------------------------

// <�p�h���I�u�W�F�N�g�쐬>
GameObject GameObject_Ship_Create(void);

// <�p�h���I�u�W�F�N�g���WY�f�t�H���g>
void GameObject_Ship_SetPosYDefault(GameObject* obj, GameObject* field);

// <�p�h���I�u�W�F�N�g�{�[���Փˏ���>
BOOL GameObject_Ship_CollisionBullet(GameObject* ship, GameObject* bullet);

// <<�t�B�[���h�I�u�W�F�N�g>> ------------------------------------------

// <�{�[���I�u�W�F�N�g�쐬>
GameObject GameObject_Field_Create(void);

// <�t�B�[���h�㉺�Փˏ���>
ObjectSide GameObject_Field_CollisionVertical(GameObject* field, GameObject* obj, BOOL is_loop = TRUE, BOOL is_inner = FALSE);

// <�t�B�[���h���E�Փˏ���>
ObjectSide GameObject_Field_CollisionHorizontal(GameObject* field, GameObject* obj, BOOL is_loop = TRUE, BOOL is_inner = FALSE);

// <�t�B�[���h�`��>
void GameObject_Field_Render(GameObject* field);
