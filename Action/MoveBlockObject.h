#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;


class MoveBlockObject :
    public GameObject
{

public:
	MoveBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Vector3& _distance, const Vector3& _direction,const float& _speed,MoveDirectionTag _moveTag);
	~MoveBlockObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	Mesh* mesh;
	MeshComponent* meshComponent;
	BoxCollider* boxCollider;

	//�����ʒu
	Vector3 initPos;
	//�ړ���ʒu
	Vector3 goalPos;
	//���]�t���O
	bool inversionFlag;
	//�ړ����x
	float moveSpeed;
	//�ړ�����
	Vector3 direction;

	float start;
	float totalTime;	
	float elapseTime;
	float differencePos;
	MoveDirectionTag moveTag;
};

