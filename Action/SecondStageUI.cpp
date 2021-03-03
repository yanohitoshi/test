#include "SecondStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"
#include "TimeUpSprite.h"
#include "ContinueSprite.h"
#include "GameOverSprite.h"

// �ÓI�����o�[������
bool SecondStageUI::timeOverFlag = false;
bool SecondStageUI::countStartFlag = false;

SecondStageUI::SecondStageUI()
	: GameObject(false, Tag::UI)
{
	// �J�E���g�_�E��
	new CountDownFont(90);
	// start���̃J�E���g�_�E��
	new StartCountDownSprite();
	// �^�C���A�b�v����sprite
	new TimeUpSprite();
	// �R���e�B�j���[�I������sprite
	new ContinueSprite();
	// GameOver����sprite
	new GameOverSprite();
}

SecondStageUI::~SecondStageUI()
{
	// �ÓI�����o�[������
	timeOverFlag = false;
	countStartFlag = false;
}

void SecondStageUI::UpdateGameObject(float _deltaTime)
{
}
