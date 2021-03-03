#pragma once
#include "GameObject.h"

class SpriteComponent;

/*
@file TitleBackGroundSprite.h
@brief タイトルの背景を表示する
*/
class TitleBackGroundSprite :
    public GameObject
{
public:
    
    TitleBackGroundSprite();
    ~TitleBackGroundSprite();
    /*
    @brief	アップデート
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    // 背景用スプライトComponent
    SpriteComponent* sprite;

};

