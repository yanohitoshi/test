#include "TitleBackGroundSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"

TitleBackGroundSprite::TitleBackGroundSprite()
	:GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// spriteComponenをnewする
	sprite = new SpriteComponent(this, true);
	// 背景テクスチャをロード
	Texture* tex = RENDERER->GetTexture("Assets/sprite/BackGround_SP/TitleBackGround_1.png");
	// 背景テクスチャをセット
	sprite->SetTexture(tex);
	// 映す映さないをセット
	sprite->SetVisible(true);
	// alpha値をセット
	sprite->SetAlpha(1.0f);

}

TitleBackGroundSprite::~TitleBackGroundSprite()
{
}

void TitleBackGroundSprite::UpdateGameObject(float _deltaTime)
{

}
