#pragma once

// �\���̂̐錾 ============================================================

// <�Q�[�����\�[�X>
typedef struct
{
	// <�t�H���g>
	HFNT font_spacerace;
	HFNT font_menu;

	// <�T�E���h>
	HSND sound_dead;
	HSND sound_ship1;
	HSND sound_ship2;

	// <�e�N�X�`��>
	HGRP texture_spacerace;

	// <����>
	HGRP movie_logo;
} GameResource;

// �萔�̒�` ==============================================================

// <�t�H���g> ----------------------------------------------------------

#define FONT_SIZE_SPACERACE 80			// �t�H���g�T�C�Y
#define FONT_SIZE_MENU 20

// �֐��̐錾 ==============================================================

// <<���\�[�X>> --------------------------------------------------

// <���\�[�X�쐬�ǂݍ���>
GameResource GameResource_Create(void);

// <���\�[�X�J��>
void GameResource_Delete(GameResource* res);
