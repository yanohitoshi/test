#pragma once
#include "GameObject.h"

//GameObject���p�������J�����̊��N���X
class CameraObjectBase :
    public GameObject
{

public:

    /*
    @brief	�R���X�g���N�^
    @param	�ė��p���邩�t���O
    @param	ObjectTag
    */
    CameraObjectBase(bool _reUseGameObject, const Tag _objectTag);
    ~CameraObjectBase();

    //���̃N���X�̓|�[�Y���ɕʃN���X����X�V�֐����Ă΂�邱�Ƃ�����
    virtual void UpdateGameObject(float _deltaTime = 1.0f);
    virtual void GameObjectInput(const InputState& _keyState);

private:

};

