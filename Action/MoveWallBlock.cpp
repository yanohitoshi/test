#include "MoveWallBlock.h"
#include "SkeletalMeshComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Skeleton.h"
#include <string>
#include "BoxCollider.h"
#include "SandSmokeMakeManeger.h"
#include "MainCameraObject.h"
#include "FirstStageUI.h"
#include "PlayerObject.h"


MoveWallBlock::MoveWallBlock(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, float _speed, Vector3 _stopPos)
	: GameObject(false, _objectTag)
	, moveSpeed(_speed)
	, stopPos(_stopPos)
{
	//GameObjectメンバ変数の初期化
	position = Vector3(_p.x , _p.y - 200, _p.z);
	SetPosition(position);
	scale = _size;
	SetScale(scale);
	tag = _objectTag;

	velocity = Vector3(0.0f, 0.0f, 0.0f);

	openFlag = true;
	SetChackSwitchTag(tag);

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this,false,false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/moveWall_model/moveWallBox.gpmesh"));

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, ColliderComponent::WallTag, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

	new SandSmokeMakeManeger(this);

}

MoveWallBlock::~MoveWallBlock()
{
}


void MoveWallBlock::UpdateGameObject(float _deltaTime)
{
	aabb = boxCollider->GetWorldBox();

	ChackSwitch(chackTag, _deltaTime);
	
	SetPosition(position);
}

void MoveWallBlock::ChackSwitch(Tag& _tag, float _deltaTime)
{
	std::vector<GameObject*> switches;
	switches = GameObject::FindGameObject(_tag);
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
		openFlag = true;

		if (openFlag == true)
		{
			velocity.z = moveSpeed;
			position.z -= velocity.z * _deltaTime;
			if (position.z <= stopPos.z)
			{
				openFlag = false;
				velocity.z = 0.0f;
			}
		}
	}


}

void MoveWallBlock::SetChackSwitchTag(Tag& _tag)
{
	switch (_tag)
	{
	case(Tag::NEXT_SCENE_MOVE_WALL):
		chackTag = Tag::NEXT_SCENE_SWITCH;
		break;
	case(Tag::TUTORIAL_MOVE_WALL):
		chackTag = Tag::TUTORIAL_SWITCH;
		break;
	case(Tag::FIRST_MOVE_WALL):
		chackTag = Tag::FIRST_SWITCH;
		break;
	case(Tag::SECOND_MOVE_WALL):
		chackTag = Tag::SECOND_SWITCH;
		break;
	case(Tag::CLEAR_SCENE_MOVE_WALL):
		chackTag = Tag::CLEAR_SCENE_SWITCH;
		break;

	}
}


