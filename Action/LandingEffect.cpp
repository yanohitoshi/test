#include "LandingEffect.h"

LandingEffect::LandingEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 30, "Assets/Effect/Particle7.png")
{
	mScale = 32.0f;
	mAlpha = 1.0f;
	velocity = _velocity;
	particleComponent->SetScale(mScale);
	particleComponent->SetAlpha(mAlpha);
	particleComponent->SetColor(Vector3(0.93f, 0.93f, 0.93f));
}

LandingEffect::~LandingEffect()
{
}

void LandingEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();
	if (lifeCount >= 0)
	{
		mScale += 0.8f;
		mAlpha -= 0.05f;
		particleComponent->SetScale(mScale);
		particleComponent->SetAlpha(mAlpha);
		position += velocity * 2.0f;
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}
}
