#include "Game.h"
#include "SDL.h"
#include <SDL_mixer.h>
#include <glew.h>
#include <algorithm>
#include "FPS.h"
#include "Renderer.h"
#include "AudioManager.h"
#include "InputSystem.h"
#include "PhysicsWorld.h"
#include "BaseScene.h"
#include "TitleScene.h"
#include "FirstStageScene.h"
#include "SecondStageScene.h"
#include "ThirdStageScene.h"
#include "FinalStageScene.h"
#include "GameOverScene.h"
#include "ClearScene.h"
#include "ResultScene.h"
#include "GameObject.h"

int Game::debug = 0;
bool Game::isChangeScene = false;
/*
@brief  �R���X�g���N�^
*/
Game::Game()
	: fps(nullptr)
    , isRunning(true)
	, screenWidth(0.0f)
	, screenHeight(0.0f)
	, isFullScreen(true)
{
}

/*
@brief  �f�X�g���N�^
*/
Game::~Game()
{
}

/*
@brief  ����������
@return true : ���� , false : ���s
*/
bool Game::Initialize()
{
	//SDL�̏�����
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

    //���͊Ǘ��N���X�̏�����
	inputSystem = new InputSystem();
	if (!inputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}

	if (isFullScreen == true)
	{
		screenWidth = 1920;
		screenHeight = 1080;
	}
	else if (isFullScreen == false)
	{
		screenWidth = 1080;
		screenHeight = 800;

	}

	//�����_���[�̏�����
	Renderer::CreateInstance();
	//��ʍ쐬
	if (!RENDERER->Initialize(screenWidth, screenHeight, isFullScreen))
	{
		SDL_Log("Failed to initialize renderer");
		Renderer::DeleteInstance();
		return false;
	}

	AudioManager::CreateInstance();
	// �T�E���h�̏�����
	if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG))
	{
		return false;
	}
	// SDLMixer API�������@44100:�����̎��g�� 2:�X�e���I 4096:�����o�b�t�@�T�C�Y
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		Mix_CloseAudio();
		Mix_Quit();
		return false;
	}
	int decordNum = Mix_GetNumMusicDecoders();
	for (int i = 0; i < decordNum; ++i)
	{
		printf("MusicDecorder %d : %s\n", i, Mix_GetMusicDecoder(i));
	}
	int chunkNum = Mix_GetNumChunkDecoders();
	for (int i = 0; i < chunkNum; ++i)
	{
		printf("SoundDecorder %d : %s\n", i, Mix_GetChunkDecoder(i));
	}


    //�����蔻��p�N���X�̏�����
	PhysicsWorld::CreateInstance();


	//FPS�Ǘ��N���X�̏�����
	fps = new FPS();

	Matrix4 v = Matrix4::CreateLookAt(Vector3(200, 0, -500), Vector3(200,0, 0),Vector3::UnitY);
	RENDERER->SetViewMatrix(v);

	nowSceneState = TITLE_SCENE;
	nowScene = new TitleScene();

	return true;
}

/*
@brief  �I������
*/
void Game::Termination()
{
	delete nowScene;
    //�f�[�^�̃A�����[�h
	UnloadData();
    //�X�^�e�B�b�N�N���X�̉������
	Renderer::DeleteInstance();
	PhysicsWorld::DeleteInstance();
    //�N���X�̉������
    delete fps;
    delete inputSystem;
    //�T�u�V�X�e���̏I��
	SDL_Quit();
}

/*
@brief  �Q�[�����[�v
*/
void Game::GameLoop()
{
	while (isRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
		fps->Update();
		if (isChangeScene == true)
		{
			ChangeScene(nowSceneState, nowScene);
			isChangeScene = false;
		}
	}
}


/*
@brief   ���[�h�����f�[�^�̉��
*/
void Game::UnloadData()
{
	if (RENDERER != nullptr)
	{
		RENDERER->UnloadData();
		RENDERER->Shutdown();
	}
}


