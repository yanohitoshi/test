#include "ClearSceneUI.h"
#include "Renderer.h"
#include "SpriteComponent.h"

ClearSceneUI::ClearSceneUI()
	: GameObject(false,UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// spriteComponentをnewセット
	sprite = new SpriteComponent(this, false);
	// タイトルのtextureをロード
	Texture* tex = RENDERER->GetTexture("Assets/sprite/GameClear.png");
	// textureをComponentにセット
	sprite->SetTexture(tex);
	// alpha値を初期化
	sprite->SetAlpha(1.0f);

}

ClearSceneUI::~ClearSceneUI()
{
}

void ClearSceneUI::UpdateGameObject(float _deltaTime)
{
}
