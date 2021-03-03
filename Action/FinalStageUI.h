#pragma once
#include "GameObject.h"

/*
@file FinalStageUI.h
@brief FinalStage画面でのUIの表示を行う
*/

class FinalStageUI :
    public GameObject
{
public:
    
    FinalStageUI();
    ~FinalStageUI();
    
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

