#include "FirstStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"


FirstStageUI::FirstStageUI()
	: GameObject(false, Tag::UI)
{
	// ジャンプチュートリアル用Particl
	new JumpTutorialParticl(Vector3(3700.0f, -1000.0f, 700.0f));
	// 移動チュートリアル用Particl
	new MoveTutorialParticl(Vector3(3700.0f, -2200.0f, 700.0f));

	// プレイヤーを動かすことができるようにするためのフラグ
	CountDownFont::countStartFlag = true;

}

FirstStageUI::~FirstStageUI()
{
	// プレイヤーを動かすことができるようにするためのフラグの初期化
	CountDownFont::countStartFlag = false;
}

void FirstStageUI::UpdateGameObject(float _deltaTime)
{
}
