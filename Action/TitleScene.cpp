#include "TitleScene.h"
#include "InputSystem.h"
#include "TitleSceneUI.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TitleStageCreator.h"
#include "BoxObject.h"

TitleScene::TitleScene()
{
	light = Vector3(0.8f, 0.8f, 0.8f);

	//ライトの設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(light);
	// ライト情報初期化
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	//ステージを生成するクラスのインスタンス
	TitleStageCreator* titleStageCreator = new TitleStageCreator(false, Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!titleStageCreator->OpenFile())
	{
		titleStageCreator->CreateStage();
	}

	// シーンUIを追加
	new TitleSceneUI();

}

TitleScene::~TitleScene()
{
}

SceneState TitleScene::Update(const InputState& state)
{
	// トリガーの情報を変数に入れる
	float leftTrigger = state.Controller.GetLeftTrigger();
	float rightTrigger = state.Controller.GetRightTrigger();

	// 入力を見てシーン遷移
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
		return SceneState::FIRST_SATGE_SCENE;
	}

	return SceneState::TITLE_SCENE;
}

