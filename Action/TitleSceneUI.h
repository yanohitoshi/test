#pragma once

#include "GameObject.h"

class SpriteComponent;

/*
@file TitleUI.h
@brief �^�C�g����ʂ�UI��\��
*/

class TitleSceneUI :
    public GameObject
{
public:

    TitleSceneUI();
    ~TitleSceneUI()override;

    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �^�C�g���摜�\���psprite
    SpriteComponent* sprite;

};

