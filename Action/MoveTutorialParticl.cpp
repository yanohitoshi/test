#include "MoveTutorialParticl.h"

MoveTutorialParticl::MoveTutorialParticl(const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 100, "Assets/move_tutorial.png", 1.0f)
{
	// ParticleComponent‰Šú‰»
	particleComponent->SetOffSet(Vector3(0.0f, 0.0f, 0.0f));
	particleComponent->SetVisible(true);
	particleComponent->SetScale(512);
}

MoveTutorialParticl::~MoveTutorialParticl()
{
}

void MoveTutorialParticl::UpdateGameObject(float _deltaTime)
{

}
