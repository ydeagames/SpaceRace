#include "GameSoundShip.h"
#include "GameUtils.h"

// �֐��̐錾 ==============================================================

// <<�T�E���h>> --------------------------------------------------

void GameSoundShip_StartInternal(HSND sound, BOOL* playing);
void GameSoundShip_StopInternal(HSND sound, BOOL* playing);

// �֐��̒�` ==============================================================

// <<�T�E���h>> --------------------------------------------------

// <�T�E���h�쐬>
GameSoundShip GameSoundShip_Create(GameScene* scene, ObjectSide team, HSND sound, int interval)
{
	return { scene, team, FALSE, sound, interval };
}

// <�T�E���h�X�V>
void GameSoundShip_Update(GameSoundShip* sound)
{
	// �㉺�̃p�f�B���O���擾
	float padding_bottom = GameObject_GetY(&sound->scene->field, BOTTOM, -30);
	float padding_top = GameObject_GetY(&sound->scene->field, TOP, -10);
	BOOL alive = FALSE;									// �`�[���S�ł��Ă��Ȃ��t���O
	float best_y = padding_bottom;						// ��ԏ�܂ōs���Ă���V�b�v��Y���W

	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
		{
			GameObjectShip* ship = &sound->scene->ship[i];
			// �`�[������v ���� �V�b�v�������Ă���
			if (ship->team == sound->team && GameObjectShip_IsAlive(ship))
			{
				// �`�[���͐����Ă���
				alive = TRUE;
				// ��ԏ�܂ōs���Ă���V�b�v��Y���W�X�V
				best_y = GetMinF(best_y, ship->ship.pos.y);
			}
		}
	}

	if (alive)
	{
		// �����Ă�����
		// �i�����v�Z
		float progress = 1 - GetPercentageRange(best_y, padding_top, padding_bottom);
		// �i���ɉ����Ď��g�����v�Z
		int pitch = (int)(SOUND_PITCH_MIN * (1 - progress) + SOUND_PITCH_MAX * progress);
		// ���g����ݒ�
		SetFrequencySoundMem(pitch, sound->sound);
		// �^�C�~���O�������Ă���Ή��ʂ�ON�ɂ���
		SetVolumeSoundMem(((GetNowCount() / sound->interval) % 2 == 0) ? 10000 : 0, sound->sound);
	}
	else
		// �S�ł��Ă�����
		// ���ʂ�0�ɂ���
		SetVolumeSoundMem(0, sound->sound);
}

// <�T�E���h�Đ�>
void GameSoundShip_Start(GameSoundShip* sound)
{
	GameSoundShip_StartInternal(sound->sound, &sound->playing);
}

// <�T�E���h��~>
void GameSoundShip_Stop(GameSoundShip* sound)
{
	GameSoundShip_StopInternal(sound->sound, &sound->playing);
}

// <�T�E���h�Đ�>
void GameSoundShip_StartInternal(HSND sound, BOOL* playing)
{
	// �Đ����ĂȂ���΍Đ�
	if (!*playing)
		PlaySoundMem(sound, DX_PLAYTYPE_LOOP);
	*playing = TRUE;
}

// <�T�E���h��~>
void GameSoundShip_StopInternal(HSND sound, BOOL* playing)
{
	// �Đ����Ă���Β�~
	if (*playing)
		StopSoundMem(sound);
	*playing = FALSE;
}
