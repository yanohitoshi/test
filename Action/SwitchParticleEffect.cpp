#include "SwitchParticleEffect.h"

SwitchParticleEffect::SwitchParticleEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 20, "Assets/Effect/Star.png")
{
	particleState = ParticleState::PARTICLE_DISABLE;
	mScale = 96.0f;
	mAlpha = 1.0f;
	particleComponent->SetScale(mScale);
	particleComponent->SetAlpha(mAlpha);
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 0.0f));
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
	speed = 20.0f;
}

SwitchParticleEffect::~SwitchParticleEffect()
{
}

void SwitchParticleEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();		
	if (lifeCount >= 0)
	{
		mScale += 1.0;
		mAlpha -= 0.02f;
		particleComponent->SetScale(mScale);
		particleComponent->SetAlpha(mAlpha);
		velocity.Normalize();
		position += velocity * speed;
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}
}
