#pragma once
#include "ParticleEffectBase.h"

/*
@file TutorialSwitchOkEffect.h
@brief OK��Ԃ̃X�C�b�`�̃`���[�g���A���`����s��
*/
class TutorialSwitchOkEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @brief	�R���X�g���N�^
    @param	�|�W�V����
    @param	�I�[�i�[�ƂȂ�GameObject�^�|�C���^
    */
    TutorialSwitchOkEffect(const Vector3& _pos, GameObject* _owner);
    ~TutorialSwitchOkEffect()override;

    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;

};

