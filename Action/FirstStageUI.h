#pragma once
#include "GameObject.h"
#include "SDL_TTF.h"

/*
@file FirstStageUI.h
@brief FirstStageのUI表示を行う
*/

class FirstStageUI :
    public GameObject
{
public:

    FirstStageUI();
    ~FirstStageUI();
    
    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;
    
private:

};


