#pragma once
#include "GameObject.h"

class SpriteComponent;
class Texture;
/*
@file StartCountDownSprite.h
@brief ゲーム開始用カウントダウンを表示する
*/

class StartCountDownSprite :
    public GameObject
{
public:

    StartCountDownSprite();
    ~StartCountDownSprite()override;

    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // スプライトComponent
    SpriteComponent* sprite;
    // texture 1用
    Texture* firstTexure;
    // texture 2用
    Texture* secondTexure;
    // texture 3用
    Texture* thirdTexure;
    // texture Start用
    Texture* startTexure;

    // texture変更フラグ
    bool texChangeFlag;
    // 描画フラグ
    bool drawSpriteFlag;
    // フレームカウント
    int frameCount;
    // 表示時間
    int time;
    // カウントダウン開始するタイミングを見るためのカウント
    int timeStartCount;

};

