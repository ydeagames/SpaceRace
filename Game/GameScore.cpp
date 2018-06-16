#include "GameScore.h"
#include "GameResource.h"

// 関数の定義 ==============================================================

// <<スコア>> ----------------------------------------------------

// <スコア作成>
GameScore GameScore_Create(void)
{
	return { 0, 0 };
}

// <スコア追加>
void GameScore_Add(GameScore* score, ObjectSide team)
{
	// チームによって加点
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

// <スコアリセット>
void GameScore_Clear(GameScore* score)
{
	score->score1 = 0;
	score->score2 = 0;
}

// <スコア描画>
void GameScore_Render(GameScore* score, GameObject* field, GameResource* resources)
{
	// スコア描画

	// フォントを使用した文字の幅を取得
	int width_score1 = GetDrawFormatStringWidthToHandle(resources->font_spacerace, "%2d", score->score1);

	// スコア描画
	DrawFormatStringToHandle((int)(GameObject_GetX(field, CENTER_X) - (100 + width_score1)), (int)GameObject_GetY(field, BOTTOM, -FONT_SIZE_SPACERACE - 10), COLOR_WHITE, resources->font_spacerace, "%2d", score->score1);
	DrawFormatStringToHandle((int)(GameObject_GetX(field, CENTER_X) + 100), (int)GameObject_GetY(field, BOTTOM, -FONT_SIZE_SPACERACE - 10), COLOR_WHITE, resources->font_spacerace, "%2d", score->score2);
}