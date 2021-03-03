#include "CrystalDefaultEffect.h"
#include "CrystalEffectManager.h"

CrystalDefaultEffect::CrystalDefaultEffect(const Vector3& _pos, const Vector3& _velocity, CrystalColor _crystalColor)
	: ParticleEffectBase(_pos, _velocity, 100, "Assets/Effect/Particle_Soft.png")
{
	mScale = 0.0f;
	mAlpha = 0.0f;
	inFlag = true;
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

CrystalDefaultEffect::~CrystalDefaultEffect()
{
}

void CrystalDefaultEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	if (lifeCount > 0)
	{
		if (inFlag == true)
		{
			mAlpha += 0.005f;
			if (mAlpha >= 0.6f)
			{
				inFlag = false;
			}
		}


		mScale += 2.0f;
		mAlpha -= 0.002f;
		particleComponent->SetScale(mScale);
		particleComponent->SetAlpha(mAlpha);
		position += velocity * 20.0 * _deltaTime;
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}
}
