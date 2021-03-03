#include "ThirdStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"
#include "TimeUpSprite.h"
#include "ContinueSprite.h"
#include "GameOverSprite.h"

// �ÓI�����o�[������
bool ThirdStageUI::timeOverFlag = false;
bool ThirdStageUI::countStartFlag = false;

ThirdStageUI::ThirdStageUI()
	: GameObject(false, Tag::UI)
{
	// �J�E���g�_�E��
	new CountDownFont(120);
	// start���̃J�E���g�_�E��
	new StartCountDownSprite();
	// �^�C���A�b�v����sprite
	new TimeUpSprite();
	// �R���e�B�j���[�I������sprite
	new ContinueSprite();
	// GameOver����sprite
	new GameOverSprite();

}

ThirdStageUI::~ThirdStageUI()
{
	// �ÓI�����o�[������
	timeOverFlag = false;
	countStartFlag = false;
}

void ThirdStageUI::UpdateGameObject(float _deltaTime)
{
}
