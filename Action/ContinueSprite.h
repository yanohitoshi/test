#pragma once
#include "GameObject.h"

class SpriteComponent;

/*
@file ContinueSprite.h
@brief �R���e�j���[�p�摜��\������
*/

class ContinueSprite :
    public GameObject
{
public:

    ContinueSprite();
    ~ContinueSprite();
    /*
    @brief	�A�b�v�f�[�g
    @param	deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;
    /*
    @brief	����
    @param	���͏��
    */
    void GameObjectInput(const InputState& _keyState)override;

    /*
    @brief	drawFlag�����邽�߂�getter�֐�
    @return	drawFlag
    */
    static bool GetDrawFlag() { return drawFlag; }
    
    /*
    @brief	�R���e�j���[�������ǂ����t���O�����邽�߂�getter�֐�
    @return	continueFlag
    */
    static bool GetContinueFlag() { return continueFlag; }


private:

    // �X�v���C�gComponent
    SpriteComponent* sprite;
    // �t���[���J�E���g
    int frameCount;
    // �`�悷�邩�ǂ����t���O
    bool visibleFlag;
    // �`�悳��Ă��邩�t���O
    static bool drawFlag;
    // �R���e�j���[�������ǂ����t���O
    static bool continueFlag;

};

