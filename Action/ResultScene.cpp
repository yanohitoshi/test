#include "ResultScene.h"
#include "TitleScene.h"
#include "InputSystem.h"
#include "ResultSceneUI.h"

ResultScene::ResultScene()
{
	// �V�[��UI�ǉ�
	new ResultSceneUI();
}

ResultScene::~ResultScene()
{

}

SceneState ResultScene::Update(const InputState& state)
{
	// �g���K�[�̏���ϐ��ɓ����
	float leftTrigger = state.Controller.GetLeftTrigger();
	float rightTrigger = state.Controller.GetRightTrigger();

	// ���͂����ăV�[���J��
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_GUIDE) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_START) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_LEFTSTICK) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_RIGHTSTICK) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_UP) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Pressed ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Pressed ||
		leftTrigger == 1 || rightTrigger == 1)
	{
		return SceneState::TITLE_SCENE;
	}
	return SceneState::RESULT_SCENE;
}

