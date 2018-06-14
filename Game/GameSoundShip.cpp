#include "GameSoundShip.h"
#include "GameUtils.h"

// 関数の宣言 ==============================================================

// <<サウンド>> --------------------------------------------------

void GameSoundShip_StartInternal(HSND sound, BOOL* playing);
void GameSoundShip_StopInternal(HSND sound, BOOL* playing);

// 関数の定義 ==============================================================

// <<サウンド>> --------------------------------------------------

// <サウンド作成>
GameSoundShip GameSoundShip_Create(GameObject* field, GameObject* ship, HSND sound, int interval)
{
	return { field, ship, FALSE,sound, interval };
}

// <サウンド更新>
void GameSoundShip_Update(GameSoundShip* sound)
{
	float progress = 1 - GetPercentageRange(sound->ship->pos.y, GameObject_GetY(sound->field, TOP, -10), GameObject_GetY(sound->field, BOTTOM, -30));
	int pitch = (int)(SOUND_PITCH_MIN * (1 - progress) + SOUND_PITCH_MAX * progress);

	SetFrequencySoundMem(pitch, sound->sound);

	SetVolumeSoundMem(((GetNowCount() / sound->interval) % 2 == 0) ? 10000 : 0, sound->sound);
}

// <サウンド再生>
void GameSoundShip_Start(GameSoundShip* sound)
{
	GameSoundShip_StartInternal(sound->sound, &sound->playing);
}

// <サウンド停止>
void GameSoundShip_Stop(GameSoundShip* sound)
{
	GameSoundShip_StopInternal(sound->sound, &sound->playing);
}

// <サウンド再生>
void GameSoundShip_StartInternal(HSND sound, BOOL* playing)
{
	if (!*playing)
		PlaySoundMem(sound, DX_PLAYTYPE_LOOP);
	*playing = TRUE;
}

// <サウンド停止>
void GameSoundShip_StopInternal(HSND sound, BOOL* playing)
{
	if (*playing)
		StopSoundMem(sound);
	*playing = FALSE;
}
