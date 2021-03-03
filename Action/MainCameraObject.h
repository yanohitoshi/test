#pragma once
#include "GameObject.h"
#include "CameraObjectBase.h"
#include "PlayerObject.h"

/*
@file MainCameraObject.h
@brief メインカメラ ゲーム中のオブジェクトを映す
*/

class LineSegmentCollider;
class SphereCollider;
class BoxCollider;

class MainCameraObject :
	public CameraObjectBase
{
public:
	/*
	@brief	コンストラクタ
	@param	ポジション
	*/
	MainCameraObject(const Vector3 _pos);
	~MainCameraObject();

	//このクラスはポーズ中に別クラスから更新関数を呼ばれることがある
	void UpdateGameObject(float _deltaTime = 1.0f)override;
	void GameObjectInput(const InputState& _keyState)override;
	/*
	@param _offset　見たい座標との差
	@param _parentPos　見る座標
	*/
	void SetViewMatrixLerpObject(const Vector3& _offset, const Vector3& _parentPos);
	void FixCollision(AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag);
	void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);

	void SetLerpObjectPos(const Vector3& _pos) { lerpObjectPos = _pos; }
	Vector3 GetCameraVec() { return forwardVec; }
	void ReSetYaw() { yaw = Math::ToRadians(180); }

private:


	//親オブジェクトとの差
	Vector3 offsetPos;
	//追従先のオブジェクト座標
	Vector3 lerpObjectPos;
	//追従先のオブジェクトを所持しているか
	bool hasParentObject;
	Vector3 cameraFront = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 cameraUp = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 direction;
	Vector3 vel;
	//カメラの高さ
	float height;
	//カメラ回転計算用のヨーとピッチ
	float yaw;
	float pitch;
	//カメラの移動速度
	static const float yawSpeed;
	static const float pitchSpeed;

	//カメラ回転の半径
	float r;

	//移動先position
	Vector3 tmpMovePos;
	Vector3 tmpPosition;
	//前方ベクトル
	//Vector3 forwardVec;
	void OnCollision(const GameObject& _hitObject)override;
	LineSegmentCollider* lineSegmentCollider;
	SphereCollider* sphereCollider;
	BoxCollider* boxcollider;

	Matrix4 view;

	int cameraTutorialCount;
	bool tutorialCameraFlag;

	bool input;
};

