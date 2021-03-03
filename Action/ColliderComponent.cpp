#include "ColliderComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "PhysicsWorld.h"

/**
@brief	コンストラクタ
@param	アタッチするゲームオブジェクトのポインタ
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
@param  当たり判定時に、めり込みから動かす処理の優先度を決める数値
*/
ColliderComponent::ColliderComponent(GameObject* _owner, PhysicsTag tag, int _updateOrder, int _collisionOrder)
	: Component(_owner, _updateOrder),
	isTrigger(false),
	collisionOrder(_collisionOrder),
	mTag(tag)
{
}
