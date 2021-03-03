#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"
#include "Renderer.h"
#include "PlayerObject.h"


TitlePlayerObject::TitlePlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, Gravity (400.0f)
{
	// �|�W�V�������Z�b�g
	SetPosition(_pos);
	//���f���`��p�̃R���|�[�l���g
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mes h���Z�b�g(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/robo_model/SK_Rob.gpmesh"));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/robo_model/SK_Rob.gpskel"));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	//�A�j���\�V�����p�̉ϒ��z������T�C�Y
	animTypes.resize(AnimState::ITEMNUM);
	//�A�j���[�V������ǂݍ���
	animTypes[IDLE] = RENDERER->GetAnimation("Assets/Model/robo_model/Happy_Idle_Anim.gpanim", true);
	animTypes[WALK] = RENDERER->GetAnimation("Assets/Model/robo_model/Happy_Walk.gpanim", true);
	animTypes[RUN] = RENDERER->GetAnimation("Assets/Model/robo_model/Running.gpanim", true);
	animTypes[JUMPLOOP] = RENDERER->GetAnimation("Assets/Model/robo_model/Floating.gpanim", true);
	animTypes[JUMPSTART] = RENDERER->GetAnimation("Assets/Model/robo_model/Jump_up.gpanim", false);
	animTypes[JUMPEND] = RENDERER->GetAnimation("Assets/Model/robo_model/Landing.gpanim", false);
	animTypes[DOWN] = RENDERER->GetAnimation("Assets/Model/robo_model/Praying_down.gpanim", false);
	animTypes[DOWN_LOOP] = RENDERER->GetAnimation("Assets/Model/robo_model/Praying_Idle.gpanim", false);
	animTypes[DOWN_UP] = RENDERER->GetAnimation("Assets/Model/robo_model/Praying_up.gpanim", false);
	animTypes[DOWN_OVER] = RENDERER->GetAnimation("Assets/Model/robo_model/over_down.gpanim", false);
	animTypes[PLAYER_DEAD] = RENDERER->GetAnimation("Assets/Model/robo_model/Stunned.gpanim", false);

	//anim�ϐ��𑬓x0.5f�ōĐ�
	skeltalMeshComponent->PlayAnimation(animTypes[RUN], 1.0f);
	// �����o�[�ϐ�������
	firstJumpPower = 40.0f;
	jumpPower = firstJumpPower;

	//Z����90�x��]������
	float radian = Math::ToRadians(90);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

}

TitlePlayerObject::~TitlePlayerObject()
{

}

void TitlePlayerObject::UpdateGameObject(float _deltaTime)
{
	RENDERER->SetPlayerPositon(position);
	AnimationUpdate();


	//�W�����v���������͗������̎��d�͂�������i��萔�ȏォ��������~�߂Ē萔�ɂ���j
	if (onGround == false )
	{
		velocity.z -= Gravity * _deltaTime;
		if (velocity.z <= -200.0f)
		{
			velocity.z = -200.0f;
		}
	}


	if (onGround == true && jumpFlag == false)
	{
		++jumpDelayCount;
		if (jumpDelayCount >= 120)
		{
			jumpFlag = true;
			skeltalMeshComponent->PlayAnimation(animTypes[JUMPSTART], 1.0f);
			animState = JUMPSTART;
			jumpDelayCount = 0;
		}

	}

	if(jumpFlag == true)
	{
		velocity.z = jumpPower;
		++jumpFrameCount;

		if (jumpFrameCount > 0 && jumpFrameCount < 13 )
		{
			jumpPower += 15.0f;
		}
		else
		{
			jumpPower = firstJumpPower;
			jumpFrameCount = 0;
			jumpFlag = false;
		}
	}


	position = position + velocity * _deltaTime;
	SetPosition(position);

	if (position.z <= 100.0f)
	{
		onGround = true;
		velocity.z = 0.0f;
	}
	else
	{
		onGround = false;
	}

}

void TitlePlayerObject::GameObjectInput(const InputState& _keyState)
{
}

void TitlePlayerObject::AnimationUpdate()
{
	if (onGround == false)
	{
		if (!skeltalMeshComponent->IsPlaying())
		{
			skeltalMeshComponent->PlayAnimation(animTypes[JUMPLOOP], 1.0f);
			animState = JUMPLOOP;
		}
		return;
	}

	if (jumpFlag == false && animState != RUN)
	{
		skeltalMeshComponent->PlayAnimation(animTypes[RUN], 1.0f);
		animState = RUN;
		return;
	}


}
