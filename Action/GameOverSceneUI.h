#pragma once
#include "GameObject.h"

class SpriteComponent;

/*
@file GameOverSceneUI.h
@brief GameOverScene画面でのUIの表示を行う
*/

class GameOverSceneUI :
    public GameObject
{
public:

    GameOverSceneUI();
    ~GameOverSceneUI();
    
    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // GameOver画像表示用sprite
    SpriteComponent* sprite;

};

