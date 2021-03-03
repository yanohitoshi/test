#include "FirstStageScene.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "FirstStageUI.h"
#include "FirstStageCreator.h"


FirstStageScene::FirstStageScene()
{
	//ライトの設定(設定しないと何も映らない)
	// ライト情報初期化
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.0f, 0.0f, 0.7f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(1.0f, 1.0f, 1.0f);
	// メンバー変数初期化
	count = 0;
	startScene = true;

	// クリエイター生成
	FirstStageCreator* firstStageCreator = new FirstStageCreator(false,Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!firstStageCreator->OpenFile())
	{
		//ステージを生成する(エネミーの初期位置情報も同時に)
		firstStageCreator->CreateStage();
		//プレイヤーの生成
		firstStageCreator->CreatePlayer();
	}

	// シーンUIを追加
	new FirstStageUI();
}

FirstStageScene::~FirstStageScene()
{
}

SceneState FirstStageScene::Update(const InputState& state)
{
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


	if (PlayerObject::GetNextSceneFlag() == true)
	{
		++count;
		light -= Vector3(0.01f, 0.01f, 0.01f);
		RENDERER->SetAmbientLight(light);
	}

	if (PlayerObject::GetNextSceneFlag() == true && count >= 120)
	{
		return SceneState::SECOND_SATGE_SCENE;
	}

	if (PlayerObject::GetReStartFlag() == true)
	{
		return SceneState::TITLE_SCENE;
	}

	return SceneState::FIRST_SATGE_SCENE;
}