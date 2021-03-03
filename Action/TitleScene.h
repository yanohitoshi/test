#pragma once
#include "BaseScene.h"
#include "GameObject.h"

/*
@file TitleScene.h
@brief �^�C�g���V�[���̏������Ɛ����A���̃V�[���ւ̃V�[���J�ڂ��s��
*/

class TitleScene : public BaseScene
{
public:

	TitleScene();
	~TitleScene()override;

	/*
	@brief	�A�b�v�f�[�g
	@param	���͏��
	@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
	*/
	SceneState Update(const InputState& state)override;

private:

};

