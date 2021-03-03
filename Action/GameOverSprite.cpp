#include "GameOverSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "ContinueSprite.h"

GameOverSprite::GameOverSprite()
	:GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// textureをロード
	Texture* tex = RENDERER->GetTexture("Assets/sprite/gameover3.png");
	// SpriteComponent初期化
	sprite = new SpriteComponent(this,false);
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// メンバー変数初期化
	frameCount = 0;
}

GameOverSprite::~GameOverSprite()
{
}

void GameOverSprite::UpdateGameObject(float _deltaTime)
{
	// コンテニュー選択状態の時コンテニューが選択されなかったら
	if (ContinueSprite::GetDrawFlag() == false && ContinueSprite::GetContinueFlag() == false)
	{
		// フレームカウントを数える
		++frameCount;
		// カウントが60になったら描画する
		if (frameCount >= 60)
		{
			sprite->SetVisible(true);
		}
	}
}
