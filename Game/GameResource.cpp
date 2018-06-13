#include "GameResource.h"

// �萔�̒�` ==============================================================

// <�t�H���g> ----------------------------------------------------------
#define FONT_FILE_PONG_CUSTOM "Resources\\Fonts\\TheSlavicFont-Regular.ttf"
#define FONT_NAME_PONG_CUSTOM "The Slavic Font"
#define FONT_NAME_PONG "HGP�n�p�p�޼��UB"
#define FONT_NAME_MENU "HGP�n�p�p�޼��UB"
#define FONT_NAME_NOTE "HGS�n�p��ھ�ݽEB"

// <�T�E���h> ----------------------------------------------------------
#define SOUND_SE01 "Resources\\Audio\\SE01.ogg"
#define SOUND_SE02 "Resources\\Audio\\SE02.ogg"
#define SOUND_SE03 "Resources\\Audio\\SE03.ogg"

// �֐��̒�` ==============================================================

// <<���\�[�X>> --------------------------------------------------

// <���\�[�X�쐬�ǂݍ���>
GameResource GameResource_Create(void)
{
	GameResource res;

	// �t�H���g
	if (AddFontResourceEx(FONT_FILE_PONG_CUSTOM, FR_PRIVATE, NULL) > 0)
		res.font_pong = CreateFontToHandle(FONT_NAME_PONG_CUSTOM, FONT_SIZE_PONG, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	else
		res.font_pong = CreateFontToHandle(FONT_NAME_PONG, FONT_SIZE_PONG, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	res.font_menu = CreateFontToHandle(FONT_NAME_MENU, FONT_SIZE_MENU, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	res.font_note = CreateFontToHandle(FONT_NAME_NOTE, FONT_SIZE_NOTE, 3, DX_FONTTYPE_ANTIALIASING_4X4);

	// �T�E���h
	res.sound_se01 = LoadSoundMem(SOUND_SE01);
	res.sound_se02 = LoadSoundMem(SOUND_SE02);
	res.sound_se03 = LoadSoundMem(SOUND_SE03);

	return res;
}

// <���\�[�X�J��>
void GameResource_Delete(GameResource* res)
{
	// �t�H���g
	DeleteFontToHandle(res->font_pong);
	RemoveFontResourceEx(FONT_FILE_PONG_CUSTOM, FR_PRIVATE, NULL);
	DeleteFontToHandle(res->font_menu);
	DeleteFontToHandle(res->font_note);

	// �T�E���h
	DeleteSoundMem(res->sound_se01);
	DeleteSoundMem(res->sound_se02);
	DeleteSoundMem(res->sound_se03);
}
