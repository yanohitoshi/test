#pragma once

#include "GameObject.h"

class SpriteComponent;

/*
@file ResultUI.h
@brief リザルト画面でのUIの表示を行う
*/

class ClearSceneUI :
    public GameObject
{
public:

    ClearSceneUI();
    ~ClearSceneUI();   

    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // クリア画像表示用sprite
    SpriteComponent* sprite;

};

