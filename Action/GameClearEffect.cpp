#include "GameClearEffect.h"
#include "FireWorksEffectManeger.h"

GameClearEffect::GameClearEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 10, "Assets/Effect/Particle_Soft.png")
{
	mScale = 64.0f;
	mAlpha = 1.0f;
	particleComponent->SetScale(mScale);
	particleComponent->SetAlpha(mAlpha);
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 0.0f));
	new FireWorksEffectManeger(this);

}

GameClearEffect::~GameClearEffect()
{
}

void GameClearEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	if (lifeCount >= 0)
	{
		position += velocity * 400.0 * _deltaTime;
		
		mScale += 10.0f;
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
