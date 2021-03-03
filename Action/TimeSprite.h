#pragma once

#include "GameObject.h"

class SpriteComponent;
class Texture;

/*
@file TimeSprite.h
@brief 時間表示フレーム用のUIを表示
*/

class TimeSprite :
    public GameObject
{
public:

    TimeSprite();
    ~TimeSprite();

    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // スプライトComponent
    SpriteComponent* sprite;
    // texture
    Texture* tex;
    // フレームカウント変数
    int frameCount;
};

