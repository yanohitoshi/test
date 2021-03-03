#pragma once
#include "ParticleEffectBase.h"

/*
@file TutorialSwitchParticlEffect.h
@brief switch用のParticleEffectの描画を行う
*/
class TutorialSwitchParticlEffect :
    public ParticleEffectBase
{
public:

    /*
    @brief	コンストラクタ
    @param	ポジション
    @param	オーナーとなるGameObject型ポインタ
    */
    TutorialSwitchParticlEffect(const Vector3& _pos,GameObject* _owner);
    ~TutorialSwitchParticlEffect()override;

    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // 親となるGameObject型のポインタ
    GameObject* owner;
};

