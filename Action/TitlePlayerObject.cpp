#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"
#include "Renderer.h"
#include "PlayerObject.h"


TitlePlayerObject::TitlePlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, Gravity (400.0f)
{
	// ポジションをセット
	SetPosition(_pos);
	//モデル描画用のコンポーネント
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMes hをセット(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/robo_model/SK_Rob.gpmesh"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/robo_model/SK_Rob.gpskel"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	//アニメ―ション用の可変長配列をリサイズ
	animTypes.resize(AnimState::ITEMNUM);
	//アニメーションを読み込み
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

	//anim変数を速度0.5fで再生
	skeltalMeshComponent->PlayAnimation(animTypes[RUN], 1.0f);
	// メンバー変数初期化
	firstJumpPower = 40.0f;
	jumpPower = firstJumpPower;

	//Z軸を90度回転させる
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


	//ジャンプ中もしくは落下中の時重力をかける（一定数以上かかったら止めて定数にする）
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
