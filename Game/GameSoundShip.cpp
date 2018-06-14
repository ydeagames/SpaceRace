#include "GameSoundShip.h"
#include "GameUtils.h"

// �֐��̐錾 ==============================================================

// <<�T�E���h>> --------------------------------------------------

void GameSoundShip_StartInternal(HSND sound, BOOL* playing);
void GameSoundShip_StopInternal(HSND sound, BOOL* playing);

// �֐��̒�` ==============================================================

// <<�T�E���h>> --------------------------------------------------

// <�T�E���h�쐬>
GameSoundShip GameSoundShip_Create(GameObject* field, GameObject* ship, HSND sound, int interval)
{
	return { field, ship, FALSE,sound, interval };
}

// <�T�E���h�X�V>
void GameSoundShip_Update(GameSoundShip* sound)
{
	float progress = 1 - GetPercentageRange(sound->ship->pos.y, GameObject_GetY(sound->field, TOP, -10), GameObject_GetY(sound->field, BOTTOM, -30));
	int pitch = (int)(SOUND_PITCH_MIN * (1 - progress) + SOUND_PITCH_MAX * progress);

	SetFrequencySoundMem(pitch, sound->sound);

	SetVolumeSoundMem(((GetNowCount() / sound->interval) % 2 == 0) ? 10000 : 0, sound->sound);
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
	if (!*playing)
		PlaySoundMem(sound, DX_PLAYTYPE_LOOP);
	*playing = TRUE;
}

// <�T�E���h��~>
void GameSoundShip_StopInternal(HSND sound, BOOL* playing)
{
	if (*playing)
		StopSoundMem(sound);
	*playing = FALSE;
}
