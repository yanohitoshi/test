#include "TutorialSwitchParticlEffect.h"

TutorialSwitchParticlEffect::TutorialSwitchParticlEffect(const Vector3& _pos, GameObject* _owner)
	: ParticleEffectBase(_pos, Vector3::Zero,100, "Assets/switch_tutorial_touch.png", 1.0f)
{
	// ParticleComponent‰Šú‰»
	particleComponent->SetOffSet(Vector3(0.0f, 0.0f, 0.0f));
	particleComponent->SetVisible(false);
	particleComponent->SetScale(128);
	// •Ï”‰Šú‰»
	owner = _owner;
}

TutorialSwitchParticlEffect::~TutorialSwitchParticlEffect()
{
}

void TutorialSwitchParticlEffect::UpdateGameObject(float _deltaTime)
{
	// e‚Ì‚Ìƒtƒ‰ƒO‚ðŒ©‚Ä•`‰æ‚ðØ‚è‘Ö‚¦‚é
	if (owner->GetSwitchFlag() == false)
	{
		particleComponent->SetVisible(true);
	}
	else if (owner->GetSwitchFlag() == true)
	{
		particleComponent->SetVisible(false);
	}
	
}
