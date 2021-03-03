#pragma once

#include "Component.h"
#include "Collision.h"

class GameObject;

/*
@file ColliderComponent.h
@brief ColliderComponent系派生classの基底のクラス
*/

class ColliderComponent : public Component
{
public:
//===================== publicのメンバ関数 ======================//

	/*
	 @enum  PhysicsTag
			PhysicsWorld内でどのObjectなのか判別するタグ
	*/
	enum PhysicsTag
	{
		GroundTag,
		MoveGroungTag,
		WallTag,
		PlayerTag,
		SwitchTag,
		SWITCH_BASE,
		JumpSwitchTag,
		GroundCheckTag,
		FOOT_CHECKTAG,
		SwitchCheckTag,
		CameraTag,
		ClearPointTag,
		NeedleTag,
		ReSpownTag
	};

    /**
	@brief	コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
    @param	コンポーネントの更新順番（数値が小さいほど早く更新される）
    @param  当たり判定時に、めり込みから動かす処理の優先度を決める数値
    */
	ColliderComponent(GameObject* _owner, PhysicsTag tag, int _updateOrder = 200,int _collisionOrder = 100);

	/**
	@brief	めり込み動かす際の優先度を示す数値を取得する
	@return 優先度を示す数値(int)
	*/
	int GetCollisionOrder() const { return collisionOrder; }

	//未実装
	////オブジェクトが球に当たった時にめりこみからずらす処理
	//virtual void ShiftObject(const Sphere& _hirSphere) {}
	////オブジェクトが平面に当たった時にめりこみからずらす処理
	//virtual void ShiftObject(const Plane& _hitPlane) {}
	////オブジェクトがAABBに当たった時にめりこみからずらす処理
	//virtual void ShiftObject(const AABB& _hitBox) {}
	////オブジェクトがカプセルに当たった時にめりこみからずらす処理
	//virtual void ShiftObject(const Capsule& _hitCapsule) {}

private:
//===================== privateのメンバ変数 ======================//

	bool isTrigger;			//実体を伴う当たり判定をするかどうか
	int	 collisionOrder;	//数値が大きい方を優先してめり込みから動かす処理をする（0以下は動かさない
protected:
	PhysicsTag mTag;
};

