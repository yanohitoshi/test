#include "ParticleEffectBase.h"
#include "Renderer.h"
#include "Texture.h"

ParticleEffectBase::ParticleEffectBase(const Vector3& _pos, const Vector3& _velocity, const int& _lifeCount, const std::string& _spriteFileName, const float& _scale)
	: GameObject(false,Tag::PARTICLE)
	 ,lifeCount(_lifeCount)
{
	velocity = _velocity;
	SetPosition(_pos);
	particleComponent = new ParticleComponent(this);
	particleComponent->SetTextureID(RENDERER->GetTexture(_spriteFileName)->GetTextureID());
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 1.0f));
	particleComponent->SetScale(_scale);
}

ParticleEffectBase::~ParticleEffectBase()
{
	//delete particleComponent;
}

void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	UpdateParticleObject(_deltaTime);
	SetPosition(position + velocity);
}

void ParticleEffectBase::UpdateParticleObject(float _deltaTime)
{
	LifeCountDown();
}

void ParticleEffectBase::LifeCountDown()
{
	//生存時間がゼロになるとこのオブジェクトを更新終了する
	if (lifeCount <= 0)
	{
		particleComponent->SetVisible(false);
		SetState(State::Dead);

	}
	else
	{
		particleComponent->SetVisible(true);
		lifeCount--;
	}

}

void ParticleEffectBase::SetReverve(float _flag)
{
	particleComponent->SetReverce(_flag);

}
