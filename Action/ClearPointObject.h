#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file ClearPointObject.h
@brief �N���A�|�C���g�̐����ƍX�V�������s��
*/

class ClearPointObject :
    public GameObject
{
public:
	ClearPointObject(const Vector3& _pos, const Tag& _objectTag);
	~ClearPointObject();

	void UpdateGameObject(float _deltaTime)override;


private:

	//3D���f���̕`����s���N���X
	MeshComponent* meshComponent;
	Mesh* mesh;
	BoxCollider* boxCollider;
	void OnCollision(const GameObject& _hitObject)override;
	float angle;
	bool backReverseFlag;
};

