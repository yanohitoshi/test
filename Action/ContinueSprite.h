#pragma once
#include "GameObject.h"

class SpriteComponent;

/*
@file ContinueSprite.h
@brief コンテニュー用画像を表示する
*/

class ContinueSprite :
    public GameObject
{
public:

    ContinueSprite();
    ~ContinueSprite();
    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;
    /*
    @brief	入力
    @param	入力情報
    */
    void GameObjectInput(const InputState& _keyState)override;

    /*
    @brief	drawFlagを見るためのgetter関数
    @return	drawFlag
    */
    static bool GetDrawFlag() { return drawFlag; }
    
    /*
    @brief	コンテニューしたかどうかフラグを見るためのgetter関数
    @return	continueFlag
    */
    static bool GetContinueFlag() { return continueFlag; }


private:

    // スプライトComponent
    SpriteComponent* sprite;
    // フレームカウント
    int frameCount;
    // 描画するかどうかフラグ
    bool visibleFlag;
    // 描画されているかフラグ
    static bool drawFlag;
    // コンテニューしたかどうかフラグ
    static bool continueFlag;

};

