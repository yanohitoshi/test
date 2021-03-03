#include "FinalStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"
#include "TimeUpSprite.h"
#include "ContinueSprite.h"
#include "GameOverSprite.h"
#include "GameClearSprite.h"

// 静的メンバー初期化
bool FinalStageUI::timeOverFlag = false;
bool FinalStageUI::countStartFlag = false;

FinalStageUI::FinalStageUI()
	: GameObject(false, Tag::UI)
{
	// カウントダウン
	new CountDownFont(150);
	// start時のカウントダウン
	new StartCountDownSprite();
	// タイムアップ時のsprite
	new TimeUpSprite();
	// コンティニュー選択時のsprite
	new ContinueSprite();
	// GameOver時のsprite
	new GameOverSprite();
	// GameClear時のsprite
	new GameClearSprite();

}

FinalStageUI::~FinalStageUI()
{
	// 静的メンバー初期化
	timeOverFlag = false;
	countStartFlag = false;
}

void FinalStageUI::UpdateGameObject(float _deltaTime)
{
}
