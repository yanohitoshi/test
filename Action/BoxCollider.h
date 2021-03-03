#pragma once

#include "PhysicsWorld.h"
#include "ColliderComponent.h"

/*
@file BoxCollider.h
@brief AABBを用いた当たり判定用class
*/

class BoxCollider final : public ColliderComponent
{
public:
//===================== publicのメンバ関数 ======================//

	/**
	@brief	コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
	@param	他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
	@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
	@param	当たり判定時に、めり込みから動かす処理の優先度を決める数値
	*/
	BoxCollider(GameObject* _owner, PhysicsTag tag, onCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);
	/**
	@brief	デストラクタ
	*/
	virtual ~BoxCollider();
	
	/**
	@brief	Transformのワールド変換
	*/
	void OnUpdateWorldTransform() override;

	/**
	@brief	Transformのワールド変換
			押し戻しが行われた直後にObjectのworldBoxを更新（行われなくても呼ばれる）
	*/
	void refreshWorldTransform();
	/**
	@brief	当たり判定に使うAABBの設定
	@param	オブジェクトの大きさに合わせたAABBの構造体
	*/
	void SetObjectBox(const AABB& _box) { objectBox = _box; }

	/**
	@brief	当たり判定時に使うワールド空間でのAABBを取得する
	@return 中心をワールド座標に合わせたAABBの構造体
	*/
	AABB GetWorldBox() const { return worldBox; }

	//タグをセット
	void SetBoxTag(const ColliderComponent::PhysicsTag& _tag) { mTag = _tag; }

	//AABBのタグをとる
	PhysicsTag GetBoxTag() const{ return mTag; }

private:
//===================== privateのメンバ変数 ======================//

	AABB objectBox;			//オブジェクトに設定する用のボックス（中心をオブジェクトの中心にする）
	AABB worldBox;			//当たり判定するときに使うボックス（中心をワールド座標の中心にする）
	bool shouldRotate;
};

