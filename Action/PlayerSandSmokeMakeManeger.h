#pragma once

#include "GameObject.h"
#include "ParticleEffectBase.h"

class PlayerSandSmokeMakeManeger :
    public GameObject
{
public:
    PlayerSandSmokeMakeManeger(GameObject* _owner);
    ~PlayerSandSmokeMakeManeger()override;
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    ParticleState particleState;
    Vector3 effectPosition;
    int frameCount;
    int generateCount;

};

