//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  SpaceRace ノーマル課題
//!
//! @date   2018/06/13
//!
//! @author GF1 26 山口寛雅
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "GameObject.h"
#include "GameScore.h"
#include "GameResource.h"
#include "GameScene.h"
#include "GameSoundShip.h"


// グローバル変数の宣言 ====================================================

// <シーン> ------------------------------------------------------------
GameScene g_scene;

// <リソース> ----------------------------------------------------------
GameResource g_resources;

// <サウンド> ----------------------------------------------------------
GameSoundShip g_ship1_sound;
GameSoundShip g_ship2_sound;


// 関数の宣言 ==============================================================

// <ゲームの更新処理:シーン> -------------------------------------------
void UpdateGameSceneDemo(void);
void UpdateGameScenePlay(void);

// <ゲームの描画処理> --------------------------------------------------
void RenderGameSceneDemo(void);
void RenderGameScenePlay(void);


// 関数の定義 ==============================================================

//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeGame(void)
{
	// シーン状態
	g_scene.game_state = STATE_DEMO;

	// フィールド
	g_scene.field = GameObject_Field_Create();

	// 弾
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
		{
			g_scene.bullet[i] = GameObject_Bullet_Create();
			GameObject_Bullet_SetPosXDefault(&g_scene.bullet[i], &g_scene.field);
			GameObject_Bullet_SetPosYDefault(&g_scene.bullet[i], &g_scene.field);
			GameObject_Bullet_SetVelXDefault(&g_scene.bullet[i]);
		}
	}

	// シップ1
	g_scene.ship1 = GameObjectShip_Create(LEFT, &g_scene.field, 80);
	g_scene.ship1.controller = GameController_Player_Create(&g_scene.ship1.ship, PAD_INPUT_8, PAD_INPUT_5);

	// シップ2
	g_scene.ship2 = GameObjectShip_Create(RIGHT, &g_scene.field, 80);
	g_scene.ship2.controller = GameController_Player_Create(&g_scene.ship2.ship, PAD_INPUT_UP, PAD_INPUT_DOWN);

	// リソース
	g_resources = GameResource_Create();

	// シップサウンド
	g_ship1_sound = GameSoundShip_Create(&g_scene.field, &g_scene.ship1.ship, g_resources.sound_se02, SOUND_SHIP1_INTERVAL);
	g_ship2_sound = GameSoundShip_Create(&g_scene.field, &g_scene.ship2.ship, g_resources.sound_se03, SOUND_SHIP2_INTERVAL);

	// タイマー
	g_scene.timer = GameTimer_Create();

	// 得点
	g_scene.score = GameScore_Create();
}


//----------------------------------------------------------------------
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateGame(void)
{
	switch (g_scene.game_state)
	{
	case STATE_DEMO:
		UpdateGameSceneDemo();
		break;
	case STATE_PLAY:
		UpdateGameScenePlay();
		break;
	}
}

// <ゲームの更新処理:シーン:デモ> --------------------------------------
void UpdateGameSceneDemo(void)
{
	// 待機&初期化
	{
		// 入力されたら
		if (IsButtonDown(PAD_INPUT_10))
		{
			// タイマーを開始
			GameTimer_SetDefault(&g_scene.timer);

			// 点数リセット
			GameScore_Clear(&g_scene.score);

			// シップを初期位置へ
			GameObjectShip_Reset(&g_scene.ship1);
			GameObjectShip_Reset(&g_scene.ship2);

			// サウンド再生
			GameSoundShip_Start(&g_ship1_sound);
			GameSoundShip_Start(&g_ship2_sound);

			// シーンをプレイに変更
			g_scene.game_state = STATE_PLAY;
		}
	}

	// コントローラー更新
	GameController_Update(&g_scene.ship1.controller);
	GameController_Update(&g_scene.ship2.controller);

	// 座標更新
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
			GameObject_UpdatePosition(&g_scene.bullet[i]);
	}

	// 当たり判定
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
			GameObject_Field_CollisionHorizontal(&g_scene.field, &g_scene.bullet[i], CONNECTION_LOOP, EDGESIDE_OUTER);
	}
}

