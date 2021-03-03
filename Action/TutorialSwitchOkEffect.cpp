#include "TutorialSwitchOkEffect.h"

TutorialSwitchOkEffect::TutorialSwitchOkEffect(const Vector3& _pos, GameObject* _owner)
	: ParticleEffectBase(_pos, Vector3::Zero, 100, "Assets/touch_OK.png", 1.0f)
{
	// ParticleComponent‰Šú‰»
	particleComponent->SetOffSet(Vector3(0.0f, 0.0f, 0.0f));
	particleComponent->SetVisible(false);
	particleComponent->SetScale(128);
	// •Ï”‰Šú‰»
	owner = _owner;
}

TutorialSwitchOkEffect::~TutorialSwitchOkEffect()
{
}

void TutorialSwitchOkEffect::UpdateGameObject(float _deltaTime)
{
	// e‚Ì‚Ìƒtƒ‰ƒO‚ðŒ©‚Ä•`‰æ‚ðØ‚è‘Ö‚¦‚é
	if (owner->GetSwitchFlag() == true)
	{
		particleComponent->SetVisible(true);
	}
	else if (owner->GetSwitchFlag() == false)
	{
		particleComponent->SetVisible(false);
	}

}
