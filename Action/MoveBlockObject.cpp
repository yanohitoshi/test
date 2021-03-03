#include "MoveBlockObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

MoveBlockObject::MoveBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag,const Vector3& _distance, const Vector3& _direction, const float& _speed, MoveDirectionTag _moveTag) :
	GameObject(false, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	initPos = _p;
	goalPos = initPos + _distance;
	direction = _direction;
	moveSpeed = _speed;
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

	// �C�[�W���O�ϐ�
	start = 0.0f;
	// �ړ����鎞��
	totalTime = 1.0f;
	elapseTime = 0.0f;
	// ���B�_
	differencePos = 0.0f;
}

MoveBlockObject::~MoveBlockObject()
{
}

void MoveBlockObject::UpdateGameObject(float _deltaTime)
{
	//worldbox��n��
	aabb = boxCollider->GetWorldBox();

	if (inversionFlag == false)
	{
		velocity = direction * moveSpeed;
	}
	else if (inversionFlag == true)
	{
		velocity = direction * moveSpeed * -1.0f;
	}

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
