#include "TimeSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

TimeSprite::TimeSprite()
	:GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(700.0f, 480.0f, 0.0f));
	// SpriteComponent初期化
	sprite = new SpriteComponent(this, false);
	tex = RENDERER->GetTexture("Assets/sprite/Time_UI.png");
	sprite->SetTexture(tex);
	sprite->SetAlpha(1.0f);
	// メンバー変数初期化
	frameCount = 0;
}

TimeSprite::~TimeSprite()
{
}

void TimeSprite::UpdateGameObject(float _deltaTime)
{
	// タイムオーバーになったら描画を切る
	if (CountDownFont::timeOverFlag == true)
	{
		sprite->SetVisible(false);
	}
}
