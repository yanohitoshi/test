#include "NeedleObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

NeedleObject::NeedleObject(GameObject* _owner ,const Vector3& _offset, const Vector3& _size, const Tag& _objectTag) :
	GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
	position = _owner->GetPosition() + _offset;
	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	owner = _owner;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/goods_model/needles.gpmesh"));
}

NeedleObject::~NeedleObject()
{
}

void NeedleObject::UpdateGameObject(float _deltaTime)
{
	velocity = owner->GetVelocity();

	position = position + velocity * _deltaTime;
	SetPosition(position);
}
