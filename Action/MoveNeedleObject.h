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

	//初期位置
	Vector3 initPos;
	//移動先位置
	Vector3 goalPos;
	//移動開始フラグ
	bool moveFlag;
	//反転フラグ
	bool inversionFlag;
	//移動間隔カウント
	int intervalCount;
	//移動速度
	const float moveSpeed;
	//移動方向
	Vector3 direction;

};

