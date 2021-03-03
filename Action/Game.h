#pragma once

#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>
#include "InputSystem.h"

class FPS;
class GameObject;
class InputSystem;
class GameScene;
class BaseScene;

enum SceneState
{
	TITLE_SCENE,
	FIRST_SATGE_SCENE,
	SECOND_SATGE_SCENE,
	THIRD_SATGE_SCENE,
	FINAL_STAGE_SCENE,
	CLEAR_SCENE,
	OVER_SCENE,
	RESULT_SCENE
};

/*
@file Game.h
@brief ゲームの進行を行う
*/
class Game
{
public:
	Game();
	~Game();

    /*
    @brief	初期化処理
    @return true : 成功, false : 失敗
    */
	bool Initialize();
	/*
	@brief  終了処理
	*/
	void Termination();
	/*
	@brief  ゲームループ
	*/
	void GameLoop();
	/*
	@brief  ゲームオブジェクトのアップデート処理
	*/
	friend void UpdateGameObjects(float _deltaTime);

	/*
	@brief  ゲームオブジェクトの入力処理
	*/
	friend void ProcessInputs(const InputState& _state);



	static int debug;
	static bool isChangeScene;

private:

	//ゲームプレイ中のシーン
	BaseScene* nowScene;
	/*
	@brief  入力関連の処理
	*/
    void ProcessInput();
	/*
	@brief  描画関連の処理
	*/
    void GenerateOutput();

	/*
	@brief  ゲームのアップデート処理
	*/
	void UpdateGame();

	/*
	@brief   ロードしたデータの解放
	*/
	void UnloadData();

	void ChangeScene(SceneState _state,BaseScene* _scene);

	// FPS計測クラス
	FPS* fps;
    // 入力管理クラス
	InputSystem* inputSystem;
	//ゲームを続けるかどうか
    bool isRunning;
	float screenWidth;
	float screenHeight;
	bool isFullScreen;

	SceneState nowSceneState;
};

