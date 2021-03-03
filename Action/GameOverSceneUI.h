#pragma once
#include "GameObject.h"

class SpriteComponent;

/*
@file GameOverSceneUI.h
@brief GameOverScene��ʂł�UI�̕\�����s��
*/

class GameOverSceneUI :
    public GameObject
{
public:

    GameOverSceneUI();
    ~GameOverSceneUI();
    
    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // GameOver�摜�\���psprite
    SpriteComponent* sprite;

};

