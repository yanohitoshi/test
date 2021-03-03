#pragma once
#include "GameObject.h"

class SpriteComponent;
/*
@file GameOverSprite.h
@brief ゲームオーバーの時用のUIを表示する
*/

class GameOverSprite :
    public GameObject
{
public:

    GameOverSprite();
    ~GameOverSprite();

    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // スプライトComponent
    SpriteComponent* sprite;
    // フレームカウント
    int frameCount;
    // 描画するかフラグ
    bool visibleFlag;

};

