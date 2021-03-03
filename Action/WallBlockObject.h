#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file WallBlockObject.h
@brief ï«objectÇÃê∂ê¨ÇçsÇ§
*/

class WallBlockObject : public GameObject
{
public:
	WallBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);
	~WallBlockObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	MeshComponent* meshComponent;
	BoxCollider* boxCollider;
	Mesh* mesh;

};
