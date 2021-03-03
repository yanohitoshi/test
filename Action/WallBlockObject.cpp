#include "WallBlockObject.h"
#include "SkeletalMeshComponent.h"
#include "MeshComponent.h"
#include "MainCameraObject.h"
#include <string>
#include "Renderer.h"
#include "Skeleton.h"
#include "BoxCollider.h"
#include  "Mesh.h"

WallBlockObject::WallBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag) :
	GameObject(false, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(Vector3(_p));
	SetScale(_size);
	tag = _objectTag;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this,false,false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/wall_model/wallBox.gpmesh"));

	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this,ColliderComponent::WallTag,GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

}

WallBlockObject::~WallBlockObject()
{
}

void WallBlockObject::UpdateGameObject(float _deltaTime)
{
	aabb = boxCollider->GetWorldBox();
}
