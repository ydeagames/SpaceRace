#pragma once

// 構造体の宣言 ============================================================

// <ゲームリソース>
typedef struct
{
	// <フォント>
	HFNT font_pong;
	HFNT font_menu;
	HFNT font_note;

	// <サウンド>
	HSND sound_dead;
	HSND sound_ship1;
	HSND sound_ship2;

	// <テクスチャ>
	HGRP texture_ship;
} GameResource;

// 定数の定義 ==============================================================

// <フォント> ----------------------------------------------------------

#define FONT_SIZE_PONG 80
#define FONT_SIZE_MENU 20
#define FONT_SIZE_NOTE 12

// 関数の宣言 ==============================================================

// <<リソース>> --------------------------------------------------

// <リソース作成読み込み>
GameResource GameResource_Create(void);

// <リソース開放>
void GameResource_Delete(GameResource* res);
