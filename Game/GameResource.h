#pragma once

// 構造体の宣言 ============================================================

// <ゲームリソース>
typedef struct
{
	// <フォント>
	HFNT font_spacerace;
	HFNT font_menu;

	// <サウンド>
	HSND sound_dead;
	HSND sound_ship1;
	HSND sound_ship2;

	// <テクスチャ>
	HGRP texture_spacerace;

	// <動画>
	HGRP movie_logo;
} GameResource;

// 定数の定義 ==============================================================

// <フォント> ----------------------------------------------------------

#define FONT_SIZE_SPACERACE 80			// フォントサイズ
#define FONT_SIZE_MENU 20

// 関数の宣言 ==============================================================

// <<リソース>> --------------------------------------------------

// <リソース作成読み込み>
GameResource GameResource_Create(void);

// <リソース開放>
void GameResource_Delete(GameResource* res);
