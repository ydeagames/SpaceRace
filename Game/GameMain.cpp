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

	// シップ1 [↑:W, ↓:S]
	{
		GameObjectShip* ship = &g_scene.ship[0];
		*ship = GameObjectShip_Create(LEFT, &g_scene.field, 80);
		ship->controller = GameController_Player_Create(&ship->ship, PAD_INPUT_8, PAD_INPUT_5);
	}

	// シップ2 [↑:↑, ↓:↓]
	{
		GameObjectShip* ship = &g_scene.ship[1];
		*ship = GameObjectShip_Create(RIGHT, &g_scene.field, 80);
		ship->controller = GameController_Player_Create(&ship->ship, PAD_INPUT_UP, PAD_INPUT_DOWN);
	}

	//*
	// シップ3 [↑:A, ↓:Z] (追加シップ) ※GameScene.h->NUM_SHIPを変更する必要あり
	{
		GameObjectShip* ship = &g_scene.ship[2];
		*ship = GameObjectShip_Create(LEFT, &g_scene.field, 120);
		ship->controller = GameController_Player_Create(&ship->ship, PAD_INPUT_4, PAD_INPUT_1);
	}
	/**/

	// リソース
	g_resources = GameResource_Create();

	// シップサウンド
	g_ship1_sound = GameSoundShip_Create(&g_scene, LEFT, g_resources.sound_se02, SOUND_SHIP1_INTERVAL);
	g_ship2_sound = GameSoundShip_Create(&g_scene, RIGHT, g_resources.sound_se03, SOUND_SHIP2_INTERVAL);

	// タイマー
	g_scene.timer = GameTimer_Create();
	GameTimer_SetRemainingDefault(&g_scene.timer);

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
			GameTimer_Resume(&g_scene.timer);

			// 点数リセット
			GameScore_Clear(&g_scene.score);

			// シップを初期位置へ
			{
				int i;
				for (i = 0; i < NUM_SHIP; i++)
					GameObjectShip_Reset(&g_scene.ship[i]);
			}

			// サウンド再生
			GameSoundShip_Start(&g_ship1_sound);
			GameSoundShip_Start(&g_ship2_sound);

			// シーンをプレイに変更
			g_scene.game_state = STATE_PLAY;
		}
	}

	// コントローラー更新
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			GameController_Update(&g_scene.ship[i].controller);
	}

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
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			GameController_Update(&g_scene.ship[i].controller);
	}

	// シップ更新
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			GameObjectShip_Update(&g_scene.ship[i]);
	}

	// 操作
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			if (GameObjectShip_IsAvailable(&g_scene.ship[i]))
				GameController_UpdateControl(&g_scene.ship[i].controller);
	}

	// 座標更新
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
			GameObject_UpdatePosition(&g_scene.bullet[i]);
	}
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			GameObject_UpdatePosition(&g_scene.ship[i].ship);
	}

	// サウンド更新
	GameSoundShip_Update(&g_ship1_sound);
	GameSoundShip_Update(&g_ship2_sound);

	// 当たり判定
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
		{
			GameObject_Field_CollisionHorizontal(&g_scene.field, &g_scene.bullet[i], CONNECTION_LOOP, EDGESIDE_OUTER);

			{
				int j;
				for (j = 0; j < NUM_SHIP; j++)
					if (GameObject_IsHit(&g_scene.ship[j].ship, &g_scene.bullet[i]))
					{
						GameObjectShip_Kill(&g_scene.ship[j]);
						PlaySoundMem(g_resources.sound_se01, DX_PLAYTYPE_BACK);
					}
			}
		}
	}
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			GameObjectShip_CollisionScore(&g_scene.ship[i], &g_scene.score);
	}

	// 終了判定
	if (GameTimer_IsFinished(&g_scene.timer))
	{
		// タイマー停止初期化
		GameTimer_Pause(&g_scene.timer);
		GameTimer_SetRemainingDefault(&g_scene.timer);

		// サウンド停止
		GameSoundShip_Stop(&g_ship1_sound);
		GameSoundShip_Stop(&g_ship2_sound);

		// シーンをデモに変更
		g_scene.game_state = STATE_DEMO;
	}
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
			GameObject_Render(&g_scene.bullet[i]);
	}
	// タイム描画
	GameTimer_Render(&g_scene.timer, &g_scene.field, &g_resources);
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
	{
		int i;
		for (i = 0; i < NUM_SHIP; i++)
			GameObjectShip_Render(&g_scene.ship[i], &g_scene.field);
	}
	// 弾描画
	{
		int i;
		for (i = 0; i < NUM_BULLET; i++)
			GameObject_Render(&g_scene.bullet[i]);
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
