#include "TimeSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

TimeSprite::TimeSprite()
	:GameObject(false, Tag::UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(700.0f, 480.0f, 0.0f));
	// SpriteComponent������
	sprite = new SpriteComponent(this, false);
	tex = RENDERER->GetTexture("Assets/sprite/Time_UI.png");
	sprite->SetTexture(tex);
	sprite->SetAlpha(1.0f);
	// �����o�[�ϐ�������
	frameCount = 0;
}

TimeSprite::~TimeSprite()
{
}

void TimeSprite::UpdateGameObject(float _deltaTime)
{
	// �^�C���I�[�o�[�ɂȂ�����`���؂�
	if (CountDownFont::timeOverFlag == true)
	{
		sprite->SetVisible(false);
	}
}
