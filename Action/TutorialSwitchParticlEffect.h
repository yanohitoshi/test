#pragma once
#include "ParticleEffectBase.h"

/*
@file TutorialSwitchParticlEffect.h
@brief switch�p��ParticleEffect�̕`����s��
*/
class TutorialSwitchParticlEffect :
    public ParticleEffectBase
{
public:

    /*
    @brief	�R���X�g���N�^
    @param	�|�W�V����
    @param	�I�[�i�[�ƂȂ�GameObject�^�|�C���^
    */
    TutorialSwitchParticlEffect(const Vector3& _pos,GameObject* _owner);
    ~TutorialSwitchParticlEffect()override;

    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �e�ƂȂ�GameObject�^�̃|�C���^
    GameObject* owner;
};

