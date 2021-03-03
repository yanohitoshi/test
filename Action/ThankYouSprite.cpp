#include "ThankYouSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"

ThankYouSprite::ThankYouSprite()
	:GameObject(false, Tag::UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// SpriteComponent��������
	sprite = new SpriteComponent(this, false);
	Texture* tex = RENDERER->GetTexture("Assets/sprite/Thankyou.png");
	sprite->SetTexture(tex);
	sprite->SetVisible(true);
	sprite->SetAlpha(1.0f);
	// �����o�[�ϐ�������
	frameCount = 0;
}

ThankYouSprite::~ThankYouSprite()
{
}

void ThankYouSprite::UpdateGameObject(float _deltaTime)
{

}
