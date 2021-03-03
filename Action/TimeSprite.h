#pragma once

#include "GameObject.h"

class SpriteComponent;
class Texture;

/*
@file TimeSprite.h
@brief ���ԕ\���t���[���p��UI��\��
*/

class TimeSprite :
    public GameObject
{
public:

    TimeSprite();
    ~TimeSprite();

    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �X�v���C�gComponent
    SpriteComponent* sprite;
    // texture
    Texture* tex;
    // �t���[���J�E���g�ϐ�
    int frameCount;
};

