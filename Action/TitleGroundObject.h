#pragma once
#include "BoxObject.h"
class TitleGroundObject :
    public BoxObject
{
public:
	TitleGroundObject(const Vector3& _p, const Vector3& _size,const Vector3& _playerPos , const Tag& _objectTag);
	~TitleGroundObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	Mesh* mesh;
	MeshComponent* meshComponent;
	Vector3 targetPos;
	Vector3 goalPos;
	Vector3 initPos;
	bool rePositionFlag;
};

