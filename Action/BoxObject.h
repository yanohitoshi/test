#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file BoxObject.h
@brief �{�b�N�X�I�u�W�F�N�g�̐����ƍX�V�������s��
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

