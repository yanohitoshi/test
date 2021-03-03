#pragma once
#include "ParticleEffectBase.h"

/*
@file MoveTutorialParticl.h
@brief 移動用チュートリアルのParticlEffectの表示を行う
*/
class MoveTutorialParticl :
    public ParticleEffectBase
{
public:
    
    /*
    @brief	コンストラクタ
    @param	ポジション
    */
    MoveTutorialParticl(const Vector3& _pos);
    ~MoveTutorialParticl()override;

    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:
};

