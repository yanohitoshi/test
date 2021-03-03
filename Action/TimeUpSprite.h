#pragma once
#include "GameObject.h"

class SpriteComponent;

/*
@file TimeUpSprite.h
@brief �^�C���I�[�o�[�pUI��\��
*/

class TimeUpSprite :
    public GameObject
{
public:
    
    TimeUpSprite();
    ~TimeUpSprite();

    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

    /*
    @brief	�`�悳��Ă��邩�t���O��getter
    @return	�`�悳��Ă��邩�t���O
    */

    static bool GetDrawFlag() { return drawFlag; }
private:

    // �X�v���C�gComponent
    SpriteComponent* sprite;
    // �t���[���J�E���g
    int frameCount;
    // 1�x�����`�悷�邽�߂̃t���O
    bool visibleFlag;
    // �`�悳��Ă��邩�t���O
    static bool drawFlag;

};

