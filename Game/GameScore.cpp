#include "GameScore.h"
#include "GameResource.h"

// �֐��̒�` ==============================================================

// <<�X�R�A>> ----------------------------------------------------

// <�X�R�A�쐬>
GameScore GameScore_Create(void)
{
	return { 0, 0 };
}

// <�X�R�A�ǉ�>
void GameScore_Add(GameScore* score, ObjectSide team)
{
	// �`�[���ɂ���ĉ��_
	switch (team)
	{
	case RIGHT:
		score->score2++;
		break;
	case LEFT:
		score->score1++;
		break;
	}
}

// <�X�R�A���Z�b�g>
void GameScore_Clear(GameScore* score)
{
	score->score1 = 0;
	score->score2 = 0;
}

// <�X�R�A�`��>
void GameScore_Render(GameScore* score, GameObject* field, GameResource* resources)
{
	// �X�R�A�`��

	// �t�H���g���g�p���������̕����擾
	int width_score1 = GetDrawFormatStringWidthToHandle(resources->font_spacerace, "%2d", score->score1);

	// �X�R�A�`��
	DrawFormatStringToHandle((int)(GameObject_GetX(field, CENTER_X) - (100 + width_score1)), (int)GameObject_GetY(field, BOTTOM, -FONT_SIZE_SPACERACE - 10), COLOR_WHITE, resources->font_spacerace, "%2d", score->score1);
	DrawFormatStringToHandle((int)(GameObject_GetX(field, CENTER_X) + 100), (int)GameObject_GetY(field, BOTTOM, -FONT_SIZE_SPACERACE - 10), COLOR_WHITE, resources->font_spacerace, "%2d", score->score2);
}