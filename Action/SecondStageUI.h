#pragma once
#include "GameObject.h"

/*
@file SecondStageUI.h
@brief SecondStageのUI表示を行う
*/

class SecondStageUI :
    public GameObject
{
public:

    SecondStageUI();
    ~SecondStageUI();

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

