#pragma once
#include "BaseScene.h"

class ThirdStageScene :
    public BaseScene
{
public:

	ThirdStageScene();
	~ThirdStageScene()override;

	/*
	@brief	アップデート
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	SceneState Update(const InputState& state)override;

private:


};

