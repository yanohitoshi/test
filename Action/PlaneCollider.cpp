#include "PlaneCollider.h"
#include "Math.h"
#include "GameObject.h"
#include "Collision.h"
#include "Game.h"

PlaneCollider::PlaneCollider(GameObject* _owner, ColliderComponent::PhysicsTag tag, onCollisionFunc _func, int _updateOrder, int _collisionOrder)
	:ColliderComponent(_owner, tag,_updateOrder, _collisionOrder)
	,objectPlane(Vector3::Zero,0.0f)
	,worldPlane(Vector3::Zero, 0.0f)
{
	PHYSICS->AddPlane(this, _func);
}

PlaneCollider::~PlaneCollider()
{
	PHYSICS->RemovePlane(this);
}

void PlaneCollider::OnUpdateWorldTransform()
{
	worldPlane = objectPlane;
}
