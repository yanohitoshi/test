#include "PlayerSandSmokeEffect.h"

PlayerSandSmokeEffect::PlayerSandSmokeEffect(const Vector3& _pos, const Vector3& _velocity,bool _run)
	: ParticleEffectBase(_pos, _velocity, 20, "Assets/Effect/Particle_Soft.png")
{
	mScale = 32.0f;
	mAlpha = 1.0f;
	particleComponent->SetScale(mScale);
	particleComponent->SetAlpha(mAlpha);
	particleComponent->SetColor(Vector3(0.93f, 0.93f, 0.93f));
	runFlag = _run;
}

PlayerSandSmokeEffect::~PlayerSandSmokeEffect()
{
}

void PlayerSandSmokeEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	if (lifeCount >= 0)
	{
		position += velocity * 10.0;
		
		mScale += 5.0f;
		mAlpha -= 0.05f;
		particleComponent->SetScale(mScale);
		particleComponent->SetAlpha(mAlpha);
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}
}
