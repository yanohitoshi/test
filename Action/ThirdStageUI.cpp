#include "ThirdStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"
#include "TimeUpSprite.h"
#include "ContinueSprite.h"
#include "GameOverSprite.h"

// 静的メンバー初期化
bool ThirdStageUI::timeOverFlag = false;
bool ThirdStageUI::countStartFlag = false;

ThirdStageUI::ThirdStageUI()
	: GameObject(false, Tag::UI)
{
	// カウントダウン
	new CountDownFont(120);
	// start時のカウントダウン
	new StartCountDownSprite();
	// タイムアップ時のsprite
	new TimeUpSprite();
	// コンティニュー選択時のsprite
	new ContinueSprite();
	// GameOver時のsprite
	new GameOverSprite();

}

ThirdStageUI::~ThirdStageUI()
{
	// 静的メンバー初期化
	timeOverFlag = false;
	countStartFlag = false;
}

void ThirdStageUI::UpdateGameObject(float _deltaTime)
{
}
