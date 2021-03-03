#include "FinalStageScene.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "FinalStageCreator.h"
#include "FinalStageUI.h"
#include "CountDownFont.h"

FinalStageScene::FinalStageScene()
{
	//���C�g�̐ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	// ���C�g��񏉊���
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.0f, 0.0f, 1.0f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);
	// �����o�[�ϐ�������
	clearCount = 0;
	changeCount = 0;
	startScene = true;
	continueFlag = false;
	endFlag = false;
	lightDownFlag = true;

	// �N���G�C�^�[����
	FinalStageCreator* finalStageCreator = new FinalStageCreator(false, Tag::OTHER);

	//�X�e�[�W���t�@�C�����J��
	if (!finalStageCreator->OpenFile())
	{
		//�X�e�[�W�𐶐�����(�G�l�~�[�̏����ʒu����������)
		finalStageCreator->CreateStage();
		//�v���C���[�̐���
		finalStageCreator->CreatePlayer();
	}

	// �V�[��UI��ǉ�
	new FinalStageUI();

}

FinalStageScene::~FinalStageScene()
{
}

SceneState FinalStageScene::Update(const InputState& state)
{
	// �V�[�����n�܂����烉�C�g����������
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

	// �N���A��ԂɂȂ�����J�E���g�J�n
	if (PlayerObject::GetClearFlag() == true)
	{
		++clearCount;
	}

	// �N���A��Ԃ��N���A�J�E���g�����𒴂�����V�[����؂�ւ���
	if (clearCount >= 360)
	{
		return SceneState::RESULT_SCENE;
	}

	// �^�C���I�[�o�[��Ԃ����C�g�����܂ŗ��Ƃ���Ԃ�������
	if (CountDownFont::timeOverFlag == true && lightDownFlag == true)
	{
		// ���C�g�Œ�
		light = Vector3(0.3f, 0.3f, 0.3f);
		RENDERER->SetAmbientLight(light);

		// A�{�^���������ꂽ��
		if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed)
		{
			lightDownFlag = false;
			// �R���e�j���[�J�ڏ�Ԃɂ���
			continueFlag = true;
		}

		// B�{�^���������ꂽ��
		if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed)
		{
			lightDownFlag = false;
			// �Q�[���I�[�o�[��Ԃɂ���
			endFlag = true;
		}
	}

	// �R���e�j���[���Q�[���I�[�o�[���I�����ꂽ��
	if (continueFlag == true || endFlag == true)
	{
		// �J�ڃJ�E���g�J�n
		++changeCount;
		if (changeCount >= 90)
		{
			// �R���e�j���[�������疾�邭�Q�[���I�[�o�[��������Â�����
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
				// �R���e�j���[��������ŏ��̃X�e�[�W�փQ�[���I�[�o�[�������烊�U���g��ʂ�
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

	// ��莞�ԑ��삪�Ȃ�������^�C�g����
	if (PlayerObject::GetReStartFlag() == true)
	{
		return SceneState::TITLE_SCENE;
	}

	return SceneState::FINAL_STAGE_SCENE;
}