#pragma once
#include "GameObject.h"

/*
@file ThirdStageUI.h
@brief ThirdStageのUI表示を行う
*/

class ThirdStageUI :
    public GameObject
{
public:

    ThirdStageUI();
    ~ThirdStageUI();

    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;
    // タイムオーバー判定用フラグ
    static bool timeOverFlag;
    // カウントスタート判定用フラグ
    static bool countStartFlag;

private:

};

