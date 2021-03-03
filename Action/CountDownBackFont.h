#pragma once
#include "GameObject.h"

class SpriteComponent;
class Texture;
class Font;

/*
@file CountDownBackFont.h
@brief カウントダウンの影の表示を行う
*/
class CountDownBackFont :
    public GameObject
{
public:

    /*
    @brief	コンストラクタ
    @param	カウントする時間
    */
    CountDownBackFont(int _time);
    ~CountDownBackFont();

    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // SpriteComponent変数
    SpriteComponent* sprite;
    // フレームカウント
    int frameCount;
    // 計測する時間
    int time;

};

