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

	//初期位置
	Vector3 initPos;
	//移動先位置
	Vector3 goalPos;
	//反転フラグ
	bool inversionFlag;
	//移動速度
	float moveSpeed;
	//移動方向
	Vector3 direction;

	float start;
	float totalTime;	
	float elapseTime;
	float differencePos;
	MoveDirectionTag moveTag;
};

