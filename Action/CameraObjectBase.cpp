#include "CameraObjectBase.h"

//�R���X�g���N�^
CameraObjectBase::CameraObjectBase(bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
{
}

//�f�X�g���N�^
CameraObjectBase::~CameraObjectBase()
{
}

//�X�V����
void CameraObjectBase::UpdateGameObject(float _deltaTime)
{
}

void CameraObjectBase::GameObjectInput(const InputState& _keyState)
{
}
