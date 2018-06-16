#include "GameResource.h"
#include "GameObject.h"

// 定数の定義 ==============================================================

// <フォント> ----------------------------------------------------------
#define FONT_FILE_SPACERACE_CUSTOM "Resources\\Fonts\\TheSlavicFont-Regular.ttf"
#define FONT_NAME_SPACERACE_CUSTOM "The Slavic Font"
#define FONT_NAME_SPACERACE "HGP創英角ｺﾞｼｯｸUB"
#define FONT_NAME_MENU "HGP創英角ｺﾞｼｯｸUB"
#define FONT_NAME_NOTE "HGS創英ﾌﾟﾚｾﾞﾝｽEB"

// <サウンド> ----------------------------------------------------------
#define SOUND_DEAD "Resources\\Audio\\se_dead.ogg"
#define SOUND_SHIP1 "Resources\\Audio\\se_ship.ogg"
#define SOUND_SHIP2 "Resources\\Audio\\se_ship.ogg"

// <テクスチャ> --------------------------------------------------------
#define TEXTURE_SPACERACE_PROTECTED "Resources\\Textures\\Protected\\SpaceRace.png"
#define TEXTURE_SPACERACE "Resources\\Textures\\Spaceship.png"

// 関数の定義 ==============================================================

// <<リソース>> --------------------------------------------------

// <リソース作成読み込み>
GameResource GameResource_Create(void)
{
	GameResource res;

	// フォント
	if (AddFontResourceEx(FONT_FILE_SPACERACE_CUSTOM, FR_PRIVATE, NULL) > 0)
		res.font_spacerace = CreateFontToHandle(FONT_NAME_SPACERACE_CUSTOM, FONT_SIZE_SPACERACE, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	else
		res.font_spacerace = CreateFontToHandle(FONT_NAME_SPACERACE, FONT_SIZE_SPACERACE, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	res.font_menu = CreateFontToHandle(FONT_NAME_MENU, FONT_SIZE_MENU, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	res.font_note = CreateFontToHandle(FONT_NAME_NOTE, FONT_SIZE_NOTE, 3, DX_FONTTYPE_ANTIALIASING_4X4);

	// サウンド
	res.sound_dead = LoadSoundMem(SOUND_DEAD);
	res.sound_ship1 = LoadSoundMem(SOUND_SHIP1);
	res.sound_ship2 = LoadSoundMem(SOUND_SHIP2);

	// テクスチャ
	res.texture_spacerace = LoadGraph(TEXTURE_SPACERACE_PROTECTED);
	if (res.texture_spacerace == TEXTURE_MISSING)
		res.texture_spacerace = LoadGraph(TEXTURE_SPACERACE);

	return res;
}

// <リソース開放>
void GameResource_Delete(GameResource* res)
{
	// フォント
	DeleteFontToHandle(res->font_spacerace);
	RemoveFontResourceEx(FONT_FILE_SPACERACE_CUSTOM, FR_PRIVATE, NULL);
	DeleteFontToHandle(res->font_menu);
	DeleteFontToHandle(res->font_note);

	// サウンド
	DeleteSoundMem(res->sound_dead);
	DeleteSoundMem(res->sound_ship1);
	DeleteSoundMem(res->sound_ship2);

	// テクスチャ
	DeleteGraph(res->texture_spacerace);
}
