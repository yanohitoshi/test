#pragma once
#include "GameObject.h"

/*
@file ResultSceneUI.h
@brief ResultScene��ʂł�UI�̕\�����s��
*/

class ResultSceneUI :
    public GameObject
{
public:

    ResultSceneUI();
    ~ResultSceneUI();

    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

};

