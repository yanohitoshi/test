#include "StartCountDownSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

StartCountDownSprite::StartCountDownSprite()
	:GameObject(false, PARTICLE)
{
	// 4種のtextureをロード
	firstTexure = RENDERER->GetTexture("Assets/sprite/CountDown3.png");
	secondTexure = RENDERER->GetTexture("Assets/sprite/CountDown2.png");
	thirdTexure = RENDERER->GetTexture("Assets/sprite/CountDown1.png");
	startTexure = RENDERER->GetTexture("Assets/sprite/Start.png");

	// SpriteComponentを初期化
	sprite = new SpriteComponent(this, false);
	sprite->SetTexture(firstTexure);
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// メンバー変数初期化
	timeStartCount = 0;
	time = 4;
	texChangeFlag = false;
	drawSpriteFlag = true;
}

StartCountDownSprite::~StartCountDownSprite()
{
}

void StartCountDownSprite::UpdateGameObject(float _deltaTime)
{
	// 描画フラグがtrueだったら
	if (drawSpriteFlag == true)
	{
		// カウント計測
		++timeStartCount;
		// カウントが60以下だったら
		if (timeStartCount >= 60)
		{
			// 描画する
			sprite->SetVisible(true);
			// フレームカウントを取る
			frameCount++;
			// 60フレーム後ごとにtextureを切り替える
			if (frameCount >= 60)
			{
				time -= 1;
				frameCount = 0;
				// texture変更フラグをtrueに
				texChangeFlag = true;
			}
		}
		if (texChangeFlag == true) // texture変更フラグがtrueだったら
		{
			// time変数を見てそれに応じたtextureをセット
			if (time == 3)
			{
				sprite->SetTexture(secondTexure);
				texChangeFlag = false;
			}
			
			if (time == 2)
			{
				sprite->SetTexture(thirdTexure);
				texChangeFlag = false;
			}
			
			if (time == 1)
			{
				sprite->SetTexture(startTexure);
				texChangeFlag = false;
			}
			
			// 0になったら描画を切ってstateをDeadに
			if (time == 0)
			{
				sprite->SetVisible(false);
				drawSpriteFlag = false;
				CountDownFont::countStartFlag = true;
				state = State::Dead;
			}
		}
	}
}
