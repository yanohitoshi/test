#pragma once

#include "PhysicsWorld.h"
#include "ColliderComponent.h"


/*
 @file PlaneCollider.h
 @brief 平面の当たり判定クラス（未実装）
*/

class PlaneCollider : public ColliderComponent
{
public:
	/**
	@brief	コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
	@param	他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
	@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
	@param	当たり判定時に、めり込みから動かす処理の優先度を決める数値
	*/
	PlaneCollider(GameObject* _owner, ColliderComponent::PhysicsTag tag, onCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);

	/**
	@brief	デストラクタ
	*/
	virtual ~PlaneCollider();

	/**
	@brief	Transformのワールド変換
	*/
	void OnUpdateWorldTransform() override;

	/**
	@brief	当たり判定に使う線分の設定
	@param	オブジェクトの大きさに合わせた線分の構造体
	*/
	void SetObjectPlane(const Plane& _plane) { objectPlane = _plane; }

	/**
	@brief	当たり判定時に使うワールド空間でのPlaneを取得する
	@return 中心をワールド座標に合わせたPlane
	*/

	Plane GetWorldPlane() const { return worldPlane; }


private:
	//===================== privateのメンバ変数 ======================//

	Plane objectPlane;
	Plane worldPlane;

};

