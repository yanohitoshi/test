#pragma once
#include "GameObject.h"

/*
@file FinalStageUI.h
@brief FinalStage��ʂł�UI�̕\�����s��
*/

class FinalStageUI :
    public GameObject
{
public:
    
    FinalStageUI();
    ~FinalStageUI();
    
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

