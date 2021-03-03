#pragma once
#include "GameObject.h"

class SpriteComponent;
/*
@file ThankYouSprite.h
@brief ���U���g��ʂ�\������
*/

class ThankYouSprite :
    public GameObject
{
public:

    ThankYouSprite();
    ~ThankYouSprite();

    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �X�v���C�gComponent
    SpriteComponent* sprite;
    // �t���[���J�E���g
    int frameCount;
    // �`�悷�邩�ǂ����t���O
    bool visibleFlag;

};

