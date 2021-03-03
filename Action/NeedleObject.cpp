#include "NeedleObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

NeedleObject::NeedleObject(GameObject* _owner ,const Vector3& _offset, const Vector3& _size, const Tag& _objectTag) :
	GameObject(false, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	position = _owner->GetPosition() + _offset;
	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	owner = _owner;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/goods_model/needles.gpmesh"));
}

NeedleObject::~NeedleObject()
{
}

void NeedleObject::UpdateGameObject(float _deltaTime)
{
	velocity = owner->GetVelocity();

	position = position + velocity * _deltaTime;
	SetPosition(position);
}
