#pragma once
#include "GameObject.h"

class SpriteComponent;
class CountDownFont;

/*
@file WarningSprite.h
@brief ���Ԍo�߂�m�点��UI��\��
*/

class WarningSprite :
    public GameObject
{
public:
    
    /*
    @brief	�R���X�g���N�^ 
    @param	�e�ƂȂ�CountDownFont�^�|�C���^
    */
    WarningSprite(CountDownFont* _owner);
    ~WarningSprite();

    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    // owner���i�[���邽�߂̃|�C���^�ϐ�
    CountDownFont* owner;
    // SpriteComponent�̃|�C���^�ϐ�
    SpriteComponent* sprite;
    // fadein�Eout��؂�ւ���t���O
    bool fadeFlag;
    // alpha�l
    float alpha;
    // ����fadein�Eout�������𐔂���J�E���g
    int count;
};

