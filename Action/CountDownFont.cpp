#include "CountDownFont.h"
#include "Renderer.h"
#include "TimeSprite.h"
#include "SpriteComponent.h"
#include "CountDownBackFont.h"
#include "WarningSprite.h"

// 静的メンバーの初期化
bool CountDownFont::timeOverFlag = false;
bool CountDownFont::countStartFlag = false;

CountDownFont::CountDownFont(int _time)
	: GameObject(false,Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(700.0f, 480.0f, 0.0f));
	// SpriteComponentの初期化
	sprite = new SpriteComponent(this,false,110);
	sprite->SetAlpha(1.0f);
	// メンバー変数の初期化
	time = _time;
	warningFlag = false;

	new CountDownBackFont(_time);
	new TimeSprite();
	new WarningSprite(this);

}

CountDownFont::~CountDownFont()
{
	// 静的メンバーの初期化
	timeOverFlag = false;
	countStartFlag = false;
}

void CountDownFont::UpdateGameObject(float _deltaTime)
{
	// ゲームスタートしたらカウント開始
	if (countStartFlag == true)
	{
		// フレームカウントを数える
		frameCount++;
		// 60になったら
		if (frameCount >= 60)
		{
			// timeを減らす
			time -= 1;
			frameCount = 0;
		}
	}

	// 30以上の時は白色で描画
	if (time > 30)
	{
		sprite->SetTexture(RENDERER->GetTimeTexture(time - 1));
	}
	else if (time <= 30 && time >= 1)	// 30以下の時は白色で描画
	{
		// 警告フラグをtrueに
		warningFlag = true;
		sprite->SetTexture(RENDERER->GetTimeRedTexture(time - 1));
	}
	// textureを先に作ってvector配列に格納している都合上0を描画するときnullにアクセスしてしまうのを回避
	if (time == 0)
	{
		sprite->SetTexture(RENDERER->GetTimeRedTexture(-1));
	}

	// timeが-1以下になったらタイムオーバーにする
	if (time <= -1)
	{
		timeOverFlag = true;
		sprite->SetVisible(false);
	}
}
