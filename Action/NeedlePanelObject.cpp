#include "NeedlePanelObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"
#include "NeedleObject.h"

NeedlePanelObject::NeedlePanelObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag) :
	GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/groundModel/box.gpmesh"));
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, ColliderComponent::NeedleTag, GetOnCollisionFunc());
	AABB box = { Vector3(-0.5f,-0.5f,-5.0f),Vector3(0.5f,0.5f,5.0f) };
	boxCollider->SetObjectBox(box);

	new NeedleObject(this, Vector3(0.0f, 0.0f, 50.0f), Vector3(2.5f, 2.5f, 2.0f), Tag::NEEDLE);
}

NeedlePanelObject::~NeedlePanelObject()
{
}

void NeedlePanelObject::UpdateGameObject(float _deltaTime)
{
	//worldboxを渡す
	aabb = boxCollider->GetWorldBox();
	position = position + velocity * _deltaTime;
	SetPosition(position);

}

void NeedlePanelObject::OnCollision(const GameObject& _hitObject)
{
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		velocity = _hitObject.GetVelocity();
	}
}
