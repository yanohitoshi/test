#pragma once

#include "ParticleEffectBase.h"

class SwitchParticleEffect :
    public ParticleEffectBase
{
public:
    SwitchParticleEffect(const Vector3& _pos, const Vector3& _velocity);
    ~SwitchParticleEffect()override;
    void UpdateGameObject(float _deltaTime)override;

private:
    ParticleState particleState;
    GameObject* owner;
    float mScale;
    float mAlpha;
    float speed;
};

