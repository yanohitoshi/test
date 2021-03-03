#include "JumpParticleEffect.h"

JumpParticleEffect::JumpParticleEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 30, "Assets/Effect/Burst_2.png")
{
	mScale = 160.0f;
	mAlpha = 1.0f;
	velocity = _velocity;
	particleComponent->SetScale(mScale);
	particleComponent->SetAlpha(mAlpha);
	particleComponent->SetColor(Vector3(0.93f, 0.93f, 0.93f));
}

JumpParticleEffect::~JumpParticleEffect()
{
}

void JumpParticleEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();
	if (lifeCount >= 0)
	{
		mScale -= 3.0f;
		mAlpha -= 0.1f;
		particleComponent->SetScale(mScale);
		particleComponent->SetAlpha(mAlpha);
		position += velocity;
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}
}
