#pragma once
#include "GameObject.h"

class SpriteComponent;
class CountDownFont;

/*
@file WarningSprite.h
@brief 時間経過を知らせるUIを表示
*/

class WarningSprite :
    public GameObject
{
public:
    
    /*
    @brief	コンストラクタ 
    @param	親となるCountDownFont型ポインタ
    */
    WarningSprite(CountDownFont* _owner);
    ~WarningSprite();

    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    // ownerを格納するためのポインタ変数
    CountDownFont* owner;
    // SpriteComponentのポインタ変数
    SpriteComponent* sprite;
    // fadein・outを切り替えるフラグ
    bool fadeFlag;
    // alpha値
    float alpha;
    // 何回fadein・outしたかを数えるカウント
    int count;
};