// <ゲームの更新処理:シーン:プレイ> ------------------------------------
void UpdateGameScenePlay(void)
{
	// コントローラー更新
	GameController_Update(&g_scene.ship1.controller);
	GameController_Update(&g_scene.ship2.controller);

	// シップ更新
	GameObjectShip_Update(&g_scene.ship1);
	GameObjectShip_Update(&g_scene.ship2);

	// 操作
	if (GameObjectShip_IsAvailable(&g_scene.ship1))
		GameController_UpdateControl(&g_scene.ship1.controller);
	if (GameObjectShip_IsAvailable(&g_scene.ship2))
		GameController_UpdateControl(&g_scene.ship2.controller);

	// 座標更新
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
			GameObject_UpdatePosition(&g_scene.bullet[i]);
	}
	GameObject_UpdatePosition(&g_scene.ship1.ship);
	GameObject_UpdatePosition(&g_scene.ship2.ship);

	// サウンド更新
	GameSoundShip_Update(&g_ship1_sound);
	GameSoundShip_Update(&g_ship2_sound);

	// 当たり判定
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
		{
			GameObject_Field_CollisionHorizontal(&g_scene.field, &g_scene.bullet[i], CONNECTION_LOOP, EDGESIDE_OUTER);

			if (GameObject_IsHit(&g_scene.ship1.ship, &g_scene.bullet[i]))
			{
				GameObjectShip_Kill(&g_scene.ship1);
				GameSoundShip_Stop(&g_ship1_sound);
				PlaySoundMem(g_resources.sound_se01, DX_PLAYTYPE_BACK);
			}

			if (GameObject_IsHit(&g_scene.ship2.ship, &g_scene.bullet[i]))
			{
				GameObjectShip_Kill(&g_scene.ship2);
				GameSoundShip_Stop(&g_ship2_sound);
				PlaySoundMem(g_resources.sound_se01, DX_PLAYTYPE_BACK);
			}
		}
	}
	GameObjectShip_CollisionScore(&g_scene.ship1, &g_scene.score);
	GameObjectShip_CollisionScore(&g_scene.ship2, &g_scene.score);

	// サーブ待機
	if (GameObjectShip_IsAvailable(&g_scene.ship1))
		GameSoundShip_Start(&g_ship1_sound);
	if (GameObjectShip_IsAvailable(&g_scene.ship2))
		GameSoundShip_Start(&g_ship2_sound);
}

//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderGame(void)
{
	switch (g_scene.game_state)
	{
	case STATE_DEMO:
		RenderGameSceneDemo();
		break;
	case STATE_PLAY:
		RenderGameScenePlay();
		break;
	}
}

// <ゲームの描画処理:シーン:デモ> ---------------------------------------------
void RenderGameSceneDemo(void)
{
	// <オブジェクト描画>
	// フィールド描画
	GameObject_Field_Render(&g_scene.field);
	// 弾描画
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
			GameObject_Render(&g_scene.bullet[i], COLOR_WHITE);
	}
	// スコア描画
	GameScore_Render(&g_scene.score, &g_scene.field, &g_resources);
}

// <ゲームの描画処理:シーン:プレイ> -------------------------------------------
void RenderGameScenePlay(void)
{
	// <オブジェクト描画>
	// フィールド描画
	GameObject_Field_Render(&g_scene.field);
	// タイム描画
	GameTimer_Render(&g_scene.timer, &g_scene.field, &g_resources);
	// スコア描画
	GameScore_Render(&g_scene.score, &g_scene.field, &g_resources);
	// シップ描画
	GameObjectShip_Render(&g_scene.ship1, &g_scene.field);
	GameObjectShip_Render(&g_scene.ship2, &g_scene.field);
	// 弾描画
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
			GameObject_Render(&g_scene.bullet[i], COLOR_WHITE);
	}
}

//----------------------------------------------------------------------
//! @brief ゲームの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeGame(void)
{
	GameResource_Delete(&g_resources);
}
