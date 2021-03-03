#include "CountDownBackFont.h"
#include "Renderer.h"
#include "Font.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

CountDownBackFont::CountDownBackFont(int _time)
	: GameObject(false, Tag::UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(695.0f, 480.0f, 0.0f));
	//  SpriteComponent������
	sprite = new SpriteComponent(this,false ,105);
	sprite->SetAlpha(1.0f);
	// �����o�[�ϐ�������
	time = _time;

}

CountDownBackFont::~CountDownBackFont()
{
}

void CountDownBackFont::UpdateGameObject(float _deltaTime)
{
	// �Q�[���X�^�[�g������J�E���g�J�n
	if (CountDownFont::countStartFlag == true)
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

	// 1�ȏ�̎��͍��F�ŕ`��
	if (time >= 1)
	{
		sprite->SetTexture(RENDERER->GetTimeBlackTexture(time - 1));
	}
	// texture���ɍ����vector�z��Ɋi�[���Ă���s����0��`�悷��Ƃ�null�ɃA�N�Z�X���Ă��܂��̂����
	if (time == 0)
	{
		sprite->SetTexture(RENDERER->GetTimeBlackTexture(-1));
	}

	// time��-1�ȉ��ɂȂ�����^�C���I�[�o�[�ɂ���
	if (time <= -1)
	{
		sprite->SetVisible(false);
	}

}
