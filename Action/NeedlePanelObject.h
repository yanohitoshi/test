#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

class NeedlePanelObject :
    public GameObject
{
public:
	NeedlePanelObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);
	~NeedlePanelObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	void OnCollision(const GameObject& _hitObject)override;

	Mesh* mesh;
	MeshComponent* meshComponent;
	BoxCollider* boxCollider;

};

