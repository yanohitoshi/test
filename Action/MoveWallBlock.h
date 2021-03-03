#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file MoveWallBlock.h
@brief �����ǂ̐����ƍX�V�������s��
*/

class MoveWallBlock : public GameObject
{
public:
	MoveWallBlock(const Vector3& _p, const Vector3& _size, const Tag& _objectTag,float _speed,Vector3 _stopPos);
	~MoveWallBlock();

	void UpdateGameObject(float _deltaTime)override;

private:

	void ChackSwitch(Tag& _tag, float _deltaTime);
	void SetChackSwitchTag(Tag& _tag);
	MeshComponent* meshComponent;
	Mesh* mesh;
	BoxCollider* boxCollider;

	//�J���x
	const float moveSpeed;
	//object�̏����ʒu��ۑ�����p��vector
	Vector3 initPos;
	Vector3 stopPos;
	//open/close����pflag
	bool openFlag;
	Tag chackTag;
};

