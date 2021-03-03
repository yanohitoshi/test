#include "FirstStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"


FirstStageUI::FirstStageUI()
	: GameObject(false, Tag::UI)
{
	// �W�����v�`���[�g���A���pParticl
	new JumpTutorialParticl(Vector3(3700.0f, -1000.0f, 700.0f));
	// �ړ��`���[�g���A���pParticl
	new MoveTutorialParticl(Vector3(3700.0f, -2200.0f, 700.0f));

	// �v���C���[�𓮂������Ƃ��ł���悤�ɂ��邽�߂̃t���O
	CountDownFont::countStartFlag = true;

}

FirstStageUI::~FirstStageUI()
{
	// �v���C���[�𓮂������Ƃ��ł���悤�ɂ��邽�߂̃t���O�̏�����
	CountDownFont::countStartFlag = false;
}

void FirstStageUI::UpdateGameObject(float _deltaTime)
{
}
