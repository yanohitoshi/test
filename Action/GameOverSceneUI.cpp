#include "GameOverSceneUI.h"
#include "Renderer.h"
#include "SpriteComponent.h"

GameOverSceneUI::GameOverSceneUI()
	: GameObject(false, UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// spriteComponentをnew
	sprite = new SpriteComponent(this, false);
	// ゲームオーバーのtextureをロード
	Texture* tex = RENDERER->GetTexture("Assets/sprite/GameOver.png");
	// textureをComponentにセット
	sprite->SetTexture(tex);
	// alpha値を初期化
	sprite->SetAlpha(1.0f);

}

GameOverSceneUI::~GameOverSceneUI()
{
}

void GameOverSceneUI::UpdateGameObject(float _deltaTime)
{
}
