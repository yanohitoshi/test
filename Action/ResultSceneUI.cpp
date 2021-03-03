#include "ResultSceneUI.h"
#include "Renderer.h"
#include "ThankYouSprite.h"

ResultSceneUI::ResultSceneUI()
	: GameObject(false, UI)
{
	// クリア時のsprite
	new ThankYouSprite();
}

ResultSceneUI::~ResultSceneUI()
{
}

void ResultSceneUI::UpdateGameObject(float _deltaTime)
{
}
