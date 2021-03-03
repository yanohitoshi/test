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
	//GameObjectメンバ変数の初期化
	tag = _objectTag;
	scale = Vector3(1.0f, 1.0f, 1.0f);
	SetScale(scale);
	SetPosition(_pos);

	//モデル描画用のコンポーネント
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/tank_model/SK_SCT_Tower.gpmesh"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/tank_model/SK_SCT_Tower.gpskel"));

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = RENDERER->GetMesh("Assets/Model/tank_model/SK_SCT_Tower.gpmesh");
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, ColliderComponent::EnemyTag, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

	//回転
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
