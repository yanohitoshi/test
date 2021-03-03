#pragma once
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

class CrystalDefaultEffect :
    public ParticleEffectBase
{
public:
    CrystalDefaultEffect(const Vector3& _pos, const Vector3& _velocity,CrystalColor _crystalColor);
    ~CrystalDefaultEffect()override;
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;
    bool inFlag;
};

