#include "SecondStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"
#include "TimeUpSprite.h"
#include "ContinueSprite.h"
#include "GameOverSprite.h"

// 静的メンバー初期化
bool SecondStageUI::timeOverFlag = false;
bool SecondStageUI::countStartFlag = false;

SecondStageUI::SecondStageUI()
	: GameObject(false, Tag::UI)
{
	// カウントダウン
	new CountDownFont(90);
	// start時のカウントダウン
	new StartCountDownSprite();
	// タイムアップ時のsprite
	new TimeUpSprite();
	// コンティニュー選択時のsprite
	new ContinueSprite();
	// GameOver時のsprite
	new GameOverSprite();
}

SecondStageUI::~SecondStageUI()
{
	// 静的メンバー初期化
	timeOverFlag = false;
	countStartFlag = false;
}

void SecondStageUI::UpdateGameObject(float _deltaTime)
{
}
