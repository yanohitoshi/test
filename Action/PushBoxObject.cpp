#include "PushBoxObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"
#include "PushBoardObject.h"

PushBoxObject::PushBoxObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Vector3& _distance, const Vector3& _direction, const float& _speed, const float& _cutBackSpeed, MoveDirectionTag _moveTag) :
	GameObject(false, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;

	// PushBoard��PushBox�̊Ԋu
	float offsetX = 210.0f;
	float offsetY = 210.0f;
	float offsetZ = 100.0f;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/groundModel/box.gpmesh"));
	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, ColliderComponent::GroundTag, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());
	if (_direction.x == 1.0f)
	{
		Vector3 boardSize = Vector3(20.0f, 200.0f, 200.0f);
		new PushBoardObject(this,Vector3(_p.x + offsetX, _p.y, _p.z + offsetZ), boardSize, PUSH_BOARD, _distance, _direction, _speed, _cutBackSpeed,_moveTag);
	}
	if (_direction.x == -1.0f)
	{
		Vector3 boardSize = Vector3(20.0f, 200.0f, 200.0f);
		new PushBoardObject(this, Vector3(_p.x - offsetX, _p.y, _p.z + offsetZ), boardSize, PUSH_BOARD, _distance, _direction, _speed, _cutBackSpeed, _moveTag);
	}
	if (_direction.y == 1.0f)
	{
		Vector3 boardSize = Vector3(200.0f, 20.0f, 200.0f);
		new PushBoardObject(this, Vector3(_p.x, _p.y + offsetY, _p.z + offsetZ), boardSize, PUSH_BOARD, _distance, _direction, _speed, _cutBackSpeed, _moveTag);
	}
	if (_direction.y == -1.0f)
	{
		Vector3 boardSize = Vector3(200.0f, 20.0f, 200.0f);
		new PushBoardObject(this, Vector3(_p.x, _p.y - offsetY, _p.z + offsetZ), boardSize, PUSH_BOARD, _distance, _direction, _speed, _cutBackSpeed, _moveTag);
	}
}

PushBoxObject::~PushBoxObject()
{
}

void PushBoxObject::UpdateGameObject(float _deltaTime)
{
	//worldbox��n��
	aabb = boxCollider->GetWorldBox();
}
