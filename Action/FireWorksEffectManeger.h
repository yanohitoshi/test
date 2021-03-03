#pragma once

#include "GameObject.h"
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

class FireWorksEffectManeger :
    public GameObject
{
public:
    FireWorksEffectManeger(GameObject* _owner);
    ~FireWorksEffectManeger()override;
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    CrystalColor crystalColor;
    int frameCount;
    bool generateFlag;
    int particleCount;
};

