#include "ContinueSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"
#include "TimeUpSprite.h"

// �ÓI�����o�[������
bool ContinueSprite::drawFlag = true;
bool ContinueSprite::continueFlag = true;

ContinueSprite::ContinueSprite()
	:GameObject(false, Tag::UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// texture�����[�h
	Texture* tex = RENDERER->GetTexture("Assets/sprite/continue.png");
	// SpriteComponent��������
	sprite = new SpriteComponent(this,false);
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// �����o�[�ϐ�������
	frameCount = 0;
	visibleFlag = true;
}

ContinueSprite::~ContinueSprite()
{
	// �ÓI�����o�[������
	drawFlag = true;
	continueFlag = true;
}

void ContinueSprite::UpdateGameObject(float _deltaTime)
{
	// �^�C���A�b�v��Ԓ��^�C���A�b�v�摜�̕`�悪�I�������`�悷��
	if (TimeUpSprite::GetDrawFlag() == false && visibleFlag == true)
	{
		sprite->SetVisible(true);
		++frameCount;
	}
}

void ContinueSprite::GameObjectInput(const InputState& _keyState)
{
	// �^�C���A�b�v�摜�̕`�悪�I����ăR���e�j���[�摜�`��J�n�����莞�Ԃ����Ă�����
	if (TimeUpSprite::GetDrawFlag() == false && frameCount >= 60)
	{
		// A�{�^���������ꂽ��
		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed )
		{
			// �`���؂��ăR���e�j���[�t���O��true��
			sprite->SetVisible(false);
			visibleFlag = false;
			drawFlag = false;
			continueFlag = true;
		}
		else if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed) // B�{�^���������ꂽ��
		{
			// �`���؂��ăR���e�j���[�t���O��false��
			sprite->SetVisible(false);
			visibleFlag = false;
			drawFlag = false;
			continueFlag = false;
		}
	}
}
