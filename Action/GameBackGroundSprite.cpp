#include "GameBackGroundSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"

GameBackGroundSprite::GameBackGroundSprite(SceneState _sceneTag)
	:GameObject(false, Tag::UI)
{
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	sprite = new SpriteComponent(this, true);
	if (_sceneTag == SceneState::FIRST_SATGE_SCENE)
	{
		Texture* tex = RENDERER->GetTexture("Assets/sprite/BackGround_SP/GameBack_1.png");
		sprite->SetTexture(tex);
	}
	else if (_sceneTag == SceneState::SECOND_SATGE_SCENE)
	{
		Texture* tex = RENDERER->GetTexture("Assets/sprite/BackGround_SP/GameBack_2.png");
		sprite->SetTexture(tex);
	}
	else if (_sceneTag == SceneState::THIRD_SATGE_SCENE)
	{
		Texture* tex = RENDERER->GetTexture("Assets/sprite/BackGround_SP/GameBack_3.png");
		sprite->SetTexture(tex);
	}
	else if (_sceneTag == SceneState::FINAL_STAGE_SCENE)
	{
		Texture* tex = RENDERER->GetTexture("Assets/sprite/BackGround_SP/GameBack_4.png");
		sprite->SetTexture(tex);
	}
	sprite->SetVisible(true);
}

GameBackGroundSprite::~GameBackGroundSprite()
{
}

void GameBackGroundSprite::UpdateGameObject(float _deltaTime)
{

}
