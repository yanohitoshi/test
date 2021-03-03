#pragma once

#include "GameObject.h"
#include <glew.h>

class BoxCollider;
class Mesh;
class ChangeColorMeshComponent;

/*
@file SwitchBlock.h
@brief スイッチの生成と更新処理を行う
*/


class SwitchBlock : public GameObject
{
public:
	// コンストラクタ
	SwitchBlock(GameObject* _owner, const Vector3& _size, const Tag& _objectTag);
	// デストラクタ
	~SwitchBlock();
	// アップデート
	void UpdateGameObject(float _deltaTime)override;

private:
	// 区画ごとに分かれたswitchがすべて押されたかどうかチェックする関数
	void ChackOnFlag(Tag& _Tag);
	// 動く床と接している時にその速度をもらうためのOnCollision
	void OnCollision(const GameObject& _hitObject)override;
	// プレイヤーの足元判定とのOnCollision
	void PlayerFootOnCollision(const GameObject& _hitObject);

	// メッシュコンポーネント
	ChangeColorMeshComponent* meshComponent;
	// 動く床と接している時にその速度をもらうためのCollider
	BoxCollider* boxCollider;
	// プレイヤーとの足元判定用Collider
	BoxCollider* PlayerFootBoxCollider;
	// メッシュからAABBの最大点最小点を得るときに使う
	Mesh* mesh;
	// Switchが利用可能か
	bool isAvailableSwitch;
	// Switchの初期ポジション保存用
	Vector3 initPosition;
	// playerがswitchに乗っているかどうか
	bool isOnPlayer;
	bool isHitPlayer;
	// 押すのを止めるかどうか
	bool pushStop;
	// 色を変えるかどうか
	bool changeColorFlag;
	// 前のフレームで色変更が行われたかどうか
	bool tmpChangeColorFlag;
	// switchの停止位置
	float stopPoint;

};
