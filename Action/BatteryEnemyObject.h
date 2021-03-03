#pragma once
#include "GameObject.h"

class SkeletalMeshComponent;
class BoxCollider;
class Mesh;

class BatteryEnemyObject : public GameObject
{
public:
	BatteryEnemyObject(const Vector3& _pos,const Tag& _objectTag);
	~BatteryEnemyObject();

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState& _keyState)override;


private:
	//3D���f���̕`����s���N���X
	SkeletalMeshComponent* skeltalMeshComponent;
	Mesh* mesh;
	BoxCollider* boxCollider;

};
