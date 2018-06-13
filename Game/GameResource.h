#pragma once

// �\���̂̐錾 ============================================================

// <�Q�[�����\�[�X>
typedef struct
{
	// <�t�H���g>
	HFNT font_pong;
	HFNT font_menu;
	HFNT font_note;

	// <�T�E���h>
	HSND sound_se01;
	HSND sound_se02;
	HSND sound_se03;
} GameResource;

// �萔�̒�` ==============================================================

// <�t�H���g> ----------------------------------------------------------

#define FONT_SIZE_PONG 100
#define FONT_SIZE_MENU 20
#define FONT_SIZE_NOTE 12

// �֐��̐錾 ==============================================================

// <<���\�[�X>> --------------------------------------------------

// <���\�[�X�쐬�ǂݍ���>
GameResource GameResource_Create(void);

// <���\�[�X�J��>
void GameResource_Delete(GameResource* res);
