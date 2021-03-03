#include "GameOverSceneUI.h"
#include "Renderer.h"
#include "SpriteComponent.h"

GameOverSceneUI::GameOverSceneUI()
	: GameObject(false, UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// spriteComponent��new
	sprite = new SpriteComponent(this, false);
	// �Q�[���I�[�o�[��texture�����[�h
	Texture* tex = RENDERER->GetTexture("Assets/sprite/GameOver.png");
	// texture��Component�ɃZ�b�g
	sprite->SetTexture(tex);
	// alpha�l��������
	sprite->SetAlpha(1.0f);

}

GameOverSceneUI::~GameOverSceneUI()
{
}

void GameOverSceneUI::UpdateGameObject(float _deltaTime)
{
}
