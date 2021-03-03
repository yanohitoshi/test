#include "MoveSwitchBaseObject.h"
#include "MeshComponent.h"
#include "SwitchBlock.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "SwitchBlock.h"
#include "Mesh.h"

MoveSwitchBaseObject::MoveSwitchBaseObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Tag& _switchTag)
	: GameObject(false, _objectTag)
{
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false, false);

	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/switch_model/S_EnergySwitch.gpmesh"));
	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();

	boxCollider = new BoxCollider(this, ColliderComponent::GroundTag, GetOnCollisionFunc());
	AABB pre = mesh->GetBox();
	boxCollider->SetObjectBox(mesh->GetBox());

	AABB aabb = { Vector3(-100.0f,-100.0f,-100.0f),Vector3(100.0f,100.0f,0.0f) };
	boxCollider->SetObjectBox(aabb);

	new SwitchBlock(this, Vector3(3.0f, 3.0f, 1.0f), _switchTag);

}

MoveSwitchBaseObject::~MoveSwitchBaseObject()
{
}

void MoveSwitchBaseObject::UpdateGameObject(float _deltaTime)
{
	aabb = boxCollider->GetWorldBox();

}

void MoveSwitchBaseObject::OnCollision(const GameObject& _hitObject)
{
}
