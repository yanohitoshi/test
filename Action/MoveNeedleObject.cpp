#include "MoveNeedleObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

MoveNeedleObject::MoveNeedleObject(GameObject* _owner, const Vector3& _offset, const Vector3& _size, const Tag& _objectTag, const float& _speed):
	NeedleObject(_owner,_offset,_size,_objectTag)
	, moveSpeed(_speed)
{
	//GameObject�����o�ϐ��̏�����
	position = _owner->GetPosition() + _offset;
	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	owner = _owner;
	initPos = position;
	goalPos = Vector3(position.x,position.y,position.z + _size.z);
	direction = Vector3::UnitZ;
	moveFlag = true;
	intervalCount = 0;
	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/goods_model/needle.gpmesh"));

}

MoveNeedleObject::~MoveNeedleObject()
{
}

void MoveNeedleObject::UpdateGameObject(float _deltaTime)
{
	//���𓮂�������
	//���]�t���O��false�Ȃ炻�̂܂܂̑��x����
	if (inversionFlag == false)
	{
		velocity = direction * moveSpeed;
	}
	//���]�t���O��true�Ȃ瑬�x��-1�������đ��
	else if (inversionFlag == true)
	{
		velocity = direction * (moveSpeed * 0.3f) * -1.0f;
	}

	if (position.z >= goalPos.z)
	{
		inversionFlag = true;
	}
	if (position.z <= initPos.z)
	{
		inversionFlag = false;
	}

	//�e�N���X�ƂȂ�NeedleObject��UpdateGameObject���g�p
	NeedleObject::UpdateGameObject(_deltaTime);

}
