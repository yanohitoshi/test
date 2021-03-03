#include "CountDownBackFont.h"
#include "Renderer.h"
#include "Font.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

CountDownBackFont::CountDownBackFont(int _time)
	: GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(695.0f, 480.0f, 0.0f));
	//  SpriteComponent初期化
	sprite = new SpriteComponent(this,false ,105);
	sprite->SetAlpha(1.0f);
	// メンバー変数初期化
	time = _time;

}

CountDownBackFont::~CountDownBackFont()
{
}

void CountDownBackFont::UpdateGameObject(float _deltaTime)
{
	// ゲームスタートしたらカウント開始
	if (CountDownFont::countStartFlag == true)
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

	// 1以上の時は黒色で描画
	if (time >= 1)
	{
		sprite->SetTexture(RENDERER->GetTimeBlackTexture(time - 1));
	}
	// textureを先に作ってvector配列に格納している都合上0を描画するときnullにアクセスしてしまうのを回避
	if (time == 0)
	{
		sprite->SetTexture(RENDERER->GetTimeBlackTexture(-1));
	}

	// timeが-1以下になったらタイムオーバーにする
	if (time <= -1)
	{
		sprite->SetVisible(false);
	}

}
