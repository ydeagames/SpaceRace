#include "GameTimerBar.h"
#include "GameUtils.h"

// 関数の宣言 ==============================================================

// <<タイマーバー>> ----------------------------------------------------

// <タイマーバー作成>
GameTimerBar GameTimerBar_Create(GameObject* field, GameSprite sprite)
{
	return { GameTimer_Create(), field, sprite };
}

// <タイマーバー描画>
void GameTimerBar_Render(GameTimerBar* bar)
{
	// 下からの長さを計算
	float length = GetPercentValueRange(GetPercentage(GameTimer_GetTimeRemaining(&bar->timer), GAME_DURATION_SECONDS), GameObject_GetY(bar->field, TOP), GameObject_GetY(bar->field, BOTTOM));
	{
		// バーの表示
		GameObject timebar = *bar->field;
		timebar.size.x = 6;
		timebar.size.y = length;
		timebar.pos.y = bar->field->pos.y + (bar->field->size.y - length) / 2;
		GameObject_Render(&timebar);

		{
			// 旗の表示
			GameObject timebanner = GameObject_Create();
			timebanner.sprite = bar->banner;
			timebanner.pos.x = timebar.pos.x;
			timebanner.pos.y = GameObject_GetY(&timebar, TOP);
			GameObject_Render(&timebanner);
		}
	}
}
