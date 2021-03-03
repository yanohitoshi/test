#pragma once
#include "BaseScene.h"

class SecondStageScene :
    public BaseScene
{
public:

	SecondStageScene();
	~SecondStageScene()override;

	/*
	@brief	アップデート
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	SceneState Update(const InputState& state)override;

private:

};

