#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

class PushBoardObject :
	public GameObject
{
public:
	PushBoardObject(GameObject* _owner,const Vector3& _p, const Vector3& _size, const Tag& _objectTag ,const Vector3& _distance, const Vector3& _direction, const float& _speed, const float& _cutBackSpeed, MoveDirectionTag _moveTag);
	~PushBoardObject();

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
	const float moveSpeed;
	const float cutBackSpeed;
	//移動方向
	Vector3 direction;

	MoveDirectionTag moveTag;

};
