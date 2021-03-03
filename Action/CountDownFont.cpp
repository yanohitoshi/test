#include "CountDownFont.h"
#include "Renderer.h"
#include "TimeSprite.h"
#include "SpriteComponent.h"
#include "CountDownBackFont.h"
#include "WarningSprite.h"

// �ÓI�����o�[�̏�����
bool CountDownFont::timeOverFlag = false;
bool CountDownFont::countStartFlag = false;

CountDownFont::CountDownFont(int _time)
	: GameObject(false,Tag::UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(700.0f, 480.0f, 0.0f));
	// SpriteComponent�̏�����
	sprite = new SpriteComponent(this,false,110);
	sprite->SetAlpha(1.0f);
	// �����o�[�ϐ��̏�����
	time = _time;
	warningFlag = false;

	new CountDownBackFont(_time);
	new TimeSprite();
	new WarningSprite(this);

}

CountDownFont::~CountDownFont()
{
	// �ÓI�����o�[�̏�����
	timeOverFlag = false;
	countStartFlag = false;
}

void CountDownFont::UpdateGameObject(float _deltaTime)
{
	// �Q�[���X�^�[�g������J�E���g�J�n
	if (countStartFlag == true)
	{
		// �t���[���J�E���g�𐔂���
		frameCount++;
		// 60�ɂȂ�����
		if (frameCount >= 60)
		{
			// time�����炷
			time -= 1;
			frameCount = 0;
		}
	}

	// 30�ȏ�̎��͔��F�ŕ`��
	if (time > 30)
	{
		sprite->SetTexture(RENDERER->GetTimeTexture(time - 1));
	}
	else if (time <= 30 && time >= 1)	// 30�ȉ��̎��͔��F�ŕ`��
	{
		// �x���t���O��true��
		warningFlag = true;
		sprite->SetTexture(RENDERER->GetTimeRedTexture(time - 1));
	}
	// texture���ɍ����vector�z��Ɋi�[���Ă���s����0��`�悷��Ƃ�null�ɃA�N�Z�X���Ă��܂��̂����
	if (time == 0)
	{
		sprite->SetTexture(RENDERER->GetTimeRedTexture(-1));
	}

	// time��-1�ȉ��ɂȂ�����^�C���I�[�o�[�ɂ���
	if (time <= -1)
	{
		timeOverFlag = true;
		sprite->SetVisible(false);
	}
}
