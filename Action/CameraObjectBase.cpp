#include "CameraObjectBase.h"

//コンストラクタ
CameraObjectBase::CameraObjectBase(bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
{
}

//デストラクタ
CameraObjectBase::~CameraObjectBase()
{
}

//更新処理
void CameraObjectBase::UpdateGameObject(float _deltaTime)
{
}

void CameraObjectBase::GameObjectInput(const InputState& _keyState)
{
}
