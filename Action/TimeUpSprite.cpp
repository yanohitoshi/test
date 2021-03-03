#include "TimeUpSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

bool TimeUpSprite::drawFlag = true;

TimeUpSprite::TimeUpSprite()
	:GameObject(false, Tag::UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// SpriteComponent������
	sprite = new SpriteComponent(this, false);
	Texture* tex = RENDERER->GetTexture("Assets/sprite/timeup.png");
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// �����o�[�ϐ�������
	frameCount = 0;
	visibleFlag = true;

}

TimeUpSprite::~TimeUpSprite()
{
	// �ÓI�ϐ�������
	drawFlag = true;
}

void TimeUpSprite::UpdateGameObject(float _deltaTime)
{
	// �^�C���I�[�o�[����1�x�����`��t���O��true��������
	if (CountDownFont::timeOverFlag == true && visibleFlag == true)
	{
		// �t���[���J�E���g�v��
		++frameCount;
		// �`�悷��
		sprite->SetVisible(true);
		// �t���[���J�E���g��120�𒴂�����
		if (frameCount >= 120)
		{
			//�@1�x�����`��t���O��false��
			visibleFlag = false;
			// �`���؂�
			sprite->SetVisible(false);
			// �`�悳��Ă��邩�t���O��false��
			drawFlag = false;
		}
	}
}
