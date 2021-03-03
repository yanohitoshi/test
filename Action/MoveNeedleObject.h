#pragma once
#include "NeedleObject.h"

class MoveNeedleObject :
    public NeedleObject
{
public:
	MoveNeedleObject(GameObject* _owner, const Vector3& _offset, const Vector3& _size, const Tag& _objectTag, const float& _speed);
	~MoveNeedleObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	Mesh* mesh;
	MeshComponent* meshComponent;
	BoxCollider* boxCollider;
	GameObject* owner;

	//�����ʒu
	Vector3 initPos;
	//�ړ���ʒu
	Vector3 goalPos;
	//�ړ��J�n�t���O
	bool moveFlag;
	//���]�t���O
	bool inversionFlag;
	//�ړ��Ԋu�J�E���g
	int intervalCount;
	//�ړ����x
	const float moveSpeed;
	//�ړ�����
	Vector3 direction;

};

