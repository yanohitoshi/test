#pragma once
#include "GameObject.h"

//GameObjectを継承したカメラの基底クラス
class CameraObjectBase :
    public GameObject
{

public:

    /*
    @brief	コンストラクタ
    @param	再利用するかフラグ
    @param	ObjectTag
    */
    CameraObjectBase(bool _reUseGameObject, const Tag _objectTag);
    ~CameraObjectBase();

    //このクラスはポーズ中に別クラスから更新関数を呼ばれることがある
    virtual void UpdateGameObject(float _deltaTime = 1.0f);
    virtual void GameObjectInput(const InputState& _keyState);

private:

};

