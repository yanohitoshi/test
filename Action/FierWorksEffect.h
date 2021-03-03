#pragma once

#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

class FierWorksEffect :
    public ParticleEffectBase
{
public:
    FierWorksEffect(const Vector3& _pos, const Vector3& _velocity , CrystalColor _crystalColor);
    ~FierWorksEffect()override;
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    bool inFlag;
    float mScale;
    float mAlpha;
    float speed;
};

