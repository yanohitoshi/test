#include "ResultSceneUI.h"
#include "Renderer.h"
#include "ThankYouSprite.h"

ResultSceneUI::ResultSceneUI()
	: GameObject(false, UI)
{
	// ƒNƒŠƒAŽž‚Ìsprite
	new ThankYouSprite();
}

ResultSceneUI::~ResultSceneUI()
{
}

void ResultSceneUI::UpdateGameObject(float _deltaTime)
{
}
