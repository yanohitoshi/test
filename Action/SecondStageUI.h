#pragma once
#include "GameObject.h"

/*
@file SecondStageUI.h
@brief SecondStage��UI�\�����s��
*/

class SecondStageUI :
    public GameObject
{
public:

    SecondStageUI();
    ~SecondStageUI();

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

