#include "FinalStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"
#include "TimeUpSprite.h"
#include "ContinueSprite.h"
#include "GameOverSprite.h"
#include "GameClearSprite.h"

// �ÓI�����o�[������
bool FinalStageUI::timeOverFlag = false;
bool FinalStageUI::countStartFlag = false;

FinalStageUI::FinalStageUI()
	: GameObject(false, Tag::UI)
{
	// �J�E���g�_�E��
	new CountDownFont(150);
	// start���̃J�E���g�_�E��
	new StartCountDownSprite();
	// �^�C���A�b�v����sprite
	new TimeUpSprite();
	// �R���e�B�j���[�I������sprite
	new ContinueSprite();
	// GameOver����sprite
	new GameOverSprite();
	// GameClear����sprite
	new GameClearSprite();

}

FinalStageUI::~FinalStageUI()
{
	// �ÓI�����o�[������
	timeOverFlag = false;
	countStartFlag = false;
}

void FinalStageUI::UpdateGameObject(float _deltaTime)
{
}
