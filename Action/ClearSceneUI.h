#pragma once

#include "GameObject.h"

class SpriteComponent;

/*
@file ResultUI.h
@brief ���U���g��ʂł�UI�̕\�����s��
*/

class ClearSceneUI :
    public GameObject
{
public:

    ClearSceneUI();
    ~ClearSceneUI();   

    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �N���A�摜�\���psprite
    SpriteComponent* sprite;

};

