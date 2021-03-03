#pragma once
#include "GameObject.h"

#include "ParticleEffectBase.h"

class SwitchEffectMakeManeger :
    public GameObject
{
public:
    SwitchEffectMakeManeger(GameObject* _owner);
    ~SwitchEffectMakeManeger()override;
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    bool ChackOnFlag;
    bool tmpChackOnFlag;
    bool generateFlag;

};

