#include "StartCountDownSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

StartCountDownSprite::StartCountDownSprite()
	:GameObject(false, PARTICLE)
{
	// 4���texture�����[�h
	firstTexure = RENDERER->GetTexture("Assets/sprite/CountDown3.png");
	secondTexure = RENDERER->GetTexture("Assets/sprite/CountDown2.png");
	thirdTexure = RENDERER->GetTexture("Assets/sprite/CountDown1.png");
	startTexure = RENDERER->GetTexture("Assets/sprite/Start.png");

	// SpriteComponent��������
	sprite = new SpriteComponent(this, false);
	sprite->SetTexture(firstTexure);
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// �����o�[�ϐ�������
	timeStartCount = 0;
	time = 4;
	texChangeFlag = false;
	drawSpriteFlag = true;
}

StartCountDownSprite::~StartCountDownSprite()
{
}

void StartCountDownSprite::UpdateGameObject(float _deltaTime)
{
	// �`��t���O��true��������
	if (drawSpriteFlag == true)
	{
		// �J�E���g�v��
		++timeStartCount;
		// �J�E���g��60�ȉ���������
		if (timeStartCount >= 60)
		{
			// �`�悷��
			sprite->SetVisible(true);
			// �t���[���J�E���g�����
			frameCount++;
			// 60�t���[���ゲ�Ƃ�texture��؂�ւ���
			if (frameCount >= 60)
			{
				time -= 1;
				frameCount = 0;
				// texture�ύX�t���O��true��
				texChangeFlag = true;
			}
		}
		if (texChangeFlag == true) // texture�ύX�t���O��true��������
		{
			// time�ϐ������Ă���ɉ�����texture���Z�b�g
			if (time == 3)
			{
				sprite->SetTexture(secondTexure);
				texChangeFlag = false;
			}
			
			if (time == 2)
			{
				sprite->SetTexture(thirdTexure);
				texChangeFlag = false;
			}
			
			if (time == 1)
			{
				sprite->SetTexture(startTexure);
				texChangeFlag = false;
			}
			
			// 0�ɂȂ�����`���؂���state��Dead��
			if (time == 0)
			{
				sprite->SetVisible(false);
				drawSpriteFlag = false;
				CountDownFont::countStartFlag = true;
				state = State::Dead;
			}
		}
	}
}
