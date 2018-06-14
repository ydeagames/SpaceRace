#pragma once
#include "GameObject.h"
#include "GameResource.h"

// 構造体の宣言 ============================================================

// <ゲームサウンド>
typedef struct
{
	// <シーン>
	GameObject* field;

	// <シップ>
	GameObject* ship;

	// <プレイ中フラグ>
	BOOL playing;

	// <サウンド>
	HSND sound;

	// サウンドのリズム
	int interval;
} GameSoundShip;

// 定数の定義 ==============================================================

// <サウンド> ----------------------------------------------------------

#define SOUND_PITCH_MAX ((int) 44100*2.6f)
#define SOUND_PITCH_MIN ((int) 44100*1.0f)
#define SOUND_SHIP1_INTERVAL 67
#define SOUND_SHIP2_INTERVAL (67*2)

// 関数の宣言 ==============================================================

// <<サウンド>> --------------------------------------------------

// <サウンド作成>
GameSoundShip GameSoundShip_Create(GameObject* field, GameObject* ship, HSND sound, int interval);

// <サウンド更新>
void GameSoundShip_Update(GameSoundShip* sound);

// <サウンド再生>
void GameSoundShip_Start(GameSoundShip* sound);

// <サウンド停止>
void GameSoundShip_Stop(GameSoundShip* sound);
