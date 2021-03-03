#pragma once
#include "Math.h"
struct InputState;
enum SceneState;

/*
@file BaseScene.h
@brief Sceneの基底クラス
*/

class BaseScene
{
public:

	// コンストラクタ（仮想関数）
	BaseScene() {};
	// デストラクタ（仮想関数）
	virtual ~BaseScene() {};

	/*
	@brief	アップデート（仮想関数）
	@param	入力情報
	@return シーンの遷移を判定するためのenum型のSceneState
	*/
	virtual SceneState Update(const InputState& state) = 0;

protected:

	// ライト用Vector3変数
	Vector3 light;
	// クリア後のカウント
	int clearCount;
	// 切り替え用カウント
	int changeCount;
	// シーンが始まったかどうかフラグ
	bool startScene;
	// コンテニューされたかフラグ
	bool continueFlag;
	// 終了フラグ
	bool endFlag;
	// ライトを落とすかどうかフラグ
	bool lightDownFlag;


};

