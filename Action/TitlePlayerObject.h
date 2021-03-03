#pragma once
#include "GameObject.h"


class SkeletalMeshComponent;
class Animation;

/*
@file TitlePlayerObject.h
@brief �^�C�g���V�[�����ł̃v���C���[
       �����A�j���[�V�������Đ����邾���̃N���X
*/

class TitlePlayerObject :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ė��p���邩�t���O
    @param	�I�u�W�F�N�g���ʗptag
    */
    TitlePlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag);
    ~TitlePlayerObject()override;
    /*
    @fn �X�V����
    @param	�t���[�����[�g�Œ�pdeltaTime
    */
    void UpdateGameObject(float _deltaTime)override;
    
    /*
    @fn ���͂������Ŏ󂯎��X�V�֐�
    @brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
    */
    void GameObjectInput(const InputState& _keyState)override;

private:

    /*
    @fn �A�j���[�V�����̍X�V����
    */
    void AnimationUpdate();

    // �A�j���[�V�����pvector�z��
    std::vector<const Animation*> animTypes;
    // �A�j���[�V�����̏�ԗp�ϐ�
    int animState;

    // SkeletalMeshComponent�̃|�C���^�ϐ�
    SkeletalMeshComponent* skeltalMeshComponent;
    
    // �d�͒萔
    const float Gravity;
    // �ڒn�t���O
    bool onGround;
    // �W�����v�t���O
    bool jumpFlag;
    // �W�����v�̊Ԋu�𑪂邽�߂̃J�E���g
    int jumpDelayCount;
    // ��p����W�����v��
    float jumpPower;
    // ����
    float firstJumpPower;
    // �W�����v���鎞�ԗp�J�E���g
    float jumpFrameCount;

};

