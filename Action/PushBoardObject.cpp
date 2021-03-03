#include "PushBoardObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

PushBoardObject::PushBoardObject(GameObject* _owner,const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Vector3& _distance, const Vector3& _direction, const float& _speed, const float& _cutBackSpeed ,MoveDirectionTag _moveTag) :
	GameObject(false, _objectTag)
	, moveSpeed (_speed)
	, cutBackSpeed(_cutBackSpeed)
{
	//GameObject�����o�ϐ��̏�����
	//GameObject�����o�ϐ��̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	initPos = _p;
	goalPos = initPos + _distance;
	direction = _direction;
	moveTag = _moveTag;
	inversionFlag = false;
	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/groundModel/box.gpmesh"));
	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, ColliderComponent::MoveGroungTag, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());
}

PushBoardObject::~PushBoardObject()
{
}

void PushBoardObject::UpdateGameObject(float _deltaTime)
{
	//worldbox��n��
	aabb = boxCollider->GetWorldBox();

	if (inversionFlag == false)
	{
		velocity = direction * moveSpeed;
	}
	else if (inversionFlag == true)
	{
		velocity = direction * (moveSpeed * cutBackSpeed) * -1.0f;
	}
	//�O��ړ��p����
	if (moveTag == MoveDirectionTag::MOVE_X)
	{
		if (position.x >= goalPos.x && direction.x == 1.0f || position.x <= goalPos.x && direction.x == -1.0f)
		{
			inversionFlag = true;
		}

		if (position.x <= initPos.x && direction.x == 1.0f || position.x >= initPos.x && direction.x == -1.0f)
		{
			inversionFlag = false;
		}
	}
	//���E�ړ��p����
	if (moveTag == MoveDirectionTag::MOVE_Y)
	{
		if (position.y >= goalPos.y && direction.y == 1.0f || position.y <= goalPos.y && direction.y == -1.0f)
		{
			inversionFlag = true;
		}

		if (position.y <= initPos.y && direction.y == 1.0f || position.y >= initPos.y && direction.y == -1.0f)
		{
			inversionFlag = false;
		}
	}
	//�㉺�ړ��p����
	if (moveTag == MoveDirectionTag::MOVE_Z)
	{
		if (position.z >= goalPos.z && direction.z == 1.0f || position.z <= goalPos.z && direction.z == -1.0f)
		{
			inversionFlag = true;
		}

		if (position.z <= initPos.z && direction.z == 1.0f || position.z >= initPos.z && direction.z == -1.0f)
		{
			inversionFlag = false;
		}
	}


	position = position + velocity * _deltaTime;

	SetPosition(position);

}
