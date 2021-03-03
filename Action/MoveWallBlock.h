#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file MoveWallBlock.h
@brief 動く壁の生成と更新処理を行う
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

	//開閉速度
	const float moveSpeed;
	//objectの初期位置を保存する用のvector
	Vector3 initPos;
	Vector3 stopPos;
	//open/close判定用flag
	bool openFlag;
	Tag chackTag;
};

