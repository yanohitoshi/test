#pragma once
#include "ParticleEffectBase.h"

/*
@file MoveTutorialParticl.h
@brief �ړ��p�`���[�g���A����ParticlEffect�̕\�����s��
*/
class MoveTutorialParticl :
    public ParticleEffectBase
{
public:
    
    /*
    @brief	�R���X�g���N�^
    @param	�|�W�V����
    */
    MoveTutorialParticl(const Vector3& _pos);
    ~MoveTutorialParticl()override;

    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:
};

