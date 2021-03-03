#pragma once
#include "GameObject.h"

class SpriteComponent;
/*
@file ThankYouSprite.h
@brief リザルト画面を表示する
*/

class ThankYouSprite :
    public GameObject
{
public:

    ThankYouSprite();
    ~ThankYouSprite();

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
    // 描画するかどうかフラグ
    bool visibleFlag;

};

