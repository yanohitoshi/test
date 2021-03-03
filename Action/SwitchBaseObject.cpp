#include "SwitchBaseObject.h"
#include "MeshComponent.h"
#include "SwitchBlock.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "SwitchBlock.h"
#include "Mesh.h"

SwitchBaseObject::SwitchBaseObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Tag& _switchTag)
	: GameObject(false, _objectTag)
{

	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);

	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/switch_model/S_EnergySwitch.gpmesh"));
	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();

	boxCollider = new BoxCollider(this, ColliderComponent::SWITCH_BASE, GetOnCollisionFunc());
	//AABB aabb2 = mesh->GetBox();
	//boxCollider->SetObjectBox(mesh->GetBox());

	AABB aabb = { Vector3(-75.0f,-75.0f,-150.0f),Vector3(75.0f,75.0f,40.0f) };
	boxCollider->SetObjectBox(aabb);

	new SwitchBlock(this, Vector3(2.6f,2.6f,2.0f), _switchTag);
}

SwitchBaseObject::~SwitchBaseObject()
{
}

void SwitchBaseObject::UpdateGameObject(float _deltaTime)
{

	aabb = boxCollider->GetWorldBox();
	position = position + velocity * _deltaTime;
	SetPosition(position);

}

void SwitchBaseObject::OnCollision(const GameObject& _hitObject)
{
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		velocity = _hitObject.GetVelocity();
	}
}
