#include "NextSceneObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "PlayerObject.h"
#include "MainCameraObject.h"
#include "CrystalEffectManager.h"


NextSceneObject::NextSceneObject(const Vector3& _pos, const Tag& _objectTag)
	: GameObject(false, _objectTag)
{

	//GameObject�����o�ϐ��̏�����
	SetPosition(_pos);
	SetScale(Vector3(50.0f, 50.0f, 50.0f));
	firstPos = _pos;
	tag = _objectTag;
	state = Active;
	angle = 0;
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/goods_model/SM_Gems_01a.gpmesh"));
	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, ColliderComponent::ClearPointTag, GetOnCollisionFunc());
	AABB aabb = { Vector3(-1.0f,-1.0f,-1.0f),Vector3(1.0f,1.0f,3.0f) };
	boxCollider->SetObjectBox(aabb);

	new CrystalEffectManager(this,CrystalColor::WHITE);
	new CrystalEffectManager(this, CrystalColor::RED);
	new CrystalEffectManager(this, CrystalColor::BLUE);
	new CrystalEffectManager(this, CrystalColor::GREEN);
}

NextSceneObject::~NextSceneObject()
{

}

void NextSceneObject::UpdateGameObject(float _deltaTime)
{
	if (PlayerObject::GetNextSceneFlag() == true)
	{
		angle = 15.0f;
		velocity.z = 50.0f;

		//Z����15�x��]������
		float radian = Math::ToRadians(angle);
		Quaternion rot = this->GetRotation();
		Quaternion inc(Vector3::UnitZ, radian);
		Quaternion target = Quaternion::Concatenate(rot, inc);
		SetRotation(target);

		position += velocity;
		SetPosition(position);
		if (position.z >= firstPos.z + 3000.0f)
		{
			meshComponent->SetVisible(false);
		}
		mainCamera->SetLerpObjectPos(position);
	}


}

void NextSceneObject::OnCollision(const GameObject& _hitObject)
{
}
