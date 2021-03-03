#pragma once
#include "GameObject.h"

class SpriteComponent;
class Texture;
/*
@file StartCountDownSprite.h
@brief �Q�[���J�n�p�J�E���g�_�E����\������
*/

class StartCountDownSprite :
    public GameObject
{
public:

    StartCountDownSprite();
    ~StartCountDownSprite()override;

    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �X�v���C�gComponent
    SpriteComponent* sprite;
    // texture 1�p
    Texture* firstTexure;
    // texture 2�p
    Texture* secondTexure;
    // texture 3�p
    Texture* thirdTexure;
    // texture Start�p
    Texture* startTexure;

    // texture�ύX�t���O
    bool texChangeFlag;
    // �`��t���O
    bool drawSpriteFlag;
    // �t���[���J�E���g
    int frameCount;
    // �\������
    int time;
    // �J�E���g�_�E���J�n����^�C�~���O�����邽�߂̃J�E���g
    int timeStartCount;

};

