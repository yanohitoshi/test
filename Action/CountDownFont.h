#pragma once
#include "GameObject.h"

class SpriteComponent;
class Texture;
class Font;

/*
@file CountDownFont.h
@brief �J�E���g�_�E���t�H���g�̕\�����s��
*/
class CountDownFont
    : public GameObject
{
public:

    /*
    @brief	�R���X�g���N�^
    @param	�J�E���g���鎞��
    */
    CountDownFont(int _time);
    ~CountDownFont();
    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;
    
    bool GetWarningFlag() { return warningFlag; }

    static bool timeOverFlag;
    static bool countStartFlag;

private:

    // SpriteComponent�ϐ�
    SpriteComponent* sprite;
    // �t���[���J�E���g
    int frameCount;
    // �v�����鎞��
    int time;
    // WarningSpriteClass���N�����邩�ǂ����t���O
    bool warningFlag;
};