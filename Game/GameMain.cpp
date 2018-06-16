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
#include "GameControllers.h"
#include "GameScore.h"
#include "GameResource.h"
#include "GameScene.h"
#include "GameSoundShip.h"


// 定数の定義 ==============================================================

// <サーブ待機> --------------------------------------------------------
#define SHIP_WAIT_TIME 60


// グローバル変数の宣言 ====================================================

// <シーン> ------------------------------------------------------------
GameScene g_scene;

// <コントローラー> ----------------------------------------------------
GameControllers g_controllers;

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
	g_scene.ship1 = GameObject_Ship_Create();
	g_scene.ship1.pos.x = GameObject_OffsetX(&g_scene.ship1, LEFT, GameObject_GetX(&g_scene.field, CENTER_X), 80);
	GameObject_Ship_SetPosYDefault(&g_scene.ship1, &g_scene.field);
	g_controllers.paddle1 = GameController_Player_Create(&g_scene.ship1, &g_scene, &g_scene.ship2, PAD_INPUT_8, PAD_INPUT_5);

	// シップ2
	g_scene.ship2 = GameObject_Ship_Create();
	g_scene.ship2.pos.x = GameObject_OffsetX(&g_scene.ship2, RIGHT, GameObject_GetX(&g_scene.field, CENTER_X), 80);
	GameObject_Ship_SetPosYDefault(&g_scene.ship2, &g_scene.field);
	g_controllers.paddle2 = GameController_Player_Create(&g_scene.ship2, &g_scene, &g_scene.ship1, PAD_INPUT_UP, PAD_INPUT_DOWN);

	// リソース
	g_resources = GameResource_Create();

	// シップサウンド
	g_ship1_sound = GameSoundShip_Create(&g_scene.field, &g_scene.ship1, g_resources.sound_se02, SOUND_SHIP1_INTERVAL);
	g_ship2_sound = GameSoundShip_Create(&g_scene.field, &g_scene.ship2, g_resources.sound_se03, SOUND_SHIP2_INTERVAL);

	// タイマー
	g_scene.timer = GameTimer_Create();

	// 得点
	g_scene.score = GameScore_Create();

	// サーブ待機
	g_scene.ship1_counter = 0;
	g_scene.ship2_counter = 0;
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
			GameObject_Ship_SetPosYDefault(&g_scene.ship1, &g_scene.field);
			GameObject_Ship_SetPosYDefault(&g_scene.ship2, &g_scene.field);

			// サウンド再生
			GameSoundShip_Start(&g_ship1_sound);
			GameSoundShip_Start(&g_ship2_sound);

			// シーンをプレイに変更
			g_scene.game_state = STATE_PLAY;
		}
	}

	// コントローラー更新
	GameController_Update(&g_controllers.paddle1);
	GameController_Update(&g_controllers.paddle2);

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
			GameObject_Field_CollisionHorizontal(&g_scene.field, &g_scene.bullet[i]);
	}
}

// <ゲームの更新処理:シーン:プレイ> ------------------------------------
void UpdateGameScenePlay(void)
{
	// コントローラー更新
	GameController_Update(&g_controllers.paddle1);
	GameController_Update(&g_controllers.paddle2);

	// 操作
	if (g_scene.ship1_counter<=0)
		GameController_UpdateControl(&g_controllers.paddle1);
	if (g_scene.ship2_counter<=0)
		GameController_UpdateControl(&g_controllers.paddle2);

	// 座標更新
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
			GameObject_UpdatePosition(&g_scene.bullet[i]);
	}
	GameObject_UpdatePosition(&g_scene.ship1);
	GameObject_UpdatePosition(&g_scene.ship2);

	// サウンド更新
	GameSoundShip_Update(&g_ship1_sound);
	GameSoundShip_Update(&g_ship2_sound);

	// 当たり判定
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
		{
			GameObject_Field_CollisionHorizontal(&g_scene.field, &g_scene.bullet[i]);

			if (GameObject_Ship_CollisionBullet(&g_scene.ship1, &g_scene.bullet[i]))
			{
				GameObject_Ship_SetPosYDefault(&g_scene.ship1, &g_scene.field);
				g_scene.ship1_counter = SHIP_WAIT_TIME;
				GameSoundShip_Stop(&g_ship1_sound);
				PlaySoundMem(g_resources.sound_se01, DX_PLAYTYPE_BACK);
			}

			if (GameObject_Ship_CollisionBullet(&g_scene.ship2, &g_scene.bullet[i]))
			{
				GameObject_Ship_SetPosYDefault(&g_scene.ship2, &g_scene.field);
				g_scene.ship2_counter = SHIP_WAIT_TIME;
				GameSoundShip_Stop(&g_ship2_sound);
				PlaySoundMem(g_resources.sound_se01, DX_PLAYTYPE_BACK);
			}
		}
	}
	{
		if (GameObject_Field_CollisionVertical(&g_scene.field, &g_scene.ship1, FALSE, FALSE) == TOP)
		{
			GameScore_Add(&g_scene.score, LEFT);
		}
		if (GameObject_Field_CollisionVertical(&g_scene.field, &g_scene.ship2, FALSE, FALSE) == TOP)
		{
			GameScore_Add(&g_scene.score, RIGHT);
		}
	}

	// サーブ待機
	if (g_scene.ship1_counter>0)
		g_scene.ship1_counter--;
	else if (g_scene.ship1_counter==0)
		GameSoundShip_Start(&g_ship1_sound);
	if (g_scene.ship2_counter>0)
		g_scene.ship2_counter--;
	else if (g_scene.ship2_counter==0)
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
	if (g_scene.ship1_counter <= 0)
	{
		{
			GameObject field = g_scene.field;
			GameObject lower = g_scene.ship1;
			field.size.y -= lower.size.y;
			lower.pos.y -= lower.size.y;
			GameObject_Field_CollisionVertical(&field, &lower, TRUE, FALSE);
			lower.pos.y += lower.size.y;
			GameObject_Render(&lower, COLOR_WHITE);
		}
		GameObject_Render(&g_scene.ship1, COLOR_WHITE);
	}
	if (g_scene.ship2_counter<=0)
		GameObject_Render(&g_scene.ship2, COLOR_WHITE);
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
