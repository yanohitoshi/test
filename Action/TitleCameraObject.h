#pragma once
#include "CameraObjectBase.h"

/*
@file TitleCamre.h
@brief タイトル画面を映すカメラの生成と更新処理
       CameraObjectBaseを継承
*/

class TitleCameraObject :
    public CameraObjectBase
{
public:

    /*
    @brief	コンストラクタ
    @param	ポジション
    */
    TitleCameraObject(const Vector3 _pos);
    ~TitleCameraObject();

    //このクラスはポーズ中に別クラスから更新関数を呼ばれることがある
    void UpdateGameObject(float _deltaTime = 1.0f);
    void GameObjectInput(const InputState& _keyState);

private:

    Vector3 target;
    Matrix4 view;

};

