#pragma once
#include "GameObject.h"

class SpriteComponent;

/*
@file TitleBackGroundSprite.h
@brief �^�C�g���̔w�i��\������
*/
class TitleBackGroundSprite :
    public GameObject
{
public:
    
    TitleBackGroundSprite();
    ~TitleBackGroundSprite();
    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    // �w�i�p�X�v���C�gComponent
    SpriteComponent* sprite;

};

