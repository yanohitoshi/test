#include "JumpSwitchObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

JumpSwitchObject::JumpSwitchObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag)
	: GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/jumpSwitch_model/jumpSwitch.gpmesh"));

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, ColliderComponent::JumpSwitchTag, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());
	//AABB aabb = { Vector3(-0.8f,-0.8f,-0.8f) ,Vector3(0.8f,0.8f,0.8f) };
	//boxCollider->SetObjectBox(aabb);
}

JumpSwitchObject::~JumpSwitchObject()
{
}

void JumpSwitchObject::UpdateGameObject(float _deltaTime)
{
	position = position + velocity * _deltaTime;
	SetPosition(position);
}

void JumpSwitchObject::OnCollision(const GameObject& _hitObject)
{
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		velocity = _hitObject.GetVelocity();
	}
}
