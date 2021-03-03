#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

class PushBoxObject :
    public GameObject
{
public:
	PushBoxObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Vector3& _distance, const Vector3& _direction, const float& _speed, const float& _cutBackSpeed , MoveDirectionTag _moveTag);
	~PushBoxObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	Mesh* mesh;
	MeshComponent* meshComponent;
	BoxCollider* boxCollider;

};

