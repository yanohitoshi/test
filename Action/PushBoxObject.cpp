#include "PushBoxObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"
#include "PushBoardObject.h"

PushBoxObject::PushBoxObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Vector3& _distance, const Vector3& _direction, const float& _speed, const float& _cutBackSpeed, MoveDirectionTag _moveTag) :
	GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;

	// PushBoardとPushBoxの間隔
	float offsetX = 210.0f;
	float offsetY = 210.0f;
	float offsetZ = 100.0f;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/groundModel/box.gpmesh"));
	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, ColliderComponent::GroundTag, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());
	if (_direction.x == 1.0f)
	{
		Vector3 boardSize = Vector3(20.0f, 200.0f, 200.0f);
		new PushBoardObject(this,Vector3(_p.x + offsetX, _p.y, _p.z + offsetZ), boardSize, PUSH_BOARD, _distance, _direction, _speed, _cutBackSpeed,_moveTag);
	}
	if (_direction.x == -1.0f)
	{
		Vector3 boardSize = Vector3(20.0f, 200.0f, 200.0f);
		new PushBoardObject(this, Vector3(_p.x - offsetX, _p.y, _p.z + offsetZ), boardSize, PUSH_BOARD, _distance, _direction, _speed, _cutBackSpeed, _moveTag);
	}
	if (_direction.y == 1.0f)
	{
		Vector3 boardSize = Vector3(200.0f, 20.0f, 200.0f);
		new PushBoardObject(this, Vector3(_p.x, _p.y + offsetY, _p.z + offsetZ), boardSize, PUSH_BOARD, _distance, _direction, _speed, _cutBackSpeed, _moveTag);
	}
	if (_direction.y == -1.0f)
	{
		Vector3 boardSize = Vector3(200.0f, 20.0f, 200.0f);
		new PushBoardObject(this, Vector3(_p.x, _p.y - offsetY, _p.z + offsetZ), boardSize, PUSH_BOARD, _distance, _direction, _speed, _cutBackSpeed, _moveTag);
	}
}

PushBoxObject::~PushBoxObject()
{
}

void PushBoxObject::UpdateGameObject(float _deltaTime)
{
	//worldboxを渡す
	aabb = boxCollider->GetWorldBox();
}
