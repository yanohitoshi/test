#include "RespawnPoint.h"
#include "BoxCollider.h"

RespawnPoint::RespawnPoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag)
	: GameObject(false,_objectTag)
{
	position = _p;
	SetPosition(position);
	reSpownFlag = false;

	boxCollider = new BoxCollider(this,ColliderComponent::ReSpownTag, GetOnCollisionFunc());
	//AABB box = { Vector3(-1.0f,-3000.0f,-5000.0f),Vector3(1.0f,3000.0f,5000.0f) };
	boxCollider->SetObjectBox(_box);

}

RespawnPoint::~RespawnPoint()
{
}

void RespawnPoint::UpdateGameObject(float _deltaTime)
{
}

void RespawnPoint::OnCollision(const GameObject& _hitObject)
{
	reSpownFlag = true;
}
