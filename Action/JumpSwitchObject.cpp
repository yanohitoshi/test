#include "JumpSwitchObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

JumpSwitchObject::JumpSwitchObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag)
	: GameObject(false, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/jumpSwitch_model/jumpSwitch.gpmesh"));

	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, ColliderComponent::JumpSwitchTag, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());
	//AABB aabb = { Vector3(-0.8f,-0.8f,-0.8f) ,Vector3(0.8f,0.8f,0.8f) };
	//boxCollider->SetObjectBox(aabb);
}

JumpSwitchObject::~JumpSwitchObject()
{
}

void JumpSwitchObject::UpdateGameObject(float _deltaTime)
{
	position = position + velocity * _deltaTime;
	SetPosition(position);
}

void JumpSwitchObject::OnCollision(const GameObject& _hitObject)
{
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		velocity = _hitObject.GetVelocity();
	}
}
