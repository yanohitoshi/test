#include "FirstStageScene.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "FirstStageUI.h"
#include "FirstStageCreator.h"


FirstStageScene::FirstStageScene()
{
	//���C�g�̐ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	// ���C�g��񏉊���
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.0f, 0.0f, 0.7f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(1.0f, 1.0f, 1.0f);
	// �����o�[�ϐ�������
	count = 0;
	startScene = true;

	// �N���G�C�^�[����
	FirstStageCreator* firstStageCreator = new FirstStageCreator(false,Tag::OTHER);

	//�X�e�[�W���t�@�C�����J��
	if (!firstStageCreator->OpenFile())
	{
		//�X�e�[�W�𐶐�����(�G�l�~�[�̏����ʒu����������)
		firstStageCreator->CreateStage();
		//�v���C���[�̐���
		firstStageCreator->CreatePlayer();
	}

	// �V�[��UI��ǉ�
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