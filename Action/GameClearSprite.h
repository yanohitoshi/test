#pragma once
#include "GameObject.h"

class SpriteComponent;
/*
@file GameClearSprite.h
@brief �Q�[���N���A�p�摜��\������
*/

class GameClearSprite :
    public GameObject
{
public:

    GameClearSprite();
    ~GameClearSprite();
    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    SpriteComponent* sprite;
    int frameCount;
    bool visibleFlag;

};

