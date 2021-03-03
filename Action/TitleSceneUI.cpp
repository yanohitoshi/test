#include "TitleSceneUI.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "TitleBackGroundSprite.h"

TitleSceneUI::TitleSceneUI()
	: GameObject(false,UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// spriteComponentをnewする
	sprite = new SpriteComponent(this, false);
	// タイトルのtextureをロード
	Texture* tex = RENDERER->GetTexture("Assets/sprite/Title.png");
	// textureをComponentにセット
	sprite->SetTexture(tex);
	// alpha値を初期化
	sprite->SetAlpha(1.0f);
	// タイトルの背景クラスをnew
	new TitleBackGroundSprite();
}

TitleSceneUI::~TitleSceneUI()
{
}

void TitleSceneUI::UpdateGameObject(float _deltaTime)
{
}
