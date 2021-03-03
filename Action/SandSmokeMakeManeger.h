#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"
class SandSmokeMakeManeger :
    public GameObject
{
public:
    SandSmokeMakeManeger(GameObject* _owner);
    ~SandSmokeMakeManeger()override;
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    ParticleState particleState;
    int frameCount;
    Vector3 ownerSize;
};

