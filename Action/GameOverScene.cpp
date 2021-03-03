#include "GameOverScene.h"
#include "TitleScene.h"
#include "InputSystem.h"
#include "GameOverSceneUI.h"
#include "FirstStageUI.h"


GameOverScene::GameOverScene()
{
	// �V�[��UI�ǉ�
	new GameOverSceneUI();

}

GameOverScene::~GameOverScene()
{

}

SceneState GameOverScene::Update(const InputState& state)
{
	// ���͂����ăV�[���J��
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed)
	{
		return SceneState::TITLE_SCENE;
	}


	return SceneState::OVER_SCENE;
}
