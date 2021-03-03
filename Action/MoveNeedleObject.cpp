#include "MoveNeedleObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

MoveNeedleObject::MoveNeedleObject(GameObject* _owner, const Vector3& _offset, const Vector3& _size, const Tag& _objectTag, const float& _speed):
	NeedleObject(_owner,_offset,_size,_objectTag)
	, moveSpeed(_speed)
{
	//GameObjectメンバ変数の初期化
	position = _owner->GetPosition() + _offset;
	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	owner = _owner;
	initPos = position;
	goalPos = Vector3(position.x,position.y,position.z + _size.z);
	direction = Vector3::UnitZ;
	moveFlag = true;
	intervalCount = 0;
	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/goods_model/needle.gpmesh"));

}

MoveNeedleObject::~MoveNeedleObject()
{
}

void MoveNeedleObject::UpdateGameObject(float _deltaTime)
{
	//棘を動かす処理
	//反転フラグがfalseならそのままの速度を代入
	if (inversionFlag == false)
	{
		velocity = direction * moveSpeed;
	}
	//反転フラグがtrueなら速度に-1をかけて代入
	else if (inversionFlag == true)
	{
		velocity = direction * (moveSpeed * 0.3f) * -1.0f;
	}

	if (position.z >= goalPos.z)
	{
		inversionFlag = true;
	}
	if (position.z <= initPos.z)
	{
		inversionFlag = false;
	}

	//親クラスとなるNeedleObjectのUpdateGameObjectを使用
	NeedleObject::UpdateGameObject(_deltaTime);

}
