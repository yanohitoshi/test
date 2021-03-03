#pragma once
#include "GameObject.h"

class BoxCollider;

class RespawnPoint :
    public GameObject
{
public:
	RespawnPoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag);
	~RespawnPoint();

	void UpdateGameObject(float _deltaTime)override;

private:

	BoxCollider* boxCollider;
	void OnCollision(const GameObject& _hitObject)override;
	bool reSpownFlag;
};

