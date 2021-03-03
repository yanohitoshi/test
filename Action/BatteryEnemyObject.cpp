#include "BatteryEnemyObject.h"
#include "SkeletalMeshComponent.h"
#include "MainCameraObject.h"
#include <string>
#include "Renderer.h"
#include "Skeleton.h"
#include "Animation.h"
#include "BoxCollider.h"
#include "Mesh.h"


BatteryEnemyObject::BatteryEnemyObject(const Vector3& _pos, const Tag& _objectTag) :
	GameObject(false, _objectTag, SectionTag::Exception)
{
	//GameObject�����o�ϐ��̏�����
	tag = _objectTag;
	scale = Vector3(1.0f, 1.0f, 1.0f);
	SetScale(scale);
	SetPosition(_pos);

	//���f���`��p�̃R���|�[�l���g
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/tank_model/SK_SCT_Tower.gpmesh"));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/tank_model/SK_SCT_Tower.gpskel"));

	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = RENDERER->GetMesh("Assets/Model/tank_model/SK_SCT_Tower.gpmesh");
	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, ColliderComponent::EnemyTag, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

	//��]
	float radian = Math::ToRadians(180.0f);
	Quaternion rot = GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);


}

BatteryEnemyObject::~BatteryEnemyObject()
{
}

void BatteryEnemyObject::UpdateGameObject(float _deltaTime)
{
	aabb = boxCollider->GetWorldBox();
}

void BatteryEnemyObject::GameObjectInput(const InputState& _keyState)
{
}
