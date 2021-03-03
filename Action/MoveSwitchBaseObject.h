#pragma once
#include "GameObject.h"

class BoxCollider;
class Mesh;
class MeshComponent;

class MoveSwitchBaseObject :
    public GameObject
{
public:

	MoveSwitchBaseObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Tag& _switchTag);
	~MoveSwitchBaseObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	void OnCollision(const GameObject& _hitObject)override;
	MeshComponent* meshComponent;
	BoxCollider* boxCollider;
	Mesh* mesh;

};

