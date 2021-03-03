#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file BoxObject.h
@brief ボックスオブジェクトの生成と更新処理を行う
*/


class BoxObject : public GameObject
{
public:
	BoxObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);
	~BoxObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	Mesh* mesh;
	MeshComponent* meshComponent;
	BoxCollider* boxCollider;
};

