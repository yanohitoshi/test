#pragma once
#include "GameObject.h"

class SpriteComponent;

/*
@file TimeUpSprite.h
@brief タイムオーバー用UIを表示
*/

class TimeUpSprite :
    public GameObject
{
public:
    
    TimeUpSprite();
    ~TimeUpSprite();

    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

    /*
    @brief	描画されているかフラグのgetter
    @return	描画されているかフラグ
    */

    static bool GetDrawFlag() { return drawFlag; }
private:

    // スプライトComponent
    SpriteComponent* sprite;
    // フレームカウント
    int frameCount;
    // 1度だけ描画するためのフラグ
    bool visibleFlag;
    // 描画されているかフラグ
    static bool drawFlag;

};