/*
@brief  ���͊֘A�̏���
*/
void Game::ProcessInput()
{
	inputSystem->PrepareForUpdate();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEWHEEL:
			inputSystem->ProcessEvent(event);
			break;
		default:
			break;
		}
	}

	inputSystem->Update();
	const InputState& state = inputSystem->GetState();

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == Released ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_BACK) == Pressed)
	{
		isRunning = false;
	}

	SceneState tmpSceneState;

	tmpSceneState = nowScene->Update(state);

	if (isChangeScene == false)
	{
		ProcessInputs(state);
	}

	if (tmpSceneState != nowSceneState)
	{
		nowSceneState = tmpSceneState;
		isChangeScene = true;
	}
}

void Game::ChangeScene(SceneState _state, BaseScene* _scene)
{

	GameObject::RemoveUsedGameObject();
	delete _scene;

	switch (_state)
	{
	case SceneState::TITLE_SCENE:
		nowScene = new TitleScene();
		break;
	case SceneState::FIRST_SATGE_SCENE:
		nowScene = new FirstStageScene();
		break;
	case SceneState::SECOND_SATGE_SCENE:
		nowScene = new SecondStageScene();
		break;
	case SceneState::THIRD_SATGE_SCENE:
		nowScene = new ThirdStageScene();
		break;
	case SceneState::FINAL_STAGE_SCENE:
		nowScene = new FinalStageScene();
		break;
	case SceneState::CLEAR_SCENE:
		nowScene = new ClearScene();
		break;
	case SceneState::OVER_SCENE:
		nowScene = new GameOverScene();
		break;
	case SceneState::RESULT_SCENE:
		nowScene = new ResultScene();
		break;

	}
}

/*
@brief  �`��֘A�̏���
*/
void Game::GenerateOutput()
{
	RENDERER->Draw();
}

/*
@brief  �Q�[���̃A�b�v�f�[�g����
*/
void Game::UpdateGame()
{
	float deltaTime = fps->GetDeltaTime();
	UpdateGameObjects(deltaTime);
}

void UpdateGameObjects(float _deltaTime)
{
	GameObject::updatingGameObject = true;
	
	//int objectCount = 0;

	for (auto itr = GameObject::gameObjectMap.begin(); itr != GameObject::gameObjectMap.end(); ++itr)
	{
		for (auto gameObject : itr->second)
		{
			gameObject->Update(_deltaTime);
			//++objectCount;
		}
	}

	for (auto pending : GameObject::pendingGameObjects)
	{
		pending->ComputeWorldTransform();
		auto gameObjects = GameObject::gameObjectMap.find(pending->GetTag());
		if (gameObjects != GameObject::gameObjectMap.end())
		{
			gameObjects->second.emplace_back(pending);
		}
		else
		{
			std::vector<GameObject*> tmpVector;
			tmpVector.emplace_back(pending);
			GameObject::gameObjectMap[pending->GetTag()] = tmpVector;
		}
		GameObject::pendingGameObjects.clear();
	}

	GameObject::updatingGameObject = false;

	std::vector<class GameObject*>deadObjects;
	for (auto itr = GameObject::gameObjectMap.begin(); itr != GameObject::gameObjectMap.end(); ++itr)
	{
		for (auto gameObject : itr->second)
		{
			if (gameObject->GetState() == State::Dead )
			{
				deadObjects.emplace_back(gameObject);
			}
		}
	}

	while (!deadObjects.empty())
	{
		deadObjects.pop_back();
	}
	deadObjects.clear();
}

void ProcessInputs(const InputState& _state)
{
	
	GameObject::updatingGameObject = true;

	for (auto itr = GameObject::gameObjectMap.begin(); itr != GameObject::gameObjectMap.end(); ++itr)
	{
		for (auto gameObject : itr->second)
		{
			gameObject->ProcessInput(_state);
		}
	}

	GameObject::updatingGameObject = false;

}
