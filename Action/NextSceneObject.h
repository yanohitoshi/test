#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

class NextSceneObject :
    public GameObject
{
public:
	NextSceneObject(const Vector3& _pos, const Tag& _objectTag);
	~NextSceneObject();

	void UpdateGameObject(float _deltaTime)override;


private:

	//3Dモデルの描画を行うクラス
	MeshComponent* meshComponent;
	Mesh* mesh;
	BoxCollider* boxCollider;
	Vector3 firstPos;
	void OnCollision(const GameObject& _hitObject)override;
	float angle;
	bool backReverseFlag;

};

