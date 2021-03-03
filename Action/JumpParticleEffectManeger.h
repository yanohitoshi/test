#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

class JumpParticleEffectManeger :
    public GameObject
{
public:
    JumpParticleEffectManeger(GameObject* _owner);
    ~JumpParticleEffectManeger()override;
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    bool ChackOnFlag;
    float tmpVelZ;
    bool generateFlag;

};

