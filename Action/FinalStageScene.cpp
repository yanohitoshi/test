#include "FinalStageScene.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "FinalStageCreator.h"
#include "FinalStageUI.h"
#include "CountDownFont.h"

FinalStageScene::FinalStageScene()
{
	//ライトの設定(設定しないと何も映らない)
	// ライト情報初期化
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.0f, 0.0f, 1.0f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);
	// メンバー変数初期化
	clearCount = 0;
	changeCount = 0;
	startScene = true;
	continueFlag = false;
	endFlag = false;
	lightDownFlag = true;

	// クリエイター生成
	FinalStageCreator* finalStageCreator = new FinalStageCreator(false, Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!finalStageCreator->OpenFile())
	{
		//ステージを生成する(エネミーの初期位置情報も同時に)
		finalStageCreator->CreateStage();
		//プレイヤーの生成
		finalStageCreator->CreatePlayer();
	}

	// シーンUIを追加
	new FinalStageUI();

}

FinalStageScene::~FinalStageScene()
{
}

SceneState FinalStageScene::Update(const InputState& state)
{
	// シーンが始まったらライトを強くする
	if (startScene == true)
	{
		light += Vector3(0.01f, 0.01f, 0.01f);
		RENDERER->SetAmbientLight(light);
		if (light.x >= 0.8f)
		{
			startScene = false;
			RENDERER->SetAmbientLight(light);
		}
	}

	// クリア状態になったらカウント開始
	if (PlayerObject::GetClearFlag() == true)
	{
		++clearCount;
	}

	// クリア状態かつクリアカウントが一定を超えたらシーンを切り替える
	if (clearCount >= 360)
	{
		return SceneState::RESULT_SCENE;
	}

	// タイムオーバー状態かつライトを一定まで落とす状態だったら
	if (CountDownFont::timeOverFlag == true && lightDownFlag == true)
	{
		// ライト固定
		light = Vector3(0.3f, 0.3f, 0.3f);
		RENDERER->SetAmbientLight(light);

		// Aボタンが押されたら
		if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed)
		{
			lightDownFlag = false;
			// コンテニュー遷移状態にする
			continueFlag = true;
		}

		// Bボタンが押されたら
		if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed)
		{
			lightDownFlag = false;
			// ゲームオーバー状態にする
			endFlag = true;
		}
	}

	// コンテニューかゲームオーバーが選択されたら
	if (continueFlag == true || endFlag == true)
	{
		// 遷移カウント開始
		++changeCount;
		if (changeCount >= 90)
		{
			// コンテニューだったら明るくゲームオーバーだったら暗くする
			if (continueFlag == true)
			{
				light += Vector3(0.01f, 0.01f, 0.01f);
				RENDERER->SetAmbientLight(light);
			}
			else if (endFlag == true)
			{
				light -= Vector3(0.01f, 0.01f, 0.01f);
				RENDERER->SetAmbientLight(light);
			}
			if (changeCount >= 360)
			{
				// コンテニューだったら最初のステージへゲームオーバーだったらリザルト画面へ
				if (continueFlag == true)
				{
					return SceneState::FIRST_SATGE_SCENE;
				}
				else if (endFlag == true)
				{
					return SceneState::RESULT_SCENE;
				}
			}
		}
	}

	// 一定時間操作がなかったらタイトルへ
	if (PlayerObject::GetReStartFlag() == true)
	{
		return SceneState::TITLE_SCENE;
	}

	return SceneState::FINAL_STAGE_SCENE;
}