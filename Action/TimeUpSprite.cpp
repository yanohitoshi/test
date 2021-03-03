#include "TimeUpSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

bool TimeUpSprite::drawFlag = true;

TimeUpSprite::TimeUpSprite()
	:GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// SpriteComponent初期化
	sprite = new SpriteComponent(this, false);
	Texture* tex = RENDERER->GetTexture("Assets/sprite/timeup.png");
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// メンバー変数初期化
	frameCount = 0;
	visibleFlag = true;

}

TimeUpSprite::~TimeUpSprite()
{
	// 静的変数初期化
	drawFlag = true;
}

void TimeUpSprite::UpdateGameObject(float _deltaTime)
{
	// タイムオーバーかつ1度だけ描画フラグがtrueだったら
	if (CountDownFont::timeOverFlag == true && visibleFlag == true)
	{
		// フレームカウント計測
		++frameCount;
		// 描画する
		sprite->SetVisible(true);
		// フレームカウントが120を超えたら
		if (frameCount >= 120)
		{
			//　1度だけ描画フラグをfalseに
			visibleFlag = false;
			// 描画を切る
			sprite->SetVisible(false);
			// 描画されているかフラグをfalseに
			drawFlag = false;
		}
	}
}
