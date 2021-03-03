#pragma once
#include "BaseScene.h"

class ClearSceneUI;

/*
@file ClearScene.h
@brief リザルトシーンの初期化と生成、次のシーンへのシーン遷移を行う
*/

class ClearScene : public BaseScene
{
public:

	ClearScene();
	~ClearScene()override;

	/*
	@brief	アップデート
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	SceneState Update(const InputState& state)override;

private:

};

