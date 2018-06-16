#include "GameResource.h"
#include "GameObject.h"

// �萔�̒�` ==============================================================

// <�t�H���g> ----------------------------------------------------------
#define FONT_FILE_SPACERACE_CUSTOM "Resources\\Fonts\\TheSlavicFont-Regular.ttf"		// �J�X�^���t�H���g�t�@�C��
#define FONT_NAME_SPACERACE_CUSTOM "The Slavic Font"									// �J�X�^���t�H���g�l�[��
#define FONT_NAME_SPACERACE "HGP�n�p�p�޼��UB"											// �t�H�[���o�b�N�p�t�H���g�l�[��

// <�T�E���h> ----------------------------------------------------------
#define SOUND_DEAD "Resources\\Audio\\se_dead.ogg"										// �V�b�v���SSE
#define SOUND_SHIP1 "Resources\\Audio\\se_ship.ogg"										// �V�b�v1SE
#define SOUND_SHIP2 "Resources\\Audio\\se_ship.ogg"										// �V�b�v2SE

// <�e�N�X�`��> --------------------------------------------------------
#define TEXTURE_SPACERACE_PROTECTED "Resources\\Textures\\Protected\\SpaceRace.png"		// ���\�[�X�ی�e�N�X�`��
#define TEXTURE_SPACERACE "Resources\\Textures\\SpaceRace.png"							// �I�[�v���e�N�X�`��

// �֐��̒�` ==============================================================

// <<���\�[�X>> --------------------------------------------------

// <���\�[�X�쐬�ǂݍ���>
GameResource GameResource_Create(void)
{
	GameResource res;

	// �t�H���g
	// �J�X�^���t�H���g�t�@�C�����ǂݍ��߂���g��
	if (AddFontResourceEx(FONT_FILE_SPACERACE_CUSTOM, FR_PRIVATE, NULL) > 0)
		res.font_spacerace = CreateFontToHandle(FONT_NAME_SPACERACE_CUSTOM, FONT_SIZE_SPACERACE, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	else
		res.font_spacerace = CreateFontToHandle(FONT_NAME_SPACERACE, FONT_SIZE_SPACERACE, 3, DX_FONTTYPE_ANTIALIASING_4X4);

	// �T�E���h
	res.sound_dead = LoadSoundMem(SOUND_DEAD);
	res.sound_ship1 = LoadSoundMem(SOUND_SHIP1);
	res.sound_ship2 = LoadSoundMem(SOUND_SHIP2);

	// �e�N�X�`��
	res.texture_spacerace = LoadGraph(TEXTURE_SPACERACE_PROTECTED);
	if (res.texture_spacerace == TEXTURE_MISSING)										// ���\�[�X�ی�e�N�X�`��������������
		res.texture_spacerace = LoadGraph(TEXTURE_SPACERACE);							// �I�[�v���e�N�X�`����ǂݍ���

	return res;
}

// <���\�[�X�J��>
void GameResource_Delete(GameResource* res)
{
	// �t�H���g
	DeleteFontToHandle(res->font_spacerace);
	RemoveFontResourceEx(FONT_FILE_SPACERACE_CUSTOM, FR_PRIVATE, NULL);

	// �T�E���h
	DeleteSoundMem(res->sound_dead);
	DeleteSoundMem(res->sound_ship1);
	DeleteSoundMem(res->sound_ship2);

	// �e�N�X�`��
	DeleteGraph(res->texture_spacerace);
}
