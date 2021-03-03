#pragma once
#include "BaseScene.h"

class ClearSceneUI;

/*
@file ClearScene.h
@brief ���U���g�V�[���̏������Ɛ����A���̃V�[���ւ̃V�[���J�ڂ��s��
*/

class ClearScene : public BaseScene
{
public:

	ClearScene();
	~ClearScene()override;

	/*
	@brief	�A�b�v�f�[�g
	@param	���͏��
	@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
	*/
	SceneState Update(const InputState& state)override;

private:

};

