#pragma once
#include "BaseScene.h"

class ThirdStageScene :
    public BaseScene
{
public:

	ThirdStageScene();
	~ThirdStageScene()override;

	/*
	@brief	�A�b�v�f�[�g
	@param	���͏��
	@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
	*/
	SceneState Update(const InputState& state)override;

private:


};

