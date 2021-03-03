#include "SandSmokeParticle.h"

SandSmokeParticle::SandSmokeParticle(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 25, "Assets/Effect/Particle_Soft.png")
{
	mScale = 16.0f;
	mAlpha = 1.0f;
	particleComponent->SetScale(mScale);
	particleComponent->SetAlpha(mAlpha);
	particleComponent->SetColor(Vector3(0.93f, 0.93f, 0.93f));
}

SandSmokeParticle::~SandSmokeParticle()
{
}

void SandSmokeParticle::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();
	
	if (lifeCount >= 0)
	{
		mScale += 5.0f;
		mAlpha -= 0.05f;
		particleComponent->SetScale(mScale);
		particleComponent->SetAlpha(mAlpha);
		position += velocity * _deltaTime;
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}
}
