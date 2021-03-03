#include "WarningSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

WarningSprite::WarningSprite(CountDownFont* _owner)
	:GameObject(false, Tag::UI)
{
	// �ϐ��̏�����
	owner = _owner;
	alpha = 0.1f;
	count = 0;
	fadeFlag = true;
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// SpriteComponent�̏�����
	sprite = new SpriteComponent(this, false);
	Texture* tex = RENDERER->GetTexture("Assets/sprite/warning2.png");
	sprite->SetTexture(tex);
	sprite->SetVisible(true);
	sprite->SetAlpha(alpha);
}

WarningSprite::~WarningSprite()
{
}

void WarningSprite::UpdateGameObject(float _deltaTime)
{
	// count��2�ȉ�����owner�̃t���O��true�̎�
	if (count <= 2 && owner->GetWarningFlag() == true)
	{
		// fadeFlag��true��������fadein
		if (fadeFlag == true)
		{
			alpha += 0.01f;
		}
		else if (fadeFlag == false)		// fadeFlag��false��������fadeout
		{
			alpha -= 0.01f;
		}

		// alpha�l������in/out��؂�ւ�
		if (alpha <= 0.1)
		{
			fadeFlag = true;
		}
		else if (alpha >= 0.9)
		{
			fadeFlag = false;
		}
	}
	else if (count >= 3)	// count��3�ȏ�ɂȂ�����alpha�l��0�ɂȂ�܂�out
	{
		if (alpha >= 0.0f)
		{
			alpha -= 0.01f;
		}
	}
	// fadein/out���I��邲�ƂɃJ�E���g��ǉ�
	if (fadeFlag == false && alpha <= 0.1f)
	{
		++count;
	}
	// alpha�l���Z�b�g
	sprite->SetAlpha(alpha);
}
