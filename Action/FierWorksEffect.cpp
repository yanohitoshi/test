#include "FierWorksEffect.h"
#include "ParticleComponent.h"
#include "CrystalEffectManager.h"

FierWorksEffect::FierWorksEffect(const Vector3& _pos, const Vector3& _velocity, CrystalColor _crystalColor)
	: ParticleEffectBase(_pos, _velocity, 210, "Assets/Effect/Particle_Soft.png")
{
	mScale = 2.0f;
	mAlpha = 0.1f;
	inFlag = true;
	speed = 200.0f;
	particleComponent->SetScale(mScale);
	particleComponent->SetAlpha(mAlpha);
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);

	if (_crystalColor == CrystalColor::WHITE)
	{
		particleComponent->SetColor(Vector3(0.9f, 0.9f, 0.9f));
	}
	else if (_crystalColor == CrystalColor::RED)
	{
		particleComponent->SetColor(Vector3(1.0f, 0.5f, 0.5f));
	}
	else if (_crystalColor == CrystalColor::BLUE)
	{
		particleComponent->SetColor(Vector3(0.5f, 0.5f, 1.0f));
	}
	else if (_crystalColor == CrystalColor::GREEN)
	{
		particleComponent->SetColor(Vector3(0.5f, 1.0f, 0.5f));
	}
}

FierWorksEffect::~FierWorksEffect()
{
}

void FierWorksEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	if (lifeCount > 190)
	{
		if (inFlag == true)
		{
			mAlpha += 0.05f;
			if (mAlpha >= 0.9f)
			{
				inFlag = false;
			}
		}

		mScale += 2.0f;

		particleComponent->SetScale(mScale);
		particleComponent->SetAlpha(mAlpha);

		position += velocity * speed * _deltaTime;
		SetPosition(position);
	}
	else if (lifeCount <= 190)
	{
		mScale += 5.0f;
		mAlpha -= 0.001f;
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		if (speed >= 40.0f)
		{
			speed -= 1.0f;
			if (speed <= 40.0f)
			{
				speed = 40.0f;
			}
		}
		particleComponent->SetAlpha(mAlpha);
		particleComponent->SetScale(mScale);

		position += velocity * speed * _deltaTime;
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}
}
