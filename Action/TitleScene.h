#pragma once
#include "BaseScene.h"
#include "GameObject.h"

/*
@file TitleScene.h
@brief タイトルシーンの初期化と生成、次のシーンへのシーン遷移を行う
*/

class TitleScene : public BaseScene
{
public:

	TitleScene();
	~TitleScene()override;

	/*
	@brief	アップデート
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	SceneState Update(const InputState& state)override;

private:

};

