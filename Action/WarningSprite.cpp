#include "WarningSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

WarningSprite::WarningSprite(CountDownFont* _owner)
	:GameObject(false, Tag::UI)
{
	// 変数の初期化
	owner = _owner;
	alpha = 0.1f;
	count = 0;
	fadeFlag = true;
	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// SpriteComponentの初期化
	sprite = new SpriteComponent(this, false);
	Texture* tex = RENDERER->GetTexture("Assets/sprite/warning2.png");
	sprite->SetTexture(tex);
	sprite->SetVisible(true);
	sprite->SetAlpha(alpha);
}

WarningSprite::~WarningSprite()
{
}

void WarningSprite::UpdateGameObject(float _deltaTime)
{
	// countが2以下かつownerのフラグがtrueの時
	if (count <= 2 && owner->GetWarningFlag() == true)
	{
		// fadeFlagがtrueだったらfadein
		if (fadeFlag == true)
		{
			alpha += 0.01f;
		}
		else if (fadeFlag == false)		// fadeFlagがfalseだったらfadeout
		{
			alpha -= 0.01f;
		}

		// alpha値を見てin/outを切り替え
		if (alpha <= 0.1)
		{
			fadeFlag = true;
		}
		else if (alpha >= 0.9)
		{
			fadeFlag = false;
		}
	}
	else if (count >= 3)	// countが3以上になったらalpha値が0になるまでout
	{
		if (alpha >= 0.0f)
		{
			alpha -= 0.01f;
		}
	}
	// fadein/outが終わるごとにカウントを追加
	if (fadeFlag == false && alpha <= 0.1f)
	{
		++count;
	}
	// alpha値をセット
	sprite->SetAlpha(alpha);
}
