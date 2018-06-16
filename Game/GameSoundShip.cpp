#include "GameSoundShip.h"
#include "GameUtils.h"

// 関数の宣言 ==============================================================

// <<サウンド>> --------------------------------------------------

void GameSoundShip_StartInternal(HSND sound, BOOL* playing);
void GameSoundShip_StopInternal(HSND sound, BOOL* playing);

// 関数の定義 ==============================================================

// <<サウンド>> --------------------------------------------------

// <サウンド作成>
GameSoundShip GameSoundShip_Create(GameScene* scene, ObjectSide team, HSND sound, int interval)
{
	return { scene, team, FALSE, sound, interval };
}

// <サウンド更新>
void GameSoundShip_Update(GameSoundShip* sound)
{
	// 上下のパディングを取得
	float padding_bottom = GameObject_GetY(&sound->scene->field, BOTTOM, -30);
	float padding_top = GameObject_GetY(&sound->scene->field, TOP, -10);
	BOOL alive = FALSE;									// チーム全滅していないフラグ
	float best_y = padding_bottom;						// 一番上まで行っているシップのY座標

	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
		{
			GameObjectShip* ship = &sound->scene->ship[i];
			// チームが一致 かつ シップが生きている
			if (ship->team == sound->team && GameObjectShip_IsAlive(ship))
			{
				// チームは生きている
				alive = TRUE;
				// 一番上まで行っているシップのY座標更新
				best_y = GetMinF(best_y, ship->ship.pos.y);
			}
		}
	}

	if (alive)
	{
		// 生きていたら
		// 進捗を計算
		float progress = 1 - GetPercentageRange(best_y, padding_top, padding_bottom);
		// 進捗に応じて周波数を計算
		int pitch = (int)(SOUND_PITCH_MIN * (1 - progress) + SOUND_PITCH_MAX * progress);
		// 周波数を設定
		SetFrequencySoundMem(pitch, sound->sound);
		// タイミングがあっていれば音量をONにする
		SetVolumeSoundMem(((GetNowCount() / sound->interval) % 2 == 0) ? 10000 : 0, sound->sound);
	}
	else
		// 全滅していたら
		// 音量を0にする
		SetVolumeSoundMem(0, sound->sound);
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
	// 再生してなければ再生
	if (!*playing)
		PlaySoundMem(sound, DX_PLAYTYPE_LOOP);
	*playing = TRUE;
}

// <サウンド停止>
void GameSoundShip_StopInternal(HSND sound, BOOL* playing)
{
	// 再生していれば停止
	if (*playing)
		StopSoundMem(sound);
	*playing = FALSE;
}
