#pragma once
#include "BaseScene.h"


/*
@file PlayScene.h
@brief �v���C�V�[���̏������Ɛ����A���̃V�[���ւ̃V�[���J�ڂ��s��
*/

class FirstStageScene : public BaseScene
{
public:

	FirstStageScene();
	~FirstStageScene()override;

	/*
	@brief	�A�b�v�f�[�g
	@param	���͏��
	@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
	*/
	SceneState Update(const InputState& state)override;

private:
	// �J�E���g�ϐ�
	int count;
	// �V�[�����n�܂������t���O
	bool startScene;
};

