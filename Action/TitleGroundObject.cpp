#include "TitleGroundObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"

TitleGroundObject::TitleGroundObject(const Vector3& _p, const Vector3& _size, const Vector3& _playerPos, const Tag& _objectTag) :
	BoxObject(_p ,_size , _objectTag)
	, targetPos(_playerPos)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	rePositionFlag = false;
	goalPos = Vector3(position.x, position.y - 1000.0f, position.z);
	initPos = Vector3(position.x, position.y + 1000.0f, position.z);
	velocity = Vector3(0.0f, -400.0f, 0.0f);
	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);

}

TitleGroundObject::~TitleGroundObject()
{
}

void TitleGroundObject::UpdateGameObject(float _deltaTime)
{
	position += velocity * _deltaTime;
	SetPosition(position);
	if (position.y <= goalPos.y)
	{
		rePositionFlag = true;
	}

	if (rePositionFlag == true)
	{
		position = initPos;
		SetPosition(position);
		rePositionFlag = false;
	}
	
}
