#include "SwitchBlock.h"
#include "Skeleton.h"
#include "ChangeColorMeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "BoxCollider.h"
#include "MainCameraObject.h"
#include "TutorialSwitchParticlEffect.h"
#include "TutorialSwitchOkEffect.h"
#include "SwitchEffectMakeManeger.h"
#include "FirstStageUI.h"
#include <string>


SwitchBlock::SwitchBlock(GameObject* _owner, const Vector3& _size, const Tag& _objectTag)
	: GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
	position = _owner->GetPosition();
	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	velocity = Vector3::Zero;
	initPosition = position;
	stopPoint = position.z - 40;
	//モデル描画用のコンポーネント
	meshComponent = new ChangeColorMeshComponent(this,false,true);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/switch_model/S_EnergyCube.gpmesh"));

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//押し戻し判定用のコンポーネント
	boxCollider = new BoxCollider(this, ColliderComponent::SwitchTag, GetOnCollisionFunc());
	AABB aabb = { Vector3(-50.0f,-50.0f,-40.0f),Vector3(50.0f,50.0f,50.0f) };
	boxCollider->SetObjectBox(aabb);

	// ※同一のoncollisionを呼ぶと1フレームに2度呼ばれ色が変わらないため分けている
	//playerの足元判定と接しているか用のコンポーネント
	PlayerFootBoxCollider = new BoxCollider(this, ColliderComponent::FOOT_CHECKTAG, std::bind(&SwitchBlock::PlayerFootOnCollision, this, std::placeholders::_1));
	AABB footAabb = { Vector3(-55.0f,-55.0f,-40.0f),Vector3(55.0f,55.0f,50.0f) };
	PlayerFootBoxCollider->SetObjectBox(footAabb);

	tmpChangeColorFlag = false;
	changeColorFlag = false;
	pushStop = false;
	isOnPlayer = false;
	isHitPlayer = false;
	onFlag = false;
	isAvailableSwitch = true;

	if (tag == Tag::TUTORIAL_SWITCH)
	{
		new TutorialSwitchParticlEffect(Vector3(position.x,position.y,position.z + 250.0f),this);
		new TutorialSwitchOkEffect(Vector3(position.x, position.y, position.z + 250.0f), this);
	}

	new SwitchEffectMakeManeger(this);

}

SwitchBlock::~SwitchBlock()
{
}

void SwitchBlock::UpdateGameObject(float _deltaTime)
{

	aabb = boxCollider->GetWorldBox();

	ChackOnFlag(tag);

	tmpChangeColorFlag = changeColorFlag;

	if (position.z <= stopPoint && isOnPlayer == true)
	{
		changeColorFlag = true;
	}
	else
	{
		changeColorFlag = false;
	}

	 
	if (changeColorFlag == true && tmpChangeColorFlag == false)
	{
		if (isAvailableSwitch == true)
		{
			if (onFlag == false)
			{
				onFlag = true;

			}
			else if (onFlag == true)
			{
				onFlag = false;
			}
		}

	}

	if (onFlag == true && isAvailableSwitch == true)
	{
		meshComponent->SetColor(Vector3(0.1f, 0.1f, 1.0f));
	}
	else if (onFlag == false && isAvailableSwitch == true)
	{
		meshComponent->SetColor(Vector3(1.0f, 0.1f, 0.1f));
	}
	else if (isAvailableSwitch == false)
	{
		meshComponent->SetColor(Vector3(1.0f, 1.0f, 0.5f));
	}
	
	if (isOnPlayer == false && isHitPlayer == false)
	{
		if (position.z < initPosition.z)
		{
			velocity.z = 150.0f;
		}
		else if (position.z >= initPosition.z)
		{
			velocity.z = 0.0f;
		}
	}
	else if (isOnPlayer == true)
	{
		if (pushStop == false)
		{
			velocity.z = -250.0f;
		}
		else if (pushStop == true)
		{
			velocity.z = 0.0f;
		}
	}

	position = position + velocity * _deltaTime;
	SetPosition(position);

	isOnPlayer = false;
	isHitPlayer = false;

}


void SwitchBlock::ChackOnFlag(Tag& _Tag)
{
	std::vector<GameObject*> switches;

	switches = GameObject::FindGameObject(_Tag);

	int switchCount = 0;
	int flagCount = 0;
	for (auto itr : switches)
	{
		++switchCount;
		if (itr->GetSwitchFlag() == true)
		{
			++flagCount;
		}
	}
	if (flagCount == switchCount)
	{
		isAvailableSwitch = false;
	}

}

void SwitchBlock::OnCollision(const GameObject& _hitObject)
{
	if (_hitObject.GetTag() == Tag::PLAYER)
	{
		isHitPlayer = true;
	}

	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		Vector3 groundVel = _hitObject.GetVelocity();
		velocity.x = groundVel.x;
		velocity.y = groundVel.y;
	}

}

void SwitchBlock::PlayerFootOnCollision(const GameObject& _hitObject)
{

	if (_hitObject.GetTag() == Tag::PLAYER)
	{
		isOnPlayer = true;
		pushStop = false;
		if (position.z <= stopPoint)
		{
			pushStop = true;
		}
	}

}
