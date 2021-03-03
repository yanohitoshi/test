#include "ContinueSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"
#include "TimeUpSprite.h"

// 静的メンバー初期化
bool ContinueSprite::drawFlag = true;
bool ContinueSprite::continueFlag = true;

ContinueSprite::ContinueSprite()
	:GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// textureをロード
	Texture* tex = RENDERER->GetTexture("Assets/sprite/continue.png");
	// SpriteComponentを初期化
	sprite = new SpriteComponent(this,false);
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// メンバー変数初期化
	frameCount = 0;
	visibleFlag = true;
}

ContinueSprite::~ContinueSprite()
{
	// 静的メンバー初期化
	drawFlag = true;
	continueFlag = true;
}

void ContinueSprite::UpdateGameObject(float _deltaTime)
{
	// タイムアップ状態中タイムアップ画像の描画が終わったら描画する
	if (TimeUpSprite::GetDrawFlag() == false && visibleFlag == true)
	{
		sprite->SetVisible(true);
		++frameCount;
	}
}

void ContinueSprite::GameObjectInput(const InputState& _keyState)
{
	// タイムアップ画像の描画が終わってコンテニュー画像描画開始から一定時間たっていたら
	if (TimeUpSprite::GetDrawFlag() == false && frameCount >= 60)
	{
		// Aボタンが押されたら
		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed )
		{
			// 描画を切ってコンテニューフラグをtrueに
			sprite->SetVisible(false);
			visibleFlag = false;
			drawFlag = false;
			continueFlag = true;
		}
		else if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed) // Bボタンが押されたら
		{
			// 描画を切ってコンテニューフラグをfalseに
			sprite->SetVisible(false);
			visibleFlag = false;
			drawFlag = false;
			continueFlag = false;
		}
	}
}
