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
	//GameObjectメンバ変数の初期化
	SetPosition(Vector3(_p));
	SetScale(_size);
	tag = _objectTag;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this,false,false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/wall_model/wallBox.gpmesh"));

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//当たり判定用のコンポーネント
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
