#pragma once
#include "GameObject.h"

/*
@file ThirdStageUI.h
@brief ThirdStage��UI�\�����s��
*/

class ThirdStageUI :
    public GameObject
{
public:

    ThirdStageUI();
    ~ThirdStageUI();

    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;
    // �^�C���I�[�o�[����p�t���O
    static bool timeOverFlag;
    // �J�E���g�X�^�[�g����p�t���O
    static bool countStartFlag;

private:

};

