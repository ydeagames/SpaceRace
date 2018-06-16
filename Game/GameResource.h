#pragma once

// 構造体の宣言 ============================================================

// <ゲームリソース>
typedef struct
{
	// <フォント>
	HFNT font_spacerace;

	// <サウンド>
	HSND sound_dead;
	HSND sound_ship1;
	HSND sound_ship2;

	// <テクスチャ>
	HGRP texture_spacerace;
} GameResource;

// 定数の定義 ==============================================================

// <フォント> ----------------------------------------------------------

#define FONT_SIZE_SPACERACE 80			// フォントサイズ

// 関数の宣言 ==============================================================

// <<リソース>> --------------------------------------------------

// <リソース作成読み込み>
GameResource GameResource_Create(void);

// <リソース開放>
void GameResource_Delete(GameResource* res);
