#pragma once
#include "GameScene.h"
#include "GameResource.h"

// 構造体の宣言 ============================================================

// <ゲームサウンド>
typedef struct
{
	// <フィールド>
	GameScene* scene;

	// <チーム>
	ObjectSide team;

	// <プレイ中フラグ>
	BOOL playing;

	// <サウンド>
	HSND sound;

	// サウンドのリズム
	int interval;
} GameSoundShip;

// 定数の定義 ==============================================================

// <サウンド> ----------------------------------------------------------

#define SOUND_PITCH_MAX ((int) 44100*2.6f)		// シップの音ピッチ最大
#define SOUND_PITCH_MIN ((int) 44100*1.0f)		// シップの音ピッチ最小
#define SOUND_SHIP1_INTERVAL 67					// シップ1の音リズム
#define SOUND_SHIP2_INTERVAL (67*2)				// シップ2の音リズム

// 関数の宣言 ==============================================================

// <<サウンド>> --------------------------------------------------

// <サウンド作成>
GameSoundShip GameSoundShip_Create(GameScene* scene, ObjectSide team, HSND sound, int interval);

// <サウンド更新>
void GameSoundShip_Update(GameSoundShip* sound);

// <サウンド再生>
void GameSoundShip_Start(GameSoundShip* sound);

// <サウンド停止>
void GameSoundShip_Stop(GameSoundShip* sound);
