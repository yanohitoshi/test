#pragma once
#include "GameObject.h"
#include "SDL_TTF.h"

/*
@file FirstStageUI.h
@brief FirstStage��UI�\�����s��
*/

class FirstStageUI :
    public GameObject
{
public:

    FirstStageUI();
    ~FirstStageUI();
    
    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;
    
private:

};


