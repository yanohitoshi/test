#include "ResultSceneUI.h"
#include "Renderer.h"
#include "ThankYouSprite.h"

ResultSceneUI::ResultSceneUI()
	: GameObject(false, UI)
{
	// �N���A����sprite
	new ThankYouSprite();
}

ResultSceneUI::~ResultSceneUI()
{
}

void ResultSceneUI::UpdateGameObject(float _deltaTime)
{
}
