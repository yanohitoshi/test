#pragma once
#include "GameObject.h"

class SpriteComponent;
/*
@file GameClearSprite.h
@brief ゲームクリア用画像を表示する
*/

class GameClearSprite :
    public GameObject
{
public:

    GameClearSprite();
    ~GameClearSprite();
    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    SpriteComponent* sprite;
    int frameCount;
    bool visibleFlag;

};

