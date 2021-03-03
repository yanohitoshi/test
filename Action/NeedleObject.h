#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

class NeedleObject :
    public GameObject
{
public:
	NeedleObject(GameObject* _owner, const Vector3& _offset, const Vector3& _size, const Tag& _objectTag);
	~NeedleObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	Mesh* mesh;
	MeshComponent* meshComponent;
	BoxCollider* boxCollider;
	GameObject* owner;

};

