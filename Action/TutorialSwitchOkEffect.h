#pragma once
#include "ParticleEffectBase.h"

/*
@file TutorialSwitchOkEffect.h
@brief OK状態のスイッチのチュートリアル描画を行う
*/
class TutorialSwitchOkEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @brief	コンストラクタ
    @param	ポジション
    @param	オーナーとなるGameObject型ポインタ
    */
    TutorialSwitchOkEffect(const Vector3& _pos, GameObject* _owner);
    ~TutorialSwitchOkEffect()override;

    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;

};

