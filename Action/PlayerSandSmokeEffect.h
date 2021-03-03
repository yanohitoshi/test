#pragma once
#include "ParticleEffectBase.h"
class PlayerSandSmokeEffect :
    public ParticleEffectBase
{
public:
    PlayerSandSmokeEffect(const Vector3& _pos, const Vector3& _velocity, bool _run);
    ~PlayerSandSmokeEffect()override;
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;
    bool runFlag;

};

