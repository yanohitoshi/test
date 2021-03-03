#pragma once

#include "ParticleEffectBase.h"

class SandSmokeParticle :
    public ParticleEffectBase
{
public:
    SandSmokeParticle(const Vector3& _pos, const Vector3& _velocity);
    ~SandSmokeParticle()override;
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;

};

