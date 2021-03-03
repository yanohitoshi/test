#include "SphereCollider.h"
#include "Math.h"
#include "GameObject.h"
#include "Collision.h"
#include "Game.h"

/**
@brief	コンストラクタ
@param	アタッチするゲームオブジェクトのポインタ
@param	他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
@param	当たり判定時に、めり込みから動かす処理の優先度を決める数値
*/
SphereCollider::SphereCollider(GameObject* _owner, ColliderComponent::PhysicsTag tag, onCollisionFunc _func, int _updateOrder, int _collisionOrder)
	: ColliderComponent(_owner,tag, _updateOrder, _collisionOrder)
	, objectSphere({ Vector3::Zero,0.0f })
	, worldSphere({ Vector3::Zero,0.0f })
{
	PHYSICS->AddSphere(this, _func);
}

/**
@brief	デストラクタ
*/
SphereCollider::~SphereCollider()
{
	PHYSICS->RemoveSphere(this);
}

/**
@brief	Transformのワールド変換
*/
void SphereCollider::OnUpdateWorldTransform()
{
	refreshWorldTransform();
	PHYSICS->HitCheck(this);	
}

void SphereCollider::refreshWorldTransform()
{
	//ワールド座標での中心位置を更新する
	worldSphere.center = objectSphere.center + owner->GetPosition();
	//ワールド空間での球の大きさを更新する
	worldSphere.radius = objectSphere.radius * owner->GetScale();

}
