#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

enum CrystalColor
{
    WHITE,
    RED,
    BLUE,
    GREEN,
};

class CrystalEffectManager :
    public GameObject
{
public:
    CrystalEffectManager(GameObject* _owner, CrystalColor _crystalColor);
    ~CrystalEffectManager()override;
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    ParticleState particleState;
    CrystalColor crystalColor;
    Vector3 tmpMovePos;
    int frameCount;
    int activeFrameCount;
    bool revers;
    float r;
    float yaw;
    const float yawSpeed = 0.06f;
};

