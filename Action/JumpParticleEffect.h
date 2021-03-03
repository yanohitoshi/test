#pragma once
#include "ParticleEffectBase.h"
class JumpParticleEffect :
    public ParticleEffectBase
{
public:
    JumpParticleEffect(const Vector3& _pos, const Vector3& _velocity);
    ~JumpParticleEffect()override;
    void UpdateGameObject(float _deltaTime)override;

private:
    ParticleState particleState;
    GameObject* owner;
    float mScale;
    float mAlpha;
    bool ChackOnFlag;
    bool tmpChackOnFlag;
    bool generateFlag;

};

