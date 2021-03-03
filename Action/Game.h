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
@brief �Q�[���̐i�s���s��
*/
class Game
{
public:
	Game();
	~Game();

    /*
    @brief	����������
    @return true : ����, false : ���s
    */
	bool Initialize();
	/*
	@brief  �I������
	*/
	void Termination();
	/*
	@brief  �Q�[�����[�v
	*/
	void GameLoop();
	/*
	@brief  �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g����
	*/
	friend void UpdateGameObjects(float _deltaTime);

	/*
	@brief  �Q�[���I�u�W�F�N�g�̓��͏���
	*/
	friend void ProcessInputs(const InputState& _state);



	static int debug;
	static bool isChangeScene;

private:

	//�Q�[���v���C���̃V�[��
	BaseScene* nowScene;
	/*
	@brief  ���͊֘A�̏���
	*/
    void ProcessInput();
	/*
	@brief  �`��֘A�̏���
	*/
    void GenerateOutput();

	/*
	@brief  �Q�[���̃A�b�v�f�[�g����
	*/
	void UpdateGame();

	/*
	@brief   ���[�h�����f�[�^�̉��
	*/
	void UnloadData();

	void ChangeScene(SceneState _state,BaseScene* _scene);

	// FPS�v���N���X
	FPS* fps;
    // ���͊Ǘ��N���X
	InputSystem* inputSystem;
	//�Q�[���𑱂��邩�ǂ���
    bool isRunning;
	float screenWidth;
	float screenHeight;
	bool isFullScreen;

	SceneState nowSceneState;
};

