#pragma once
#include "GameObject.h"

class SkeletalMeshComponent;
class Animation;
class BoxCollider;
class Mesh;
class SphereCollider;

/*
	 @enum AnimState
	　プレイヤーのアニメーションの状態
*/
enum AnimState
{
	IDLE,
	WALK,
	RUN,
	JUMPLOOP,
	JUMPSTART,
	JUMPEND,
	DOWN,
	DOWN_LOOP,
	DOWN_UP,
	DOWN_OVER,
	PLAYER_DEAD,
	ITEMNUM
};

/*
@file PlayerObject.h
@brief ゲーム中のプレイヤー
	   ゲーム中のプレイヤーの初期化と更新処理を行う
*/
class PlayerObject : public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	再利用するかフラグ
	@param	オブジェクト判別用tag
	*/
	PlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag);

	/*
	@fn デストラクタ
	*/
	~PlayerObject();

	/*
	@fn 更新処理
	*/
	void UpdateGameObject(float _deltaTime)override;
	/*
	@fn 入力処理
	@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	*/
	void GameObjectInput(const InputState& _keyState)override;
	/*
	@fn アニメーションの更新処理
	*/
	void AnimationUpdate();
	/*
	@fn めり込み判定
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag);
	/*
	@fn 押し戻し処理
	*/
	void playerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox,Vector3& _calcFixVec,const Tag& __pairTag);
	
	// シーン遷移時に使うフラグのgetter
	static bool GetClearFlag() { return clearFlag; }
	static bool GetNextSceneFlag() { return nextSceneFlag; }
	static bool GetReStartFlag() { return reStartFlag; }

	// 着地effect側で使用するフラグ用のgetter
	static bool GetChackJumpFlag() { return chackJumpFlag; }
	static bool GetChackIsJumpingFlag() { return chackIsJumping; }

private:

	//3Dモデルの描画を行うクラス
	SkeletalMeshComponent* skeltalMeshComponent;
	Mesh* mesh;
	//当たり判定を行うクラス
	BoxCollider* boxCollider;
	SphereCollider* groundChackSphereCol;

	void OnCollision(const GameObject& _hitObject)override;
	void OnCollisionGround(const GameObject& _hitObject);

	//押し戻しに使うプレイヤーのAABB
	AABB playerBox;
	//-----------アニメーション関係------------//
	std::vector<const Animation*> animTypes;


	//再生するアニメーションの状態
	int animState;
	//切り替わったかを判断するための変数
	int tmpAnimState;
	//-----------------------------------------//

	//速度の定数
	const float moveSpeed;
	//入力があったかどうか判定するためのフラグ
	bool inputFlag = false;
	//右方向ベクトル
	Vector3 rightVec;
	//キャラクターの前方ベクトル
	Vector3 charaForwardVec;
	//キャラクターを回転させるか前方ベクトルと比較するためのベクトル
	Vector3 tmpCharaForwardVec;
	//方向に合わせて回転させるためのベクトル
	Vector3 rotateVec;
	Vector3 firstPos;
	Vector3 startPos;
	Vector3 respownPos;

	//押されている速度
	Vector3 pushedVelocity;
	//重力
	static const float Gravity;
	//初期ジャンプ力定数
	const float FirstJumpPower;

	//ジャンプ力
	float jumpPower;
	//ジャンプ中かどうかのフラグ
	bool isJumping;
	//引き続きジャンプボタンが利用可能かフラグ
	bool isAvailableJumpKey;
	//ジャンプできるかフラグ
	bool jumpFlag;
	//ジャンプボタンが押されている間のフレームカウント
	int jumpFrameCount;
	//ジャンプスイッチを押したかどうか
	bool switchJumpFlag;
	//接地フラグ
	bool onGround;
	//走り状態かどうか
	bool runFlag;
	// 入力が可能かどうか
	bool isAvailableInput;
	// 入力がない間カウント
	int reStartCount;
	// ダウン状態かどうか
	bool downFlag;
	// ダウン時コンティニュー選択でYESが選択されたかどうか
	bool downUpFlag;
	// ダウン時コンティニュー選択でNOが選択されたかどうか
	bool downOverFlag;

	// 最終ステージ用のクリアフラグ
	static bool clearFlag;
	// 最終ステージ以外での次のシーンへ遷移するフラグ
	static bool nextSceneFlag;
	// 一定時間以上入力がなかった際にタイトルへ戻るフラグ
	static bool reStartFlag;
	// 着地effectを発生させる際に使用するフラグ
	// JumpFlagチェック用
	static bool chackJumpFlag;
	// isJumpingチェック用（ジャンプ中かどうか）
	static bool chackIsJumping;

	// 死んだ際にすぐリスポーンさせないためのカウント
	int reSpawnCount;
	// リスポーン用フラグ
	bool reSpawnFlag;

	// dead状態かそうじゃないか確認用フラグ
	bool deadFlag;

};

