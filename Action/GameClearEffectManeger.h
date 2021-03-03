#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

class GameClearEffectManeger :
    public GameObject
{
public:
    GameClearEffectManeger(GameObject* _owner);
    ~GameClearEffectManeger()override;
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    int frameCount;
    int generateCount;
    int particleCount;
};

