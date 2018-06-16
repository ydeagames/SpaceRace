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
	HSND sound_dead;
	HSND sound_ship1;
	HSND sound_ship2;

	// <�e�N�X�`��>
	HGRP texture_ship;
} GameResource;

// �萔�̒�` ==============================================================

// <�t�H���g> ----------------------------------------------------------

#define FONT_SIZE_PONG 80
#define FONT_SIZE_MENU 20
#define FONT_SIZE_NOTE 12

// �֐��̐錾 ==============================================================

// <<���\�[�X>> --------------------------------------------------

// <���\�[�X�쐬�ǂݍ���>
GameResource GameResource_Create(void);

// <���\�[�X�J��>
void GameResource_Delete(GameResource* res);
