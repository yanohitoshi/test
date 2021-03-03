#pragma once
#include "GameObject.h"

class SpriteComponent;
class Texture;
class Font;

/*
@file CountDownBackFont.h
@brief �J�E���g�_�E���̉e�̕\�����s��
*/
class CountDownBackFont :
    public GameObject
{
public:

    /*
    @brief	�R���X�g���N�^
    @param	�J�E���g���鎞��
    */
    CountDownBackFont(int _time);
    ~CountDownBackFont();

    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // SpriteComponent�ϐ�
    SpriteComponent* sprite;
    // �t���[���J�E���g
    int frameCount;
    // �v�����鎞��
    int time;

};

