#pragma once
#include "ParticleEffectBase.h"

/*
@file JumpTutorialParticl.h
@brief �W�����v�p�`���[�g���A����ParticlEffect�\�����s��
*/
class JumpTutorialParticl :
    public ParticleEffectBase
{
public:

    /*
    @brief	�R���X�g���N�^
    @param	�|�W�V����
    */
    JumpTutorialParticl(const Vector3& _pos);
    ~JumpTutorialParticl()override;

    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

};

