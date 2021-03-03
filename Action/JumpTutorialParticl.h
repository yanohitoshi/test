#pragma once
#include "ParticleEffectBase.h"

/*
@file JumpTutorialParticl.h
@brief ジャンプ用チュートリアルのParticlEffect表示を行う
*/
class JumpTutorialParticl :
    public ParticleEffectBase
{
public:

    /*
    @brief	コンストラクタ
    @param	ポジション
    */
    JumpTutorialParticl(const Vector3& _pos);
    ~JumpTutorialParticl()override;

    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

};

