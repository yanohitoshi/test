#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"
class LandingEffectManeger :
    public GameObject
{
public:
    LandingEffectManeger(GameObject* _owner);
    ~LandingEffectManeger()override;
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    bool ChackOnFlag;
    float tmpVelZ;
    bool generateFlag;

};

