#include "GameScore.h"

// �֐��̒�` ==============================================================

// <<�X�R�A>> ----------------------------------------------------

// <�X�R�A�쐬>
GameScore GameScore_Create(void)
{
	return { 0, 0 };
}

// <�X�R�A�ǉ�>
void GameScore_Add(GameScore* score, ObjectSide side)
{
	switch (side)
	{
	case LEFT:
		score->score2++;
		break;
	case RIGHT:
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

// <�X�R�A�I������>
BOOL GameScore_IsFinished(GameScore* score)
{
	return score->score1 >= SCORE_GOAL || score->score2 >= SCORE_GOAL;
}

// <�X�R�A�`��>
void GameScore_Render(GameScore* score, GameObject* field, HFNT font)
{
	// �X�R�A�`��

	// �t�H���g���g�p���������̕����擾
	int width_score1 = GetDrawFormatStringWidthToHandle(font, "%2d", score->score1);

	DrawFormatStringToHandle((int)(field->pos.x - 100 - width_score1), (int)(GameObject_GetY(field, TOP, 10)), COLOR_WHITE, font, "%2d", score->score1);
	DrawFormatStringToHandle((int)(field->pos.x + 100), (int)(GameObject_GetY(field, TOP, 10)), COLOR_WHITE, font, "%2d", score->score2);
}