#pragma once

#include "GameObject.h"

class SpriteComponent;

/*
@file TitleUI.h
@brief タイトル画面のUIを表示
*/

class TitleSceneUI :
    public GameObject
{
public:

    TitleSceneUI();
    ~TitleSceneUI()override;

    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // タイトル画像表示用sprite
    SpriteComponent* sprite;

};

