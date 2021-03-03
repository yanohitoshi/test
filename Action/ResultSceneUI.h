#pragma once
#include "GameObject.h"

/*
@file ResultSceneUI.h
@brief ResultScene画面でのUIの表示を行う
*/

class ResultSceneUI :
    public GameObject
{
public:

    ResultSceneUI();
    ~ResultSceneUI();

    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

};

